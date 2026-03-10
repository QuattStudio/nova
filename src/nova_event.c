/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/


#include "nova_event.h"
#include "nova_window.h"

#include <string.h>
#include "nova_.h"
#include "nova_common.h"
#include "nova_inc.h"
#include "nova_renderer.h"



#define NOVA_MAX_EVENTS 256

static nova_Event eventQueue[NOVA_MAX_EVENTS];
static int eventCount = 0;










// ====================== CONTINUOUS INPUT STATE ======================
static nova_Bool keyDown[NOVA_KEY_LAST + 1]       = { NOVA_FALSE };
static nova_Bool keyPressed[NOVA_KEY_LAST + 1]    = { NOVA_FALSE };
static nova_Bool keyReleased[NOVA_KEY_LAST + 1]   = { NOVA_FALSE };

static nova_Bool mouseDown[NOVA_MOUSE_BUTTON_LAST + 1]      = { NOVA_FALSE };
static nova_Bool mousePressed[NOVA_MOUSE_BUTTON_LAST + 1]   = { NOVA_FALSE };
static nova_Bool mouseReleased[NOVA_MOUSE_BUTTON_LAST + 1]  = { NOVA_FALSE };

static double mouseX = 0.0;
static double mouseY = 0.0;
static double mouseWheel = 0.0;











void nova_PushEvent(nova_Event e)
{
    if (eventCount >= NOVA_MAX_EVENTS) return;
    eventQueue[eventCount++] = e;
}









// Call once per frame (after glfwPollEvents())
void nova_UpdateInput(void)
{
    // Reset "this frame only" flags
    memset(keyPressed,   0, sizeof(keyPressed));
    memset(keyReleased,  0, sizeof(keyReleased));
    memset(mousePressed, 0, sizeof(mousePressed));
    memset(mouseReleased,0, sizeof(mouseReleased));
    mouseWheel = 0.0;
}

// NEW: User calls this for every event they poll
void nova_ProcessEvent(const nova_Event* e)
{
    if (!e) return;

    switch (e->type)
    {
        case NOVA_EVENT_KEY_DOWN:
            if (!keyDown[e->key.key]) {
                keyPressed[e->key.key] = NOVA_TRUE;
            }
            keyDown[e->key.key] = NOVA_TRUE;
            break;

        case NOVA_EVENT_KEY_UP:
            if (keyDown[e->key.key]) {
                keyReleased[e->key.key] = NOVA_TRUE;
            }
            keyDown[e->key.key] = NOVA_FALSE;
            break;

        case NOVA_EVENT_MOUSE_BUTTON_DOWN:
            if (!mouseDown[e->mouseButton.button]) {
                mousePressed[e->mouseButton.button] = NOVA_TRUE;
            }
            mouseDown[e->mouseButton.button] = NOVA_TRUE;
            break;

        case NOVA_EVENT_MOUSE_BUTTON_UP:
            if (mouseDown[e->mouseButton.button]) {
                mouseReleased[e->mouseButton.button] = NOVA_TRUE;
            }
            mouseDown[e->mouseButton.button] = NOVA_FALSE;
            break;

        case NOVA_EVENT_MOUSE_MOVE:
            mouseX = e->mouseMove.x;
            mouseY = e->mouseMove.y;
            break;

        case NOVA_EVENT_MOUSE_SCROLL:
            mouseWheel += e->scroll.offset;
            break;

        default:
            break;
    }
}



// ====================== PUBLIC GETTERS (unchanged) ======================
nova_Bool nova_IsKeyDown(nova_Key key)
{
    if (key < 0 || key > NOVA_KEY_LAST) return NOVA_FALSE;
    return keyDown[key];
}

nova_Bool nova_IsKeyPressed(nova_Key key)
{
    if (key < 0 || key > NOVA_KEY_LAST) return NOVA_FALSE;
    return keyPressed[key];
}

