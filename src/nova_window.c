/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/


// all main libs
#include "nova_window.h"
#include "nova_common.h"
#include "nova_core.h"
#include "nova_text.h"

#include "nova_event.h"

#include "nova_renderer.h"
#include "nova_audio.h"
#include "nova_inc.h"

#include "nova_algo.h" 


// internals
#define GLH_IMPLEMENTATION
#include "glh.h"


#include "nova_.h"


// C std libs
#include <stdio.h>
#include <stdlib.h>
#include <math.h>






/* internal flags */

// flag to determine either user / developer want contorl in game engine!?
int nova_IsControlFlagEnabled_I = 0;

// internal variables to get known window flags.
static int nova_IsNOVAInit;


// check error state of an object
#define nova_CheckErrState_I(obj, retType, msg)\
    if (NOVA_NOT obj) {\
        nova_CheckIsControlFlagEnabledEx_I(\
            retType,\
            msg\
        );\
    }



/* Functions uses! */
int nova_Start(int flags)
{
    if (flags & NOVA_FLAG_ENABLE_CONTROL)
        nova_IsControlFlagEnabled_I = 1;
    



    // Init GLFW
    int GLFWInitErrState = glfwInit();

    nova_CheckErrState_I(
        GLFWInitErrState,
        NOVA_FALSE,
        "GLFW Initialization failed!"
    )

    NOVA_LOGV_INFO("GLFW Initialization completed!");


    
    /* Setup Gl version */
    GLH_UseGL330Version();
    NOVA_LOGV_INFO("GL Version : %d", NOVA_GL_VERSION_USED);

    nova_OpenAudioEngine_I();


    NOVA_LOG_INFO("Nova Initialization completed!");

    nova_IsNOVAInit = 1;

    return NOVA_TRUE;
}



/* Create Window */
nova_App* nova_StartApp(int width, int height, const char* title, int flags)
{

    if (NOVA_NOT nova_IsNOVAInit) nova_Start(flags);


    nova_ApplyGLFWWindowHint_I(flags);

    if (width < 0 NOVA_OR height < 0) {
        NOVA_LOG_WARN("Size (Width or Height) should not be zero! Size: %dx%d", width, height);
        return NULL;
    }

    // Create GLFW Window 
    GLFWwindow* GLFW_Window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (NOVA_NOT GLFW_Window)
    {
        nova_CheckIsControlFlagEnabledEx_I(
            NULL, 
            "GLFW Window Creation Failed!"
        );
    }


    // allocate memory to window 
    nova_App *app = NOVA_MALLOC(nova_App);
    if (NOVA_NOT app) 
    {
        nova_CheckIsControlFlagEnabledEx_I(
            NULL, 
            "nova Window allocation Failed!"
        );
    }

    glfwMakeContextCurrent(GLFW_Window);


    /* Init renderer */
    nova_InitRenderer_I(app);

    
    nova_SetProjectionOrtho(0.0f, (float)width, (float)height, 0.0f); // Y=0 at top

    int windowX, windowY;
    glfwGetWindowPos(GLFW_Window, &windowX, &windowY);


    // init everything 
    app->handle = GLFW_Window;
    app->flags = 0;
    app->width = width;
    app->height = height;

    app->x = windowX;
    app->y = windowY;

    NOVA_INIT_ARRAY(app->widgets);
    app->widgetCount = 0;



    app->fps = 60;

    // set background color greyish by default!
    app->color.r = 0.13f;
    app->color.g = 0.13f;
    app->color.b = 0.13f;


    // start the timer, so we can use delta time when we want
    app->timer = nova_StartTimer();

    app->callback = NULL;



    glfwSetWindowUserPointer(GLFW_Window, app);

    nova_SetWindowEventCallBacks_I(app->handle);

    
    NOVA_LOGV_INFO("Nova Window successfully Created!");


    return app;
}





int nova_RunWindow(nova_App* app)
{

    // don't play if window not found
    NOVA_CHECK_WINDOW_I(app, NOVA_MSG_WINDOW_NOT_FOUND_I, 0)


    // // poll glfw events
    // glfwPollEvents();

    // update SageAura Input systems
    nova_UpdateInput();


    // needed for run any type of event handling, can be NULL but important to call for event handling
    nova_HandleEvents(app);


    // return glfwWindowShouldClose
    return NOVA_NOT glfwWindowShouldClose(app->handle); 
}




// NOVA_API void nova_StopPlaying(void)
// {
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I->handle, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);  
    
//     glfwSetWindowShouldClose(nova_WindowInst_I->handle, NOVA_YES);
// }





