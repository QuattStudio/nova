/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/


#pragma once


#include "core/nova_types.h"


#include "nova_platforms.h"


typedef enum
{
    NOVA_EVENT_NONE = 0,
    NOVA_EVENT_KEY_DOWN,
    NOVA_EVENT_KEY_UP,
    NOVA_EVENT_MOUSE_MOVE,
    NOVA_EVENT_MOUSE_BUTTON_DOWN,
    NOVA_EVENT_MOUSE_BUTTON_UP,
    NOVA_EVENT_MOUSE_SCROLL,
    NOVA_EVENT_WINDOW_RESIZE,
    NOVA_EVENT_WINDOW_CLOSE
} nova_EventType;



typedef enum nova_Key
{
    NOVA_KEY_UNKNOWN         = -1,

    NOVA_KEY_SPACE           = 32,
    NOVA_KEY_APOSTROPHE      = 39,   /* ' */
    NOVA_KEY_COMMA           = 44,   /* , */
    NOVA_KEY_MINUS           = 45,   /* - */
    NOVA_KEY_PERIOD          = 46,   /* . */
    NOVA_KEY_SLASH           = 47,   /* / */

    NOVA_KEY_0               = 48,
    NOVA_KEY_1               = 49,
    NOVA_KEY_2               = 50,
    NOVA_KEY_3               = 51,
    NOVA_KEY_4               = 52,
    NOVA_KEY_5               = 53,
    NOVA_KEY_6               = 54,
    NOVA_KEY_7               = 55,
    NOVA_KEY_8               = 56,
    NOVA_KEY_9               = 57,

    NOVA_KEY_SEMICOLON       = 59,   /* ; */
    NOVA_KEY_EQUAL           = 61,   /* = */

    NOVA_KEY_A               = 65,
    NOVA_KEY_B               = 66,
    NOVA_KEY_C               = 67,
    NOVA_KEY_D               = 68,
    NOVA_KEY_E               = 69,
    NOVA_KEY_F               = 70,
    NOVA_KEY_G               = 71,
    NOVA_KEY_H               = 72,
    NOVA_KEY_I               = 73,
    NOVA_KEY_J               = 74,
    NOVA_KEY_K               = 75,
    NOVA_KEY_L               = 76,
    NOVA_KEY_M               = 77,
    NOVA_KEY_N               = 78,
    NOVA_KEY_O               = 79,
    NOVA_KEY_P               = 80,
    NOVA_KEY_Q               = 81,
    NOVA_KEY_R               = 82,
    NOVA_KEY_S               = 83,
    NOVA_KEY_T               = 84,
    NOVA_KEY_U               = 85,
    NOVA_KEY_V               = 86,
    NOVA_KEY_W               = 87,
    NOVA_KEY_X               = 88,
    NOVA_KEY_Y               = 89,
    NOVA_KEY_Z               = 90,

    NOVA_KEY_LEFT_BRACKET    = 91,   /* [ */
    NOVA_KEY_BACKSLASH       = 92,   /* \ */
    NOVA_KEY_RIGHT_BRACKET   = 93,   /* ] */
    NOVA_KEY_GRAVE_ACCENT    = 96,   /* ` */

    NOVA_KEY_WORLD_1         = 161,  /* non-US #1 */
    NOVA_KEY_WORLD_2         = 162,  /* non-US #2 */

    NOVA_KEY_ESCAPE          = 256,
    NOVA_KEY_ENTER           = 257,
    NOVA_KEY_TAB             = 258,
    NOVA_KEY_BACKSPACE       = 259,
    NOVA_KEY_INSERT          = 260,
    NOVA_KEY_DELETE          = 261,
    NOVA_KEY_RIGHT           = 262,
    NOVA_KEY_LEFT            = 263,
    NOVA_KEY_DOWN            = 264,
    NOVA_KEY_UP              = 265,

    NOVA_KEY_PAGE_UP         = 266,
    NOVA_KEY_PAGE_DOWN       = 267,
    NOVA_KEY_HOME            = 268,
    NOVA_KEY_END             = 269,

    NOVA_KEY_CAPS_LOCK       = 280,
    NOVA_KEY_SCROLL_LOCK     = 281,
    NOVA_KEY_NUM_LOCK        = 282,
    NOVA_KEY_PRINT_SCREEN    = 283,
    NOVA_KEY_PAUSE           = 284,

    NOVA_KEY_F1              = 290,
    NOVA_KEY_F2              = 291,
    NOVA_KEY_F3              = 292,
    NOVA_KEY_F4              = 293,
    NOVA_KEY_F5              = 294,
    NOVA_KEY_F6              = 295,
    NOVA_KEY_F7              = 296,
    NOVA_KEY_F8              = 297,
    NOVA_KEY_F9              = 298,
    NOVA_KEY_F10             = 299,
    NOVA_KEY_F11             = 300,
    NOVA_KEY_F12             = 301,
    NOVA_KEY_F13             = 302,
    NOVA_KEY_F14             = 303,
    NOVA_KEY_F15             = 304,
    NOVA_KEY_F16             = 305,
    NOVA_KEY_F17             = 306,
    NOVA_KEY_F18             = 307,
    NOVA_KEY_F19             = 308,
    NOVA_KEY_F20             = 309,
    NOVA_KEY_F21             = 310,
    NOVA_KEY_F22             = 311,
    NOVA_KEY_F23             = 312,
    NOVA_KEY_F24             = 313,
    NOVA_KEY_F25             = 314,

    /* Keypad */
    NOVA_KEY_KP_0            = 320,
    NOVA_KEY_KP_1            = 321,
    NOVA_KEY_KP_2            = 322,
    NOVA_KEY_KP_3            = 323,
    NOVA_KEY_KP_4            = 324,
    NOVA_KEY_KP_5            = 325,
    NOVA_KEY_KP_6            = 326,
    NOVA_KEY_KP_7            = 327,
    NOVA_KEY_KP_8            = 328,
    NOVA_KEY_KP_9            = 329,
    NOVA_KEY_KP_DECIMAL      = 330,
    NOVA_KEY_KP_DIVIDE       = 331,
    NOVA_KEY_KP_MULTIPLY     = 332,
    NOVA_KEY_KP_SUBTRACT     = 333,
    NOVA_KEY_KP_ADD          = 334,
    NOVA_KEY_KP_ENTER        = 335,
    NOVA_KEY_KP_EQUAL        = 336,

    /* Modifiers */
    NOVA_KEY_LEFT_SHIFT      = 340,
    NOVA_KEY_LEFT_CONTROL    = 341,
    NOVA_KEY_LEFT_ALT        = 342,
    NOVA_KEY_LEFT_SUPER      = 343,
    NOVA_KEY_RIGHT_SHIFT     = 344,
    NOVA_KEY_RIGHT_CONTROL   = 345,
    NOVA_KEY_RIGHT_ALT       = 346,
    NOVA_KEY_RIGHT_SUPER     = 347,
    NOVA_KEY_MENU            = 348,

    NOVA_KEY_LAST            = 348
} nova_Key;








