/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

/* includes */

// internals
#include "nova_.h"

// others

#include "nova_renderer.h"

#include "nova_window.h"

#include "nova_inc.h"
#include "nova_algo.h"

#include "nova_common.h"
#include "nova_shaders.h"

#include "glh.h"

#include <math.h>



// Include End //





/* globals & statics */

nova_Vertex sa_vertex_I[NOVA_MAX_VERTICES];
nova_Uint sa_index_I[NOVA_MAX_INDICES];

static nova_Uint ShaderProgram;
// nova_Mesh* GlobalMesh = NULL;
int uModelLoc;


// add near existing globals
nova_Texture* nova_WhiteTexture = NULL; // white 1x1 texture
nova_Uint CurrentBoundTexture = 0; // 0 means white


// struct definations
typedef struct nova_App nova_App;



/* functions */


static void nova_CreateWhiteTexture_I(void)
{
    unsigned char white[4] = { 255, 255, 255, 255 };
    nova_WhiteTexture = NOVA_MALLOC(nova_Texture);
    glGenTextures(1, &nova_WhiteTexture->id);
    glBindTexture(GL_TEXTURE_2D, nova_WhiteTexture->id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white);
    GLH_GenMipmap(GLH_TEX2D);

    GLH_SetTexparami(GL_TEXTURE_WRAP_S, GL_REPEAT);
    GLH_SetTexparami(GL_TEXTURE_WRAP_T, GL_REPEAT);
    GLH_SetTexparami(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    GLH_SetTexparami(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    nova_WhiteTexture->width = 1;
    nova_WhiteTexture->height = 1;
}






int nova_InitRenderer_I(nova_App* app)
{
    NOVA_LOG_INFO("[Side: Renderer] > Setting up Renderer...");


    


        /* Load GLAD */
    if (NOVA_NOT GLH_GL_Load()) {
        NOVA_LOG_ERROR("GLAD Loading failed!");
        nova_CheckIsControlFlagEnabled_I(NOVA_FALSE);
    }

    glEnable(GL_MULTINOVAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    nova_Uint VAO, VBO, EBO;


    GLH_SetupVAO(&VAO, 1);

    NOVA_LOGV_INFO("VAO Setup Completed!");

    GLH_SetBufferDataFast(GLH_VBO, &VBO, NULL, sizeof(nova_Vertex) * NOVA_MAX_VERTICES, 1);
    GLH_SetBufferDataFast(GLH_EBO, &EBO, NULL, sizeof(nova_Uint) * NOVA_MAX_INDICES, 1);
    

    NOVA_LOGV_INFO("VBO allocated for max %d vertices (%zu MB)", 
             NOVA_MAX_VERTICES, 
             (sizeof(nova_Vertex) * NOVA_MAX_VERTICES) / (1024*1024));

    NOVA_LOGV_INFO("VBO & EBO Setup Completed!");



    // stride is sizeof(nova_Vertex)
    GLsizei stride = (GLsizei)sizeof(nova_Vertex);

    // position: location 0, vec2
    GLH_SetVertexAttrib(0, 2, GL_FLOAT, GL_FALSE, stride, NOVA_OFFSET(0));

    // color: location 1, vec4; offset = 2 * sizeof(float)
    GLH_SetVertexAttrib(1, 4, GL_FLOAT, GL_FALSE, stride, NOVA_OFFSET(2 * sizeof(float)));

    // texcoord: location 2, vec2; offset = 6 * sizeof(float)
    GLH_SetVertexAttrib(2, 2, GL_FLOAT, GL_FALSE, stride, NOVA_OFFSET(6 * sizeof(float)));


    NOVA_LOGV_INFO("Vertex Atrribute setted!");


    nova_Uint VertexShader = GLH_CompileShader(&nova_VertexShaderSrc_I, 1, GL_VERTEX_SHADER);
    NOVA_LOGV_INFO("Vertex Shader compiled successfully!");
    
    nova_Uint FragmentShader = GLH_CompileShader(&nova_FragmentShaderSrc_I, 1, GL_FRAGMENT_SHADER);
    NOVA_LOGV_INFO("Fragment Shader compiled successfully!");


    ShaderProgram = GLH_CreateProgram(VertexShader, FragmentShader); // compile & link
    NOVA_LOGV_INFO("Renderer program created successfully!");

    glUseProgram(ShaderProgram);
    GLint loc = glGetUniformLocation(ShaderProgram, "uTexture");

    if (loc >= 0) {
        glUniform1i(loc, 0); // texture unit 0
    }


    app->mesh = nova_CreateMesh_I(VAO, VBO, EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GLH_EBO, EBO);
    glBindVertexArray(0);


    nova_CreateWhiteTexture_I();
    CurrentBoundTexture = nova_WhiteTexture ? nova_WhiteTexture->id : 0;

    NOVA_LOG_INFO("[Side: Renderer] > Renderer Init completed!");
}













void nova_PushIndex(nova_App* app, nova_Uint idx)
{
    if (app->mesh->IndexCount >= NOVA_MAX_INDICES) {
        nova_FlushBatch(app);
        nova_MeshCounterReset_I(app->mesh);
    }
    sa_index_I[app->mesh->IndexCount++] = idx;
}






void nova_PushVertex(nova_App* app, float x, float y, nova_Color color)
{
    if (app->mesh->VertexCount >= NOVA_MAX_VERTICES || 
        app->mesh->IndexCount >= NOVA_MAX_INDICES - 6) {   // safety margin
        nova_FlushBatch(app);
        nova_MeshCounterReset_I(app->mesh);
    }

    nova_Vertex* vertex = &sa_vertex_I[app->mesh->VertexCount++];
    vertex->x = x; 
    vertex->y = y;

    vertex->r = color.r; 
    vertex->g = color.g; 
    vertex->b = color.b; 
    vertex->a = color.a;

    // default
    vertex->u = 0.0f; 
    vertex->v = 0.0f; 
}





void nova_PushVertexUV(nova_App* app, float x, float y, nova_Color color, float u, float v)
{
    if (app->mesh->VertexCount >= NOVA_MAX_VERTICES ||
        app->mesh->IndexCount >= NOVA_MAX_INDICES - 6) {
        nova_FlushBatch(app);
        nova_MeshCounterReset_I(app->mesh);
    }

    nova_Vertex* vertex = &sa_vertex_I[app->mesh->VertexCount++];
    vertex->x = x; 
    vertex->y = y;

    vertex->r = color.r; 
    vertex->g = color.g; 
    vertex->b = color.b; 
    vertex->a = color.a;

    vertex->u = u; 
    vertex->v = v;
}




void nova_DrawTriangle(
    nova_App* app,
    int x1, int y1, nova_Colori color1,
    int x2, int y2, nova_Colori color2,
    int x3, int y3, nova_Colori color3)
{
    nova_Uint whiteId = nova_WhiteTexture ? nova_WhiteTexture->id : 0;
    if (CurrentBoundTexture != whiteId) {
        nova_FlushBatch(app);
        nova_MeshCounterReset_I(app->mesh);
        CurrentBoundTexture = whiteId;
    }

    size_t base = app->mesh->VertexCount;

    
    nova_Color fcolor1;
    nova_Color fcolor2;
    nova_Color fcolor3;
    fcolor1 = nova_NormalizeColorEx(color1);
    fcolor2 = nova_NormalizeColorEx(color2);
    fcolor3 = nova_NormalizeColorEx(color3);


    nova_PushVertex(app, (float)x1, (float)y1, fcolor1);
    nova_PushVertex(app, (float)x2, (float)y2, fcolor2);
    nova_PushVertex(app, (float)x3, (float)y3, fcolor3);

    nova_PushIndex(app, base + 0);
    nova_PushIndex(app, base + 1);
    nova_PushIndex(app, base + 2);
}




void nova_DrawRect(nova_App* app, nova_Rect* rect, nova_Colori color)
{
    nova_Uint whiteId = nova_WhiteTexture ? nova_WhiteTexture->id : 0;
    if (CurrentBoundTexture != whiteId) {
        nova_FlushBatch(app);
        nova_MeshCounterReset_I(app->mesh);
        CurrentBoundTexture = whiteId;
    }

    size_t base = app->mesh->VertexCount;   // starting index for this rect

    nova_Color fcolor;
    fcolor = nova_NormalizeColorEx(color);

    // Push 4 vertices (counter-clockwise order)
    nova_PushVertex(app, rect->x,     rect->y,     fcolor);   // 0 top-left
    nova_PushVertex(app, rect->x + rect->width, rect->y,     fcolor);   // 1 top-right
    nova_PushVertex(app, rect->x,     rect->y + rect->height, fcolor);   // 2 bottom-left
    nova_PushVertex(app, rect->x + rect->width, rect->y + rect->height, fcolor);   // 3 bottom-right

    // Push 6 indices (two triangles)
    nova_PushIndex(app, base + 0);
    nova_PushIndex(app, base + 1);
    nova_PushIndex(app, base + 2);

    nova_PushIndex(app, base + 1);
    nova_PushIndex(app, base + 3);
    nova_PushIndex(app, base + 2);
}





void nova_DrawRecti(nova_App* app, nova_Recti* rect, nova_Colori color)
{
    nova_Uint whiteId = nova_WhiteTexture ? nova_WhiteTexture->id : 0;
    if (CurrentBoundTexture != whiteId) {
        nova_FlushBatch(app);
        nova_MeshCounterReset_I(app->mesh);
        CurrentBoundTexture = whiteId;
    }

    size_t base = app->mesh->VertexCount;   // starting index for this rect

    nova_Color fcolor;
    fcolor = nova_NormalizeColorEx(color);

    // Push 4 vertices (counter-clockwise order)
    nova_PushVertex(app, (float)rect->x,  (float)rect->y,     fcolor);   // 0 top-left
    nova_PushVertex(app, (float)rect->x + (float)rect->width, (float)rect->y,     fcolor);   // 1 top-right
    nova_PushVertex(app, (float)rect->x,  (float)rect->y + rect->height, fcolor);   // 2 bottom-left
    nova_PushVertex(app, (float)rect->x + (float)rect->width, (float)rect->y + (float)rect->height, fcolor);   // 3 bottom-right

    // Push 6 indices (two triangles)
    nova_PushIndex(app, base + 0);
    nova_PushIndex(app, base + 1);
    nova_PushIndex(app, base + 2);

    nova_PushIndex(app, base + 1);
    nova_PushIndex(app, base + 3);
    nova_PushIndex(app, base + 2);
}





void nova_SetProjectionOrtho(float left, float right, float bottom, float top)
{
    float ortho[16] = {
        2.0f/(right-left),  0,                  0, 0,
        0,                  2.0f/(top-bottom),  0, 0,
        0,                  0,                 -1, 0,
        -(right+left)/(right-left), -(top+bottom)/(top-bottom), 0, 1
    };

    GLint loc = glGetUniformLocation(ShaderProgram, "uProjection");
    glUseProgram(ShaderProgram);
    glUniformMatrix4fv(loc, 1, GL_FALSE, ortho);
}











void nova_FlushBatch(nova_App* app)
{
    if (app->mesh->IndexCount == 0) return;

    
    // Upload VBO data
    glBindBuffer(GLH_VBO, app->mesh->VBO);
    glBufferSubData(GLH_VBO, 0,
                    app->mesh->VertexCount * sizeof(nova_Vertex),
                    sa_vertex_I);

    
    // Upload EBO data
    glBindBuffer(GLH_EBO, app->mesh->EBO);
    glBufferSubData(GLH_EBO, 0,
                    app->mesh->IndexCount * sizeof(nova_Uint),
                    sa_index_I);

                    
    glUseProgram(ShaderProgram);
    GLH_BindVAO(app->mesh->VAO);

    // bind texture to unit 0 (use white texture if none set)
    nova_Uint texToBind = CurrentBoundTexture;
    if (texToBind == 0 && nova_WhiteTexture) texToBind = nova_WhiteTexture->id;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GLH_TEX2D, texToBind);

    // draw
    GLH_DrawTriElms((GLsizei)app->mesh->IndexCount, GLH_UINT, 0);

    // unbind
    glBindVertexArray(0);

}





void nova_DrawPoint(nova_App* app, int x, int y, nova_Colori color) {
    // Option A: two small triangles = perfect 1×1 pixel coverage
    nova_DrawTriangle(app, x,   y,   color,
                    x+1, y,   color,
                    x,   y+1, color);

    nova_DrawTriangle(app, x+1, y,   color,
                    x+1, y+1, color,
                    x,   y+1, color);

}

void nova_DrawLine(nova_App* app, int x0, int y0, int x1, int y1, nova_Colori color) {
    float dx = (float)(x1 - x0);
    float dy = (float)(y1 - y0);
    float len = sqrtf(dx*dx + dy*dy);

    if (len < 0.5f) {
        nova_DrawPoint(app, x0, y0, color);
        return;
    }

    float nx = dx / len;
    float ny = dy / len;

    // Perpendicular offset, half thickness = 1.0 px
    float px = -ny * 1.5f;
    float py =  nx * 1.5f;

    // Four corners with rounded offset
    int xA = x0 + (int)( px + 0.5f);
    int yA = y0 + (int)( py + 0.5f);
    int xB = x1 + (int)( px + 0.5f);
    int yB = y1 + (int)( py + 0.5f);
    int xC = x0 - (int)( px + 0.5f);
    int yC = y0 - (int)( py + 0.5f);
    int xD = x1 - (int)( px + 0.5f);
    int yD = y1 - (int)( py + 0.5f);

    // Two triangles forming the thin quad (counter-clockwise winding)
    nova_DrawTriangle(app, xA, yA, color, xB, yB, color, xC, yC, color);
    nova_DrawTriangle(app, xB, yB, color, xD, yD, color, xC, yC, color);
}




void nova_DrawRectLines(nova_App* app, nova_Rect* rect, nova_Colori color) {
    nova_DrawLine(app, rect->x, rect->y, rect->x + rect->width, rect->y, color);          // top
    nova_DrawLine(app, rect->x + rect->width, rect->y, rect->x + rect->width, rect->y + rect->height, color); // right
    nova_DrawLine(app, rect->x, rect->y + rect->height, rect->x + rect->width, rect->y + rect->height, color); // bottom
    nova_DrawLine(app, rect->x, rect->y, rect->x, rect->y + rect->height, color); // left
}



