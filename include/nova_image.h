#pragma once

#include "nova_platforms.h"




typedef struct nova_Texture nova_Texture;
typedef struct nova_Rect nova_Rect;
typedef struct nova_Colori nova_Colori;
typedef struct nova_App nova_App;

// #include "glh.h"



NOVA_API nova_Texture* nova_LoadTexture(const char* filepath);



// u0,v0 = top-left texcoord, u1,v1 = bottom-right texcoord
NOVA_API void nova_DrawTexture(nova_App* app, nova_Texture* tex, nova_Rect* rect);
NOVA_API void nova_DrawTextureEx(nova_App* app, nova_Texture* tex, nova_Rect* rect, nova_Colori color);
// NOVA_API void nova_DrawTextureEx(nova_Texture* tex, int x, int y, int w, int h, int rotation, int scaleX, int scaleY);


NOVA_API void nova_UnloadTexture(nova_Texture* texture);




