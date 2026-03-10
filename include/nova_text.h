#pragma once


#include "nova_platforms.h"
#include "core/nova_types.h"


// ────────────────────────────────────────────────
// Text / Font support (embedded in renderer)
// ────────────────────────────────────────────────

typedef struct nova_Font nova_Font;


extern nova_Font *nova_DefaultFont_I;














NOVA_API nova_Font* nova_LoadFont(const char* ttf_path, float pixel_size);

NOVA_API void nova_SetDefaultFont(nova_Font* font);


NOVA_API void nova_DrawText(nova_App* app, const char* str, float x, float y, nova_Colori color);
NOVA_API void nova_DrawTextEx(nova_App* app, nova_Font* font, const char* str, float x, float y, nova_Colori color);



NOVA_API void nova_UnLoadFont(nova_Font* font);