typedef enum nova_MouseButton
{
    NOVA_MOUSE_BUTTON_UNKNOWN = -1,

    NOVA_MOUSE_BUTTON_1       = 0,
    NOVA_MOUSE_BUTTON_2       = 1,
    NOVA_MOUSE_BUTTON_3       = 2,
    NOVA_MOUSE_BUTTON_4       = 3,
    NOVA_MOUSE_BUTTON_5       = 4,
    NOVA_MOUSE_BUTTON_6       = 5,
    NOVA_MOUSE_BUTTON_7       = 6,
    NOVA_MOUSE_BUTTON_8       = 7,

    NOVA_MOUSE_BUTTON_LAST    = 7,

    // Common aliases (most games only use these 3)
    NOVA_MOUSE_BUTTON_LEFT    = 0,
    NOVA_MOUSE_BUTTON_RIGHT   = 1,
    NOVA_MOUSE_BUTTON_MIDDLE  = 2,

    // You can also use NOVA_MOUSE_BUTTON_4 … NOVA_MOUSE_BUTTON_8 for extra buttons
} nova_MouseButton;





typedef enum nova_MouseWheel
{
    NOVA_MOUSE_WHEEL_NONE = 0,
    NOVA_MOUSE_WHEEL_UP   = 1,
    NOVA_MOUSE_WHEEL_DOWN = -1
} nova_MouseWheel;




typedef struct nova_Event
{
    nova_EventType type;

    union
    {
        struct { nova_Key key; } key;
        struct { double x, y; } mouseMove;
        struct { nova_MouseButton button; } mouseButton;
        struct { double offset; } scroll;
        struct { int width, height; } resize;
    };

} nova_Event;




/* window type declarations */
typedef struct nova_Window nova_Window;
typedef struct GLFWwindow GLFWwindow;



NOVA_API
void nova_PushEvent(nova_Event e);



NOVA_API
int nova_PollEvent(nova_Event* out);



void nova_SetWindowEventCallBacks_I(GLFWwindow* window);









// ================================================================
// Continuous Input (Raylib / SDL / Godot style)
// Call nova_UpdateInput() once per frame!
// ================================================================





NOVA_API void nova_UpdateInput(void);
NOVA_API void nova_ProcessEvent(const nova_Event* e);      // ← NEW: Feed one event into the state system

NOVA_API nova_Bool nova_IsKeyDown(nova_Key key);
NOVA_API nova_Bool nova_IsKeyPressed(nova_Key key);     // true only this frame
NOVA_API nova_Bool nova_IsKeyReleased(nova_Key key);

NOVA_API nova_Bool nova_IsMouseButtonDown(nova_MouseButton button);
NOVA_API nova_Bool nova_IsMouseButtonPressed(nova_MouseButton button);
NOVA_API nova_Bool nova_IsMouseButtonReleased(nova_MouseButton button);

NOVA_API double nova_GetMouseX(void);
NOVA_API double nova_GetMouseY(void);
NOVA_API double nova_GetMouseWheel(void);        // last scroll delta this frame








NOVA_API void nova_HandleEvents(nova_App* app);