/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/


// all main libs
#include "sa_window.h"
#include "sa_common.h"
#include "sa_core.h"
#include "sa_text.h"

#include "sa_event.h"

#include "sa_renderer.h"
#include "sa_audio.h"
#include "sa_inc.h"

#include "sa_algo.h" 


// internals
#define GLH_IMPLEMENTATION
#include "glh.h"


#include "sa_.h"
#include "sa_core_.h"


// C std libs
#include <stdio.h>
#include <stdlib.h>


/* Internally Assigned Window */
SA_Window *SA_WindowInst_I = NULL;





/* internal flags */

// flag to determine either user / developer want contorl in game engine!?
int SA_IsControlFlagEnabled_I = 0;


// internal variables to get known window flags.
static int SA_WindowInitFlags_I;


// check error state of an object
#define SA_CheckErrState_I(obj, retType, msg)\
    if (SA_NOT obj) {\
        SA_CheckIsControlFlagEnabledEx_I(\
            retType,\
            msg\
        );\
    }



/* Functions uses! */
int SA_Start(int flags)
{
    if (flags & SA_FLAG_ENABLE_CONTROL)
        SA_IsControlFlagEnabled_I = 1;
    



    // Init GLFW
    int GLFWInitErrState = glfwInit();

    SA_CheckErrState_I(
        GLFWInitErrState,
        SA_FALSE,
        "GLFW Initialization failed!"
    )

    SA_LOGV_INFO("GLFW Initialization completed!");

    SA_WindowInitFlags_I = flags;

    
    /* Setup Gl version */
    GLH_UseGL330Version();
    SA_LOGV_INFO("GL Version : %d", SA_GL_VERSION_USED);

    SA_OpenAudioEngine_I();


    SA_LOG_INFO("SageAura Initialization completed!");

    return SA_TRUE;
}



/* Create Window */
int SA_OpenWindow(int width, int height, const char* title)
{
    SA_ApplyGLFWWindowHint_I(SA_WindowInitFlags_I);

    if (width < 0 SA_OR height < 0) {
        SA_LOG_WARN("Size (Width or Height) should not be zero! Size: %dx%d", width, height);
        return SA_FALSE;
    }

    // Create GLFW Window 
    GLFWwindow* GLFW_Window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (SA_NOT GLFW_Window)
    {
        SA_CheckIsControlFlagEnabledEx_I(
            SA_FALSE, 
            "GLFW Window Creation Failed!"
        );
    }


    // allocate memory to window 
    SA_Window *window = SA_MALLOC(SA_Window);
    if (SA_NOT window) 
    {
        SA_CheckIsControlFlagEnabledEx_I(
            SA_FALSE, 
            "SageAura Window allocation Failed!"
        );
    }

    glfwMakeContextCurrent(GLFW_Window);


    
    /* Init renderer */
    SA_InitRenderer_I();
    SA_SetProjectionOrtho(0.0f, (float)width, (float)height, 0.0f); // Y=0 at top

    int windowX, windowY;
    glfwGetWindowPos(GLFW_Window, &windowX, &windowY);


    // fill everything with appropiate data
    window->handle = GLFW_Window;
    window->flags = 0;
    window->width = width;
    window->height = height;

    window->x = windowX;
    window->y = windowY;



    window->fps = 60;

    // set background color greyish by default!
    window->color.r = 0.13f;
    window->color.g = 0.13f;
    window->color.b = 0.13f;


    // start the timer, so we can use delta time when we want
    window->timer = SA_StartTimer();

    window->callback = NULL;



    SA_SetWindowEventCallBacks_I(window->handle);


    // register window internally
    SA_WindowInst_I = window;

    
    SA_LOGV_INFO("SageAura Window Creation successfull!");


    return SA_TRUE;
}





int SA_Play()
{

    // don't play if window not found
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, 0);  


    // poll glfw events
    glfwPollEvents();

    // update SageAura Input systems
    SA_UpdateInput();


    // needed for run any type of event handling, can be NULL but important to call for event handling
    SA_HandleEvents(SA_WindowInst_I->callback);


    // return glfwWindowShouldClose
    return SA_NOT glfwWindowShouldClose(SA_WindowInst_I->handle); 
}




SA_API void SA_StopPlaying(void)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    SA_CHECK_WINDOW_I(SA_WindowInst_I->handle, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);  
    
    glfwSetWindowShouldClose(SA_WindowInst_I->handle, SA_YES);
}





void SA_SetEventTo(SA_EventCallback callback)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    
    SA_WindowInst_I->callback = callback;
}