void nova_SetEventTo(nova_App* app, nova_EventCallback callback)
{
    NOVA_CHECK_WINDOW_I(app, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);
    
    app->callback = callback;
}




void nova_CloseWindow(nova_App* app)
{
    // check either nova_WindowInst_I exists or not
    NOVA_CHECK_WINDOW_I(app, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);  




    // destroy window of glfw
    glfwDestroyWindow(app->handle);

    NOVA_LOGV_INFO("GLFW window Destroyed!");

    // stop the timer, to stop the calculation of delta time
    nova_StopTimer(app->timer);


    // free the memory allocation of window
    free(app);


    // clear the default font
    if (nova_DefaultFont_I) {
        nova_UnLoadFont(nova_DefaultFont_I);
        nova_DefaultFont_I = NULL;        
        NOVA_LOG_INFO("Default Font unloaded successfully!");
    }


    NOVA_LOG_INFO("SageAura window closed successfully!");
}








void nova_BeginDrawing(nova_App* app)
{
    // reset the mesh counter of global mesh
    nova_MeshCounterReset_I(app->mesh);

    // check either nova_WindowInst_I exists or not
    NOVA_CHECK_WINDOW_I(app, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);
    
    // clear color of background
    GLH_ClearColor(
        app->color.r,
        app->color.g,
        app->color.b
    );
}







void nova_EndDrawing(nova_App* app)
{
    // check either nova_WindowInst_I exists or not
    NOVA_CHECK_WINDOW_I(app, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);

    // flush the batch
    nova_FlushBatch(app);


    // swap window buffers
    glfwSwapBuffers(app->handle);

    // reset global mesh counter
    nova_MeshCounterReset_I(app->mesh);

    // set fps, convert FPS into delay in ms.
    nova_Delay((int)(1000.0 / app->fps));
}









void nova_Run(nova_App* app)
{
    int anyRunning = 1;

    while (anyRunning)
    {
        anyRunning = 0;

        // 1) Poll events once per frame (important)
        glfwPollEvents();

        // 2) Update global input AFTER event polling
        nova_UpdateInput();

        // 3) Walk the windows and draw each (ensure context is current per-window)
        nova_App* curr = app;
        while (curr != NULL)
        {
            if (nova_RunWindow(curr)) // checks window validity + event handling
            {
                anyRunning = 1;

                // Make this window's GL context current BEFORE any GL calls
                glfwMakeContextCurrent(curr->handle);

                // Optionally set vsync for this context (do once after context is created / first used)
                // glfwSwapInterval(1);

                // // Ensure viewport matches framebuffer size (important for HiDPI)
                int fbw = 0, fbh = 0;
                glfwGetFramebufferSize(curr->handle, &fbw, &fbh);
                if (fbw <= 0 || fbh <= 0) {
                    // debug: print sizes if needed
                    // printf("Warning: fb size for window %p is %dx%d\n", (void*)curr->handle, fbw, fbh);
                } else {
                    glViewport(0, 0, fbw, fbh);
                }

                // Begin + draw + end (Begin/End will use the current context)
                nova_BeginDrawing(curr);
                    // widgets loop goes here: draw widgets using curr as context
                nova_EndDrawing(curr);

                // NOTE: EndDrawing already calls glfwSwapBuffers(app->handle) in your code.
                // If you move swap out of EndDrawing, do it here instead.
            }

            curr = curr->branch;
        }

        // Optional: global frame limiter (do it once per frame, not per-window)
        // nova_Delay((int)(1000.0f / app->fps));
    }

    // Close all windows (cleanup)
    nova_App* walk = app;
    while (walk != NULL)
    {
        nova_App* next = walk->branch;
        nova_CloseWindow(walk);
        walk = next;
    }

    nova_DestroyMesh_I(app->mesh);
    nova_IsControlFlagEnabled_I = 0;
    nova_CloseAudioEngine_I();
    glfwTerminate();
}



// void nova_Run(nova_App* app)
// {
//     int anyRunning = 1;
//     while (anyRunning)
//     {
//         anyRunning = 0;
//         nova_App* curr = app;
//         while (curr != NULL)
//         {
//             if (nova_RunWindow(curr))
//             {
//                 anyRunning = 1;
//                 nova_BeginDrawing(curr);
//                     // widgets loop goes here
//                 nova_EndDrawing(curr);
//             }
//             curr = curr->branch;
//         }
//     }

//     // Close all windows (same as before)
//     nova_App* curr = app;
//     while (curr != NULL)
//     {
//         nova_App* next = curr->branch;
//         nova_CloseWindow(curr);
//         curr = next;
//     }

//     nova_DestroyMesh_I(app->mesh);
//     nova_IsControlFlagEnabled_I = 0;
//     nova_CloseAudioEngine_I();
//     glfwTerminate();
// }




