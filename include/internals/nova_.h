/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/







#pragma once






#include "nova_inc.h"
#include "core/nova_core.h"
#include "core/nova_types.h"
#include "widgets/nova_widget.h"



/* macros */

#define NOVA_MAX_WIDGETS  0xffff


/* struct definations */

typedef struct nova_Mesh    nova_Mesh;


// structs

struct nova_App {

    // window rect
    int x;
    int y;
    int width;
    int height;

    // window handle
    GLFWwindow* handle;


    // window background color
    struct {
        float r, g, b;
    } color;


    // window mesh
    nova_Mesh* mesh;

    // window event callback
    nova_EventCallback callback;

    // window timer
    nova_Timer* timer;

    // widgets list
    nova_Widget* widgets[NOVA_MAX_WIDGETS];

    int widgetCount;

    int flags;
    int fps;


    // next attached window
    struct nova_App* branch;
};



