/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/




#pragma once





typedef enum {
    NOVA_WIDGET_BUTTON,
    NOVA_WIDGET_TEXT
} nova_WidgetType;



typedef struct nova_Widget {
    nova_WidgetType type;
} nova_Widget;