nova_Bool nova_IsKeyReleased(nova_Key key)
{
    if (key < 0 || key > NOVA_KEY_LAST) return NOVA_FALSE;
    return keyReleased[key];
}

nova_Bool nova_IsMouseButtonDown(nova_MouseButton button)
{
    if (button < 0 || button > NOVA_MOUSE_BUTTON_LAST) return NOVA_FALSE;
    return mouseDown[button];
}

nova_Bool nova_IsMouseButtonPressed(nova_MouseButton button)
{
    if (button < 0 || button > NOVA_MOUSE_BUTTON_LAST) return NOVA_FALSE;
    return mousePressed[button];
}

nova_Bool nova_IsMouseButtonReleased(nova_MouseButton button)
{
    if (button < 0 || button > NOVA_MOUSE_BUTTON_LAST) return NOVA_FALSE;
    return mouseReleased[button];
}

double nova_GetMouseX(void) { return mouseX; }
double nova_GetMouseY(void) { return mouseY; }
double nova_GetMouseWheel(void) { return mouseWheel; }




int nova_PollEvent(nova_Event* out)
{
    if (eventCount == 0) return 0;

    *out = eventQueue[0];

    for (int i = 1; i < eventCount; i++)
        eventQueue[i - 1] = eventQueue[i];
    
    nova_ProcessEvent(out);

    eventCount--;
    return 1;
}








static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    nova_Event e;

    if (action == GLFW_PRESS) {
        e.type = NOVA_EVENT_KEY_DOWN;
        e.key.key = key;
        nova_PushEvent(e);
    }
    else if (action == GLFW_RELEASE) {
        e.type = NOVA_EVENT_KEY_UP;
        e.key.key = key;
        nova_PushEvent(e);
    }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    nova_Event e;

    if (action == GLFW_PRESS) {
        e.type = NOVA_EVENT_MOUSE_BUTTON_DOWN;
        e.mouseButton.button = button;
        nova_PushEvent(e);
    }
    else if (action == GLFW_RELEASE) {
        e.type = NOVA_EVENT_MOUSE_BUTTON_UP;
        e.mouseButton.button = button;
        nova_PushEvent(e);
    }
}

static void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
    nova_Event e;
    e.type = NOVA_EVENT_MOUSE_MOVE;
    e.mouseMove.x = xpos;
    e.mouseMove.y = ypos;
    nova_PushEvent(e);
}



static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    nova_Event e;
    e.type = NOVA_EVENT_MOUSE_SCROLL;
    e.scroll.offset = yoffset;        // positive = scroll up / away from you
    nova_PushEvent(e);
}





static void window_resize_callback(GLFWwindow* window, int width, int height)
{
    nova_App* app = glfwGetWindowUserPointer(window);
    NOVA_CHECK_WINDOW_I(app, NOVA_MSG_WINDOW_NOT_FOUND_I, NOVA_RET_TYPE_NONE_I);

    app->width = width;
    app->height = height;
    
    
    // if using OpenGL, update viewport too
    glViewport(0, 0, width, height);

    nova_SetProjectionOrtho(0.0f, (float)width, (float)height, 0.0f);
}


void nova_SetWindowEventCallBacks_I(GLFWwindow* window)
{
    glfwSetKeyCallback(window,          key_callback);
    glfwSetCursorPosCallback(window,    cursor_callback);
    glfwSetMouseButtonCallback(window,  mouse_button_callback);
    glfwSetScrollCallback(window,       scroll_callback);
    glfwSetWindowSizeCallback(window,   window_resize_callback);
}

















// ================================================================
// USER EVENT CALLBACK (completely new code)
// ================================================================




void nova_HandleEvents(nova_App *app)
{
    nova_EventCallback callback = app->callback;

    nova_Event event;
    if (NOVA_NOT app) return;
    
    nova_UpdateInput();  // Reset "this frame only" flags at the start of each frame
    
    while (nova_PollEvent(&event)) {
        if (callback != NULL) {
            callback(app, &event);
        }
    }
}









































