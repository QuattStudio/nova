/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/



#pragma once





#include "nova_types.h"



#define NOVA_ALGO_API_I    static inline
#define NOVA_ALGO_MAX_OPACITY_I     (255)




#define nova_Normalize_I(val, max) ((val) / (float)(max))









NOVA_ALGO_API_I
nova_Color NOVA_NormalizeColor(nova_Colori color)
{
    nova_Color colorf;

    colorf.r = nova_Normalize_I(color.r, NOVA_ALGO_MAX_OPACITY_I);
    colorf.g = nova_Normalize_I(color.g, NOVA_ALGO_MAX_OPACITY_I);
    colorf.b = nova_Normalize_I(color.b, NOVA_ALGO_MAX_OPACITY_I);
    colorf.a = 1.0f;

    return colorf;
}





NOVA_ALGO_API_I
nova_Color nova_NormalizeColorEx(nova_Colori color)
{
    nova_Color colorf;

    colorf.r = nova_Normalize_I(color.r, NOVA_ALGO_MAX_OPACITY_I);
    colorf.g = nova_Normalize_I(color.g, NOVA_ALGO_MAX_OPACITY_I);
    colorf.b = nova_Normalize_I(color.b, NOVA_ALGO_MAX_OPACITY_I);
    colorf.a = nova_Normalize_I(color.a, NOVA_ALGO_MAX_OPACITY_I);


    return colorf;
}







// // move from a to b by t (t = 0.0 to 1.0)
// // t=0 returns a, t=1 returns b, t=0.5 returns middle
// NOVA_ALGO_API_I float nova_Lerp(float a, float b, float t) {
//     return a + (b - a) * t;
// }



// // keep value between min and max
// NOVA_ALGO_API_I float nova_Clamp(float val, float min, float max) {
//     if (val < min) return min;
//     if (val > max) return max;
//     return val;
// }



// // remap value from one range to another
// // example: nova_Map(0.5, 0,1, 0,100) = 50
// // example: nova_Map(128, 0,255, 0,1) = 0.5  (normalize)
// NOVA_ALGO_API_I float nova_Map(float val, float a, float b, float c, float d) {
//     return c + (val - a) / (b - a) * (d - c);
// }





// // returns 1 if rects overlap, 0 if not
// NOVA_ALGO_API_I int nova_CheckCollision(nova_Rect a, nova_Rect b) {
//     return a.x < b.x + b.width &&
//            a.x + a.width > b.x &&
//            a.y < b.y + b.height &&
//            a.y + a.height > b.y;
// }



// NOVA_ALGO_API_I int nova_CheckCollisionInt(nova_Recti a, nova_Recti b) {
//     return a.x < b.x + b.width &&
//            a.x + a.width > b.x &&
//            a.y < b.y + b.height &&
//            a.y + a.height > b.y;
// }



// // returns 1 if point is inside rect
// NOVA_ALGO_API_I int nova_CheckCollisionPoint(float px, float py, nova_Rect r) {
//     return px >= r.x && px <= r.x + r.width &&
//            py >= r.y && py <= r.y + r.height;
// }



// // returns 1 if point is inside rect
// NOVA_ALGO_API_I int nova_CheckCollisionPointInt(float px, float py, nova_Recti r) {
//     return px >= r.x && px <= r.x + r.width &&
//            py >= r.y && py <= r.y + r.height;
// }




// // returns 1 if rect a is fully inside rect b
// NOVA_ALGO_API_I int nova_RectContains(nova_Rect outer, nova_Rect inner) {
//     return inner.x >= outer.x &&
//            inner.y >= outer.y &&
//            inner.x + inner.width <= outer.x + outer.width &&
//            inner.y + inner.height <= outer.y + outer.height;
// }






// // returns 1 if rect a is fully inside rect b
// NOVA_ALGO_API_I int nova_RectContainsInt(nova_Recti outer, nova_Recti inner) {
//     return inner.x >= outer.x &&
//            inner.y >= outer.y &&
//            inner.x + inner.width <= outer.x + outer.width &&
//            inner.y + inner.height <= outer.y + outer.height;
// }