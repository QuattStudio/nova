#include "nova_text.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"   // put stb_truetype.h in src/ or external/include/

#include "nova_.h"
#include "nova_inc.h"
#include "nova_renderer.h"

#include "glh.h"
#include "nova_algo.h"

#include "nova_common.h"




// ────────────────────────────────────────────────
// Text / Font support (embedded in renderer)
// ────────────────────────────────────────────────

typedef struct nova_Font {
    stbtt_fontinfo     info;
    GLuint             texID;
    int                atlasW, atlasH;
    stbtt_packedchar   chardata[128];     // 32..126 + some margin
    float              size;
    float              ascent, descent, linegap;
} nova_Font;









nova_Font *nova_DefaultFont_I = NULL;


















nova_Font* nova_LoadFont(const char* ttf_path, float pixel_size)
{
    nova_Font* f = calloc(1, sizeof(nova_Font));
    
    if (NOVA_NOT f) {
        NOVA_LOG_WARN("allocation failed while creating a font!");
        return NULL;
    }


    FILE* fp = fopen(ttf_path, "rb");
    if (NOVA_NOT fp) {
        NOVA_LOG_WARN("Failed to access ttf file of path [%s]", ttf_path); 
        free(f); 
        return NULL; 
    }


    fseek(fp, 0, SEEK_END);
    long sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);


    unsigned char* buf = malloc(sz);
    fread(buf, 1, sz, fp);
    fclose(fp);

    if (NOVA_NOT stbtt_InitFont(&f->info, buf, 0)) {
        NOVA_LOG_WARN("Font Init Failed! Font path: %s", ttf_path);
        free(buf); 
        free(f); 
        return NULL;
    }

    f->size = pixel_size;

    int ascent, descent, linegap;
    stbtt_GetFontVMetrics(&f->info, &ascent, &descent, &linegap);

    float scale = stbtt_ScaleForPixelHeight(&f->info, pixel_size);
    f->ascent   = ascent   * scale;
    f->descent  = descent  * scale;
    f->linegap  = linegap  * scale;

    // Atlas
    f->atlasW = 512;
    f->atlasH = 512;
    nova_Uint8* alpha_map = calloc(f->atlasW * f->atlasH, 1);

    stbtt_pack_context pc;
    stbtt_PackBegin(&pc, alpha_map, f->atlasW, f->atlasH, 0, 1, NULL);
    stbtt_PackSetOversampling(&pc, 2, 2);
    stbtt_PackFontRange(&pc, buf, 0, pixel_size, 32, 95, f->chardata + 32);
    stbtt_PackEnd(&pc);

    // Make RGBA white + alpha (so original shader tex * vertexColor works perfectly)
    nova_Uint8* rgba = malloc(f->atlasW * f->atlasH * 4);
    for (int i = 0; i < f->atlasW * f->atlasH; i++) {
        rgba[i*4 + 0] = 255;
        rgba[i*4 + 1] = 255;
        rgba[i*4 + 2] = 255;
        rgba[i*4 + 3] = alpha_map[i];
    }

    GLH_SetupTex2D(&f->texID, 1);
    glTexImage2D(GLH_TEX2D, 0, GL_RGBA, f->atlasW, f->atlasH, 0, GL_RGBA, GLH_UBYTE, rgba);

    GLH_SetTex2Dparami(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GLH_SetTex2Dparami(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLH_BindTex2D(CurrentBoundTexture);

    free(buf);
    free(alpha_map);
    free(rgba);

    NOVA_LOG_INFO("Font loaded → texID = %u, size=%.1f", f->texID, pixel_size);
    NOVA_LOG_INFO("Atlas uploaded, bound tex now %u", CurrentBoundTexture);

    return f;
}








void nova_SetDefaultFont(nova_Font* font)
{
    if (NOVA_NOT font) {
        NOVA_LOG_WARN("No Font provided for default!");
        return;
    }

    nova_DefaultFont_I = font;
}














void nova_DrawText(nova_App* app, const char* str, float x, float y, nova_Colori color)
{
    nova_Font* font = nova_DefaultFont_I;

    if (!font || !str || !*str) return;

    if (CurrentBoundTexture != font->texID) {
        nova_FlushBatch(app);
        app->mesh->VertexCount = 0;
        app->mesh->IndexCount  = 0;
        CurrentBoundTexture = font->texID;
    }



    float cx = x;
    float cy = y + font->ascent;

    nova_Color fc = nova_NormalizeColorEx(color);

    while (*str) {
        int ch = (unsigned char)*str++;
        if (ch < 32 || ch > 126) {
            if (ch == ' ') cx += font->size * 0.45f;
            continue;
        }

        stbtt_aligned_quad q;
        stbtt_GetPackedQuad(font->chardata, font->atlasW, font->atlasH,
                            ch, &cx, &cy, &q, 1);   // 1 = use align (baseline)

        // Push quad (using your existing helpers)
        size_t base = app->mesh->VertexCount;

        nova_PushVertexUV(app, q.x0, q.y0, fc, q.s0, q.t0);
        nova_PushVertexUV(app, q.x1, q.y0, fc, q.s1, q.t0);
        nova_PushVertexUV(app, q.x0, q.y1, fc, q.s0, q.t1);
        nova_PushVertexUV(app, q.x1, q.y1, fc, q.s1, q.t1);

        nova_PushIndex(app, base+0); nova_PushIndex(app, base+1); nova_PushIndex(app, base+2);
        nova_PushIndex(app, base+1); nova_PushIndex(app, base+3); nova_PushIndex(app, base+2);

        if (app->mesh->VertexCount >= NOVA_MAX_VERTICES - 4) {
            nova_FlushBatch(app);
            app->mesh->VertexCount = 0;
            app->mesh->IndexCount  = 0;
        }
    }

    nova_FlushBatch(app);  // force draw text this frame
}









void nova_DrawTextEx(nova_App* app, nova_Font* font, const char* str, float x, float y, nova_Colori color)
{
    if (!font || !str || !*str) return;

    if (CurrentBoundTexture != font->texID) {
        nova_FlushBatch(app);
        app->mesh->VertexCount = 0;
        app->mesh->IndexCount  = 0;
        CurrentBoundTexture = font->texID;
    }



    float cx = x;
    float cy = y + font->ascent;

    nova_Color fc = nova_NormalizeColorEx(color);

    while (*str) {
        int ch = (unsigned char)*str++;
        if (ch < 32 || ch > 126) {
            if (ch == ' ') cx += font->size * 0.45f;
            continue;
        }

        stbtt_aligned_quad q;
        stbtt_GetPackedQuad(font->chardata, font->atlasW, font->atlasH,
                            ch, &cx, &cy, &q, 1);   // 1 = use align (baseline)

        // Push quad (using your existing helpers)
        size_t base = app->mesh->VertexCount;

        nova_PushVertexUV(app, q.x0, q.y0, fc, q.s0, q.t0);
        nova_PushVertexUV(app, q.x1, q.y0, fc, q.s1, q.t0);
        nova_PushVertexUV(app, q.x0, q.y1, fc, q.s0, q.t1);
        nova_PushVertexUV(app, q.x1, q.y1, fc, q.s1, q.t1);

        nova_PushIndex(app, base+0); nova_PushIndex(app, base+1); nova_PushIndex(app, base+2);
        nova_PushIndex(app, base+1); nova_PushIndex(app, base+3); nova_PushIndex(app, base+2);

        if (app->mesh->VertexCount >= NOVA_MAX_VERTICES - 4) {
            nova_FlushBatch(app);
            app->mesh->VertexCount = 0;
            app->mesh->IndexCount  = 0;
        }
    }

    nova_FlushBatch(app);  // force draw text this frame
}








void nova_UnLoadFont(nova_Font* font)
{
    if (NOVA_NOT font) {
        NOVA_LOG_INFO("No font provide to UnLoad!");
        return;
    }


    glDeleteTextures(1, &font->texID);
    free(font);
    font = NULL;

    NOVA_LOG_INFO("Font UnLoaded Successfully!");
}