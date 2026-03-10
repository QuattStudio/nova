/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once



#include <stdint.h>
#include "nova_image.h"


/* SageAura int & uint types */


// unsigned int (unsigned int)
typedef unsigned int    nova_Uint;

// unsigned int-8 (unsigned char)
typedef uint8_t     nova_Uint8;

// unsigned int-16 (unsigned short)
typedef uint16_t    nova_Uint16;

// unsigned int-32 (unsigned int)
typedef uint32_t    nova_Uint32;

// unsigned int-64 (unsigned long long)
typedef uint64_t    nova_Uint64;



// signed int-8 (signed char)
typedef int8_t      nova_Int8;

// signed int-16 (signed short)
typedef int16_t     nova_Int16;

// signed int-32 (signed int)
typedef int32_t     nova_Int32;

// signed int-64 (signed long long)
typedef int64_t     nova_Int64;






typedef struct nova_App nova_App;
typedef struct nova_Event nova_Event;

typedef void (*nova_EventCallback)(nova_App* window, const nova_Event* event);






/* 
    Nova bools contains:

    NOVA_YES, NOVA_TRUE,
    NOVA_NO, NOVA_FALSE
*/
typedef enum {
    NOVA_NO = 0,
    NOVA_FALSE = 0,
    NOVA_TRUE = 1,
    NOVA_YES = 1, 
} nova_Bool;



/*
    Nova Color is a struct (of int)
    contains:

    int r, g, b, a;
*/
typedef struct nova_Colori {
    int r;
    int g;
    int b;
    int a;
} nova_Colori;





/*
    Nova ColorF is a float struct
    contains:

    float r, g, b, a;
*/
typedef struct nova_Color {
    float r;
    float g;
    float b;
    float a;
} nova_Color;










/*
    Nova Rect is a struct (of int)
    contains:

    int r, g, b, a;
*/
typedef struct nova_Recti 
{
    int x;
    int y;
    int width;
    int height;
} nova_Recti;






/*
    Nova Rect is a float struct
    contains:

    float r, g, b, a;
*/
typedef struct nova_Rect 
{
    float x;
    float y;
    float width;
    float height;
} nova_Rect;







typedef struct nova_Position {
    float x;
    float y;
} nova_Position;




typedef nova_Position nova_Pos;




typedef struct nova_PositionEx {
    double x;
    double y;
} nova_PositionEx;

typedef nova_PositionEx nova_PosEx;




typedef struct nova_Size {
    float width;
    float height;
} nova_Size;




typedef struct nova_Sizei {
    int width;
    int height;
} nova_Sizei;
