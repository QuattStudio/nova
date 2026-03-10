#include "nova_image.h"



#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#include "nova_algo.h"

#include "nova_renderer.h"
#include "glh.h"

#include "nova_.h"
#include "nova_common.h"
#include "nova_colorl.h"
#include "core/nova_types.h"



nova_Texture* nova_LoadTexture(const char* filepath)
{
    int w, h, channels;
    // stbi_set_flip_vertically_on_load(NOVA_TRUE);   // OpenGL needs this

    unsigned char* data = stbi_load(filepath, &w, &h, &channels, 4); // force RGBA
    if (!data) {
        NOVA_LOG_WARN("Failed to load image: %s", filepath);
        return NULL;
    }

    nova_Texture* tex = NOVA_MALLOC(nova_Texture);
    glGenTextures(1, &tex->id);
    glBindTexture(GLH_TEX2D, tex->id);


    glTexImage2D(GLH_TEX2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GLH_UBYTE, data);
    GLH_GenMipmap(GLH_TEX2D);


    GLH_SetTex2Dparami(GL_TEXTURE_WRAP_S, GL_REPEAT);
    GLH_SetTex2Dparami(GL_TEXTURE_WRAP_T, GL_REPEAT);
    GLH_SetTex2Dparami(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    GLH_SetTex2Dparami(GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    stbi_image_free(data);

    tex->width = w;
    tex->height = h;
    return tex;
}





// u0,v0 = top-left texcoord, u1,v1 = bottom-right texcoord
void nova_DrawTexture(nova_App* app, nova_Texture* tex, nova_Rect* rect)
{
    // if texture changed -> flush batch
    nova_Uint texId = tex ? tex->id : (nova_WhiteTexture ? nova_WhiteTexture->id : 0);
    if (texId != CurrentBoundTexture) {
        nova_FlushBatch(app);
        app->mesh->VertexCount = 0;
        app->mesh->IndexCount = 0;
        CurrentBoundTexture = texId;
    }

    size_t base = app->mesh->VertexCount;

    float u0, v0, u1, v1;
    u0 = 0.0f;
    v0 = 0.0f;
    u1 = 1.0f;
    v1 = 1.0f;
    

    /*
        we normallizing because ...
        I don't Known

        may be because previously nova_DrawImage function explicity takes tint of an image so
        we normalize it but now just for laziness of few lines we write directly also
        writing 1.0f is weird at least for me.

    */

    nova_Color fcolor;
    fcolor = nova_NormalizeColorEx(NOVA_COLOR_WHITE);

    // Note: choose vertex ordering consistent with your coordinate system
    nova_PushVertexUV(app, rect->x, rect->y,                  fcolor, u0, v0); // top-left
    nova_PushVertexUV(app, rect->x + rect->width, rect->y,    fcolor, u1, v0); // top-right
    nova_PushVertexUV(app, rect->x, rect->y + rect->height,   fcolor, u0, v1); // bottom-left
    nova_PushVertexUV(app, rect->x + rect->width, rect->y + rect->height,  fcolor, u1, v1); // bottom-right

    nova_PushIndex(app, (nova_Uint)(base + 0));
    nova_PushIndex(app, (nova_Uint)(base + 1));
    nova_PushIndex(app, (nova_Uint)(base + 2));

    nova_PushIndex(app, (nova_Uint)(base + 1));
    nova_PushIndex(app, (nova_Uint)(base + 3));
    nova_PushIndex(app, (nova_Uint)(base + 2));
}













void nova_DrawTextureEx(nova_App* app, nova_Texture* tex, nova_Rect* rect, nova_Colori color)
{
        // if texture changed -> flush batch
    nova_Uint texId = tex ? tex->id : (nova_WhiteTexture ? nova_WhiteTexture->id : 0);
    if (texId != CurrentBoundTexture) {
        nova_FlushBatch(app);
        app->mesh->VertexCount = 0;
        app->mesh->IndexCount = 0;
        CurrentBoundTexture = texId;
    }

    size_t base = app->mesh->VertexCount;

    float u0, v0, u1, v1;
    u0 = 0.0f;
    v0 = 0.0f;
    u1 = 1.0f;
    v1 = 1.0f;
    


    nova_Color fcolor;
    fcolor = nova_NormalizeColorEx(color);

    // Note: choose vertex ordering consistent with your coordinate system
    nova_PushVertexUV(app, rect->x, rect->y,                  fcolor, u0, v0); // top-left
    nova_PushVertexUV(app, rect->x + rect->width, rect->y,    fcolor, u1, v0); // top-right
    nova_PushVertexUV(app, rect->x, rect->y + rect->height,   fcolor, u0, v1); // bottom-left
    nova_PushVertexUV(app, rect->x + rect->width, rect->y + rect->height,  fcolor, u1, v1); // bottom-right

    nova_PushIndex(app, (nova_Uint)(base + 0));
    nova_PushIndex(app, (nova_Uint)(base + 1));
    nova_PushIndex(app, (nova_Uint)(base + 2));

    nova_PushIndex(app, (nova_Uint)(base + 1));
    nova_PushIndex(app, (nova_Uint)(base + 3));
    nova_PushIndex(app, (nova_Uint)(base + 2));
}





void nova_UnloadTexture(nova_Texture* texture)
{
    if (NOVA_NOT texture) return;
    free(texture);
}

