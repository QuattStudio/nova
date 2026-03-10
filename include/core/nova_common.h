/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once



#include <stdio.h>
#include <stdlib.h>


#include "nova_types.h"




#define NOVA_LOG_INFO(fmt, ...) \
    printf("[INFO] > " fmt "\n", ##__VA_ARGS__)


#define NOVA_LOG_WARN(fmt, ...) \
    printf("[WARN] > {%s:%d} > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)


#define NOVA_LOG_ERROR(fmt, ...) \
    printf("[ERR] > {%s:%d} > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)


#define NOVA_LOG_CRITICAL(fmt, ...) \
    printf("[CRITICAL] > {%s:%d} > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); exit(1)






#ifndef NOVA_DINOVABLE_VERBOSE_LOGS_I


#define NOVA_LOGV_INFO(fmt, ...) \
    printf("[INFO-V] > " fmt "\n", ##__VA_ARGS__)


#define NOVA_LOGV_WARN(fmt, ...) \
    printf("[WARN-V] > {%s:%d} > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)


#endif

















#define NOVA_COLOR_MAX_OPACITY    (255)
#define NOVA_GL_VERSION_USED      (330)





#define NOVA_NOT  !
#define NOVA_OR   ||
#define NOVA_XOR  ^
#define NOVA_AND  &&

#define NOVA_THEN  ?
#define NOVA_ELSE  :





#define NOVA_MALLOC(type) ((type*)malloc(sizeof(type)))
#define NOVA_MALLOC_N(type, n) ((type*)malloc(sizeof(type * n)))



/* structs macros */

#define NOVA_RECT(x, y, width, height)    ((nova_Rect){(x), (y), (width), (height)})
#define NOVA_RECTF(x, y, width, height)    ((nova_RectF){(x), (y), (width), (height)})
#define NOVA_VEC2(x, y)   ((nova_Vec2){(x), (y)})
#define NOVA_VEC2I(x, y)   ((nova_Vec2i){(x), (y)})



