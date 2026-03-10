/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once



#include "core/nova_core.h"
#include "core/nova_types.h"

#include "nova_platforms.h"







#define NOVA_MAX_TRIANGLES    0x1388  // 5k
#define NOVA_MAX_INDICES      0x7530  // 30k  
#define NOVA_MAX_VERTICES     (NOVA_MAX_TRIANGLES * 3)



extern nova_Vertex sa_vertex_I[NOVA_MAX_VERTICES];
extern nova_Uint   sa_index_I[NOVA_MAX_INDICES];


extern nova_Uint CurrentBoundTexture;



/* struct definations */

typedef struct nova_App nova_App;


/* structs */

typedef struct nova_Texture {
    nova_Uint id;
    int width, height;
} nova_Texture;



extern nova_Texture* nova_WhiteTexture;   // global white texture for colored draws
extern int uModelLoc;



// NOVA_API
int nova_InitRenderer_I(nova_App* app);


NOVA_API
void nova_PushIndex(nova_App* app, nova_Uint idx);


// Simple vertex push (you can use this directly)
NOVA_API
void nova_PushVertex(nova_App* app, float x, float y, nova_Color color);


NOVA_API
void nova_PushVertexUV(nova_App* app, float x, float y, nova_Color color, float u, float v);



NOVA_API
void nova_DrawTriangle(
    nova_App* app,
    int x1, int y1, nova_Colori color1,
    int x2, int y2, nova_Colori color2,
    int x3, int y3, nova_Colori color3);




NOVA_API
void nova_DrawRect(nova_App* app, nova_Rect* rect, nova_Colori color);


NOVA_API
void nova_DrawRecti(nova_App* app, nova_Recti* rect, nova_Colori color);




NOVA_API
void nova_SetProjectionOrtho(float left, float right, float bottom, float top);




NOVA_API
void nova_FlushBatch(nova_App* app);






NOVA_API
void nova_DrawPoint(nova_App* app, int x, int y, nova_Colori color);



NOVA_API
void nova_DrawLine(nova_App* app, int x0, int y0, int x1, int y1, nova_Colori color);


NOVA_API
void nova_DrawRectLines(nova_App* app, nova_Rect* rect, nova_Colori color);
