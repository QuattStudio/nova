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
#include "core/nova_common.h"

#include "core/nova_core.h"


#include <string.h>



/* MACROS */


#define NOVA_INIT_ARRAY(object)     memset(object, 0, sizeof(object))



/* FUNCTIONS */

/**
 * @brief Window Context
 * Window Context
 * 
 * @details nova_Window is a struct used by SageAura, developers don't usually need it to
 * directly interfare with it, this usually used by SageAura itself
 */
typedef struct nova_App nova_App;






extern int nova_IsControlFlagEnabled_I;










/**
 * Opens the window of the game engine.
 * 
 * @param width   Width of the window.
 * @param height  Height of the window.
 * @param title  Title of the window.
 * 
 * @return 1 on success and 0 on failure.
*/
NOVA_API nova_App* nova_StartApp(int width, int height, const char* title, int flags);




NOVA_API void nova_Run(nova_App* app);


NOVA_API void nova_NewApp(nova_App* RootApp, nova_App* app);





NOVA_API void nova_SetEventTo(nova_App* app, nova_EventCallback callback);






/**
 * Set Background Color of window
 * 
 * @param color Takes new color of the window
 * 
 * @since added in version 0.4.0
*/
NOVA_API void nova_SetBackgroundColor(nova_App* app, nova_Colori color);






// NOVA_API void nova_EnableFullScreen();


// NOVA_API void nova_DisableFullScreen();


// NOVA_API void nova_GetMousePosition(double* x, double *y);



// NOVA_API void nova_StopPlaying(void);

// NOVA_API nova_Sizei nova_GetWindowSize(void);
// NOVA_API int nova_GetWindowWidth(void);
// NOVA_API int nova_GetWindowHeight(void);

// NOVA_API const char* nova_GetWindowTitle(const char* title);
// NOVA_API void nova_SetWindowTitle(const char* title);
// NOVA_API nova_Bool nova_IsFullScreen(void);




/* Macros for task simplifications */

#define nova_CheckIsControlFlagEnabled_I(retType)\
    if (nova_IsControlFlagEnabled_I)\
        return retType;\
    else exit(1)


#define nova_CheckIsControlFlagEnabledEx_I(retType, msg)\
    NOVA_LOG_ERROR(msg);\
    nova_CheckIsControlFlagEnabled_I(retType)