// void nova_Run(nova_App* app)
// {

//     while (nova_RunWindow(app))
//     {
//         nova_BeginDrawing(app);

//             // for (int WidgetsIndex = 0; WidgetsIndex < app->widgetCount; WidgetsIndex++)
//             // {

//             // }

//         nova_EndDrawing(app);
//     }


//     nova_App* curr = app;

//     while (curr != NULL)
//     {
//         nova_App* next = curr->branch;
//         nova_CloseWindow(curr);
//         curr = next;
//     }

//     // destroy mesh of renderer
//     nova_DestroyMesh_I(app->mesh);



//     // set control flag enabled to 0 even it was 0 or not, just reset it
//     nova_IsControlFlagEnabled_I = 0; // close the flag
    
    
//     // Close audio engine states
//     nova_CloseAudioEngine_I();


//     // terminate glfw internal states and terminate it
//     glfwTerminate();
// }







void nova_SetBackgroundColor(nova_App* app, nova_Colori color)
{
    NOVA_CHECK_WINDOW_I(app, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);
    nova_Color fcolor;
    fcolor = nova_NormalizeColorEx(color);

    app->color.r = fcolor.r;
    app->color.g = fcolor.g;
    app->color.b = fcolor.b;

    NOVA_LOG_INFO("new background color applied successfully! where Color: (R: %f; G: %f; B: %f)", 
        fcolor.r, fcolor.g, fcolor.b);
}






void nova_NewApp(nova_App* RootApp, nova_App* app)
{
    RootApp->branch = app;
}






// void nova_EnableFullScreen()
// {
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I->handle, NOVA_MSG_GLFW_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);
//     static int fullscreen = 0;
//     // static int wx, wy;
//     fullscreen = !fullscreen;
//     if (fullscreen)
//     {
//         // glfwGetWindowPos(nova_WindowInst_I->handle, &wx, &wy);
        
//         GLFWmonitor* monitor = glfwGetPrimaryMonitor();
//         const GLFWvidmode* mode = glfwGetVideoMode(monitor);
//         glfwSetWindowMonitor(nova_WindowInst_I->handle, monitor,
//                              0, 0,
//                              mode->width, mode->height,
//                              mode->refreshRate);
//     }

// }




// NOVA_API void nova_DisableFullScreen() {
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I->handle, NOVA_MSG_GLFW_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);

    
//     glfwSetWindowMonitor(nova_WindowInst_I->handle, NULL,
//                          nova_WindowInst_I->x,
//                          nova_WindowInst_I->y,
//                          nova_WindowInst_I->width,
//                          nova_WindowInst_I->height, 0);
    
// }






// void nova_GetMousePosition(double *x, double *y)
// {
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I->handle, NOVA_MSG_GLFW_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);


//     glfwGetCursorPos(nova_WindowInst_I->handle, x, y);

// }





// nova_Sizei nova_GetWindowSize(void)
// {

//     nova_Sizei size;
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I, NOVA_MSG_WINDOW_NOT_FOUND_I, size);


//     size.width = nova_WindowInst_I->width;
//     size.height = nova_WindowInst_I->height;

//     return size;
// }


// int nova_GetWindowWidth(void)
// {
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I, NOVA_MSG_WINDOW_NOT_FOUND_I, -1);

//     return nova_WindowInst_I->width;
// }


// int nova_GetWindowHeight(void)
// {
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I, NOVA_MSG_WINDOW_NOT_FOUND_I, -1);

//     return nova_WindowInst_I->height;
// }





// const char* nova_GetWindowTitle(const char* title)
// {
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I, NOVA_MSG_WINDOW_NOT_FOUND_I, "ERROR");
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I->handle, NOVA_MSG_WINDOW_NOT_FOUND_I, "ERROR");

//     return glfwGetWindowTitle(nova_WindowInst_I->handle);
// }


// void nova_SetWindowTitle(const char* title)
// {
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I->handle, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);

//     glfwSetWindowTitle(nova_WindowInst_I->handle, title);
// }





// nova_Bool nova_IsFullScreen(void)
// {
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_NO);
//     NOVA_CHECK_WINDOW_I(nova_WindowInst_I->handle, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_NO);

//     return glfwGetWindowMonitor(nova_WindowInst_I->handle) != NULL;
// }







/*
    =====================================================================================
    THIS DATA IS NOT IMPORTANT MUCH, IT STATE ABOUT INTERNAL STATES, HISTORY ACROSS VERSIONS, ETC.
    =====================================================================================

    LINES:
        3179 LOC total in something v5.0.1 - v5.0.2




*/