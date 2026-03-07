/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once






#include "core/sa_types.h"

#include "sa_platforms.h"
#include "core/sa_common.h"

#include "core/sa_core.h"


/**
 * @brief Window Context
 * Window Context
 * 
 * @details SA_Window is a struct used by SageAura, developers don't usually need it to
 * directly interfare with it, this usually used by SageAura itself
 */
typedef struct SA_Window SA_Window;




/* 
    @brief data related to window
    
    Data related to window, who is directly exposed to developers, to help them.

    @warning Don't use this struct until you have at least SageAura 1.0.0 version,
    as it may break and not work properlly 


    @since added in version 0.5.4
*/ 
typedef struct sa_Globals_window {
    // the main first size of window
    int main_width;
    int main_height;

    int main_width_half;
    int main_height_half;

    // the size of window but change when we resize
    int width;
    int height;

    int width_half;
    int height_half;

} sa_Globals_window;


extern int SA_IsControlFlagEnabled_I;
extern sa_Globals_window SA_window;








/**
 * Starts the SageAura game engine
 * @param flags Takes engine initialization flags
 * 
 * @return 1 on success and 0 on failure.
*/
SA_API int SA_Start(int flags);






/**
 * Opens the window of the game engine.
 * 
 * @param width   Width of the window.
 * @param height  Height of the window.
 * @param title  Title of the window.
 * 
 * @return 1 on success and 0 on failure.
*/
SA_API int SA_OpenWindow(int width, int height, const char* title);






/**
 * Close the window of the game engine.
 * 
*/
SA_API void SA_CloseWindow(void);




/**
 * Play the game in loop
 * 
 * @example 
 *  >>> while(SA_Play()) {...}
 * 
 * @return 1 on game should playing else 0.
*/
SA_API int SA_Play();



SA_API void SA_SetEventTo(SA_EventCallback callback);


SA_API void SA_BeginDrawing(void);



SA_API void SA_EndDrawing(void);


/**
 * Set Background Color of window
 * 
 * @param color Takes new color of the window
 * 
 * @since added in version 0.4.0
*/
SA_API void SA_SetBackgroundColor(SA_Colori color);




/**
 * Set Window FPS
 * 
 * @param fps Takes new FPS to set
 * 
 * @since added in version 0.4.0
 * 
*/
SA_API void SA_SetTargetFPS(int fps);






/**
 * Get Delta Time
 *
 * @since added in version 0.5.3 
 * 
 * @return Delta Time of window
*/
SA_API float SA_GetDeltaTime();

SA_API void SA_EnableFullScreen();


SA_API void SA_DisableFullScreen();


SA_API void SA_GetMousePosition(double* x, double *y);



SA_API void SA_StopPlaying(void);

SA_API SA_Sizei SA_GetWindowSize(void);
SA_API int SA_GetWindowWidth(void);
SA_API int SA_GetWindowHeight(void);

SA_API const char* SA_GetWindowTitle(const char* title);
SA_API void SA_SetWindowTitle(const char* title);
SA_API SA_Bool SA_IsFullScreen(void);




/* Macros for task simplifications */

#define SA_CheckIsControlFlagEnabled_I(retType)\
    if (SA_IsControlFlagEnabled_I)\
        return retType;\
    else exit(1)


#define SA_CheckIsControlFlagEnabledEx_I(retType, msg)\
    SA_LOG_ERROR(msg);\
    SA_CheckIsControlFlagEnabled_I(retType)

