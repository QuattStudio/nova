/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once



#include "nova_common.h"
#include "nova_types.h"
#include "nova_platforms.h"


typedef struct nova_Mesh    nova_Mesh;
typedef struct nova_Vertex  nova_Vertex;

/////// /////////////// /////////////// ////////////////// ///////////////

NOVA_API void nova_Delay(int ms);
nova_Mesh* nova_CreateMesh_I(nova_Uint VAO, nova_Uint VBO, nova_Uint EBO);
void nova_DestroyMesh_I(nova_Mesh* mesh);

void nova_MeshCounterReset_I(nova_Mesh* mesh);




void nova_ApplyGLFWWindowHint_I(nova_Uint flags);



// typedefs struct

typedef struct nova_Mesh {
    nova_Uint VAO;
    nova_Uint VBO;
    nova_Uint EBO;

    int IndexCount;
    int VertexCount;
} nova_Mesh;




typedef struct nova_Vertex {
    float x, y;
    float r, g, b, a;
    float u, v;
} nova_Vertex;





typedef struct nova_Timer {
    struct {
        nova_Uint32 start;
        nova_Uint32 last;
        nova_Uint32 current;
        float delta;
    } time;
} nova_Timer;



NOVA_API nova_Uint32 nova_GetTicks(void);

NOVA_API nova_Timer* nova_StartTimer(void);

NOVA_API void nova_StopTimer(nova_Timer* timer);
NOVA_API float nova_GetDeltaFromTimer(nova_Timer *timer);
NOVA_API float nova_GetElapsed(nova_Timer* timer);








typedef enum {
    NOVA_FLAG_NONE = 0,
    NOVA_FLAG_WINDOW_MAXIMIZED = (1 << 0),
    NOVA_FLAG_WINDOW_FULLSCREEN = (1 << 1),
    NOVA_FLAG_WINDOW_BORDERLESS = (1 << 2),
    NOVA_FLAG_WINDOW_RESIZABLE = (1 << 3),

    NOVA_FLAG_ENABLE_CONTROL = (1 << 4),
} NOVA_InitFlags_I;




#define NOVA_FLAG_MAXIMIZED   NOVA_FLAG_WINDOW_MAXIMIZED
#define NOVA_FLAG_BORDERLESS  NOVA_FLAG_WINDOW_BORDERLESS
#define NOVA_FLAG_RESIZABLE   NOVA_FLAG_WINDOW_RESIZABLE


#define NOVA_MAXIMIZED        NOVA_FLAG_MAXIMIZED
#define NOVA_BORDERLESS       NOVA_FLAG_BORDERLESS
#define NOVA_RESIZABLE        NOVA_FLAG_RESIZABLE


// exceptions types

#define NOVA_RET_TYPE_NONE_I


#define NOVA_CHECK_WINDOW_I(window, msg, retType)\
    if (!window) {\
        NOVA_LOG_ERROR(msg);\
        return retType;\
    }



// exceptions msg

#define NOVA_MSG_WINDOW_NOT_FOUND_I    "Nova Window not found!"
#define NOVA_MSG_GLFW_WINDOW_NOT_FOUND_I    "GLFW Window not found!"