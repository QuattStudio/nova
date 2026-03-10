/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#include "nova_core.h"
#include "glh.h"
#include "nova_inc.h"



#include <stdlib.h>






#ifdef _WIN32
    #include <windows.h>
#elif defined(__unix__) || defined(__APPLE__) || defined(_POSIX_C_SOURCE)
    #include <time.h>      // for nanosleep (best precision)
    #include <unistd.h>    // fallback usleep
#endif

void nova_Delay(int ms)
{
    if (ms <= 0) return;   // ignore negative or zero

#ifdef _WIN32
    Sleep((DWORD)ms);      // Windows: milliseconds
#else
    // POSIX (Linux, macOS, etc.)
    #if _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec  = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000000L;
        nanosleep(&ts, NULL);
    #else
        usleep((useconds_t)ms * 1000);   // microseconds
    #endif
#endif
}




nova_Mesh* nova_CreateMesh_I(nova_Uint VAO, nova_Uint VBO, nova_Uint EBO)
{
    nova_Mesh* mesh = NOVA_MALLOC(nova_Mesh);
    if (!mesh) return NULL;

    mesh->VAO = VAO;
    mesh->VBO = VBO;
    mesh->EBO = EBO;
    mesh->VertexCount = 0;
    mesh->IndexCount = 0;

    return mesh;
}




void nova_MeshCounterReset_I(nova_Mesh* mesh)
{
    if (NOVA_NOT mesh) {
        NOVA_LOG_WARN("Nothing provided to reset in mesh counter reset function!");
        return;
    }

    mesh->VertexCount = 0;
    mesh->IndexCount = 0;
}





void nova_DestroyMesh_I(nova_Mesh* mesh)
{
    if (NOVA_NOT mesh) {
        NOVA_LOG_WARN("No mesh provided for destruction!");
        return;
    }


    GLH_DelVAO(&mesh->VAO, 1);
    GLH_DelBuffers(&mesh->VBO, 1);
    GLH_DelBuffers(&mesh->EBO, 1);

    NOVA_LOG_INFO("Mesh Destroyed succesfully!");

    free(mesh);

    mesh = NULL;
}






#ifdef _WIN32

nova_Uint32 nova_GetTicks(void)
{
    return GetTickCount();
}

#else
#include <time.h>

nova_Uint32 nova_GetTicks(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}

#endif





nova_Timer* nova_StartTimer(void)
{
    nova_Timer* timer = NOVA_MALLOC(nova_Timer);
    
    if (NOVA_NOT timer) {
        NOVA_LOG_WARN("Timer memory allocation failed!");
        return NULL;
    }

    nova_Uint32 now = nova_GetTicks();
    timer->time.start = now;
    timer->time.last = now;
    timer->time.current = now;
    timer->time.delta = 0.0f;

    return timer;
}










float nova_GetDeltaFromTimer(nova_Timer *timer)
{
    if (NOVA_NOT timer) {
        NOVA_LOG_WARN("Timer not found!");
        return 0;
    }

    timer->time.current = nova_GetTicks();
    timer->time.delta = (timer->time.current - timer->time.last) / 1000.0f;
    timer->time.last = timer->time.current;
    if (timer->time.delta > 0.05f)  timer->time.delta = 0.05f;

    return timer->time.delta;
}



void nova_StopTimer(nova_Timer* timer)
{
    if (NOVA_NOT timer) {
        NOVA_LOG_INFO("Timer stop successfully!");
        return;
    }

    free(timer);
    timer = NULL;
}




float nova_GetElapsed(nova_Timer* timer)
{
    if (NOVA_NOT timer) {
        NOVA_LOG_WARN("No timer provided in elapsed function!");
        return 0.0f;
    }
    return (nova_GetTicks() - timer->time.start) / 1000.0f;
}



void nova_ApplyGLFWWindowHint_I(nova_Uint flags)
{
    if (flags & NOVA_FLAG_WINDOW_RESIZABLE) {
        NOVA_LOG_INFO("Flag type [window resizable] setted on window!");
        glfwWindowHint(GLFW_RESIZABLE, NOVA_YES);
    }

    if (flags & NOVA_FLAG_WINDOW_BORDERLESS) {
        NOVA_LOG_INFO("Flag type [window border-less] setted on window!");
        glfwWindowHint(GLFW_DECORATED, NOVA_NO);
    }

    if (flags & NOVA_FLAG_WINDOW_MAXIMIZED) {
        NOVA_LOG_INFO("Flag type [window maximized] setted on window!");
        glfwWindowHint(GLFW_MAXIMIZED, NOVA_YES);
    }

    if (flags & NOVA_FLAG_WINDOW_FULLSCREEN) {
        NOVA_LOG_INFO("Flag type [window fullscreen] setted on window!");
        // glfwWindowHint(GLFW_FULL, NOVA_NO);
    }
    
}