void SA_CloseWindow(void)
{
    // check either SA_WindowInst_I exists or not
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);  


    // destroy mesh of renderer
    SA_DestroyMesh_I(GlobalMesh);


    // destroy window of glfw
    glfwDestroyWindow(SA_WindowInst_I->handle);

    SA_LOGV_INFO("GLFW window Destroyed!");

    // stop the timer, to stop the calculation of delta time
    SA_StopTimer(SA_WindowInst_I->timer);


    // free the memory allocation of window
    free(SA_WindowInst_I);


    // null the window instance
    SA_WindowInst_I = NULL;

    // reset the window internal flags
    SA_WindowInitFlags_I = 0;

    // clear the default font
    if (SA_DefaultFont_I) {
        SA_UnLoadFont(SA_DefaultFont_I);
        SA_DefaultFont_I = NULL;        
        SA_LOG_INFO("Default Font unloaded successfully!");
    }


    // Close audio engine states
    SA_CloseAudioEngine_I();


    // set control flag enabled to 0 even it was 0 or not, just reset it
    SA_IsControlFlagEnabled_I = 0; // close the flag

    // terminate glfw internal states and terminate it
    glfwTerminate();

    SA_LOG_INFO("SageAura window closed successfully!");
}












void SA_BeginDrawing(void)
{
    // reset the mesh counter of global mesh
    SA_MeshCounterReset_I(GlobalMesh);

    // check either SA_WindowInst_I exists or not
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    
    // clear color of background
    GLH_ClearColor(
        SA_WindowInst_I->color.r,
        SA_WindowInst_I->color.g,
        SA_WindowInst_I->color.b
    );
}



void SA_EndDrawing(void)
{
    // check either SA_WindowInst_I exists or not
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);

    // flush the batch
    SA_FlushBatch();


    // swap window buffers
    glfwSwapBuffers(SA_WindowInst_I->handle);

    // reset global mesh counter
    SA_MeshCounterReset_I(GlobalMesh);

    // set fps, convert FPS into delay in ms.
    SA_Delay((int)(1000.0 / SA_WindowInst_I->fps));
}









void SA_SetBackgroundColor(SA_Colori color)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    SA_Color fcolor;
    fcolor = SA_NormalizeColorEx(color);

    SA_WindowInst_I->color.r = fcolor.r;
    SA_WindowInst_I->color.g = fcolor.g;
    SA_WindowInst_I->color.b = fcolor.b;

    SA_LOG_INFO("new background color applied successfully! where Color: (R: %f; G: %f; B: %f)", 
        fcolor.r, fcolor.g, fcolor.b);
}



void SA_SetTargetFPS(int fps)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    
    SA_WindowInst_I->fps = fps;
}






float SA_GetDeltaTime()
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, 0.0f);

    return SA_GetDeltaFromTimer(SA_WindowInst_I->timer);
}





void SA_EnableFullScreen()
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    SA_CHECK_WINDOW_I(SA_WindowInst_I->handle, SA_MSG_GLFW_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    static int fullscreen = 0;
    // static int wx, wy;
    fullscreen = !fullscreen;
    if (fullscreen)
    {
        // glfwGetWindowPos(SA_WindowInst_I->handle, &wx, &wy);
        
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(SA_WindowInst_I->handle, monitor,
                             0, 0,
                             mode->width, mode->height,
                             mode->refreshRate);
    }

}




SA_API void SA_DisableFullScreen() {
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    SA_CHECK_WINDOW_I(SA_WindowInst_I->handle, SA_MSG_GLFW_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);

    
    glfwSetWindowMonitor(SA_WindowInst_I->handle, NULL,
                         SA_WindowInst_I->x,
                         SA_WindowInst_I->y,
                         SA_WindowInst_I->width,
                         SA_WindowInst_I->height, 0);
    
}






void SA_GetMousePosition(double *x, double *y)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    SA_CHECK_WINDOW_I(SA_WindowInst_I->handle, SA_MSG_GLFW_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);


    glfwGetCursorPos(SA_WindowInst_I->handle, x, y);

}





SA_Sizei SA_GetWindowSize(void)
{

    SA_Sizei size;
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, size);


    size.width = SA_WindowInst_I->width;
    size.height = SA_WindowInst_I->height;

    return size;
}


int SA_GetWindowWidth(void)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, -1);

    return SA_WindowInst_I->width;
}


int SA_GetWindowHeight(void)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, -1);

    return SA_WindowInst_I->height;
}





const char* SA_GetWindowTitle(const char* title)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, "ERROR");
    SA_CHECK_WINDOW_I(SA_WindowInst_I->handle, SA_MSG_WINDOW_NOT_FOUND_I, "ERROR");

    return glfwGetWindowTitle(SA_WindowInst_I->handle);
}


void SA_SetWindowTitle(const char* title)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    SA_CHECK_WINDOW_I(SA_WindowInst_I->handle, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);

    glfwSetWindowTitle(SA_WindowInst_I->handle, title);
}





SA_Bool SA_IsFullScreen(void)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_NO);
    SA_CHECK_WINDOW_I(SA_WindowInst_I->handle, SA_MSG_WINDOW_NOT_FOUND_I, SA_NO);

    return glfwGetWindowMonitor(SA_WindowInst_I->handle) != NULL;
}







/*
    =====================================================================================
    THIS DATA IS NOT IMPORTANT MUCH, IT STATE ABOUT INTERNAL STATES, HISTORY ACROSS VERSIONS, ETC.
    =====================================================================================

    LINES:
        3179 LOC total in something v5.0.1 - v5.0.2




*/