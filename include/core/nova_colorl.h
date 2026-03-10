/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/


#pragma once


#include "nova_types.h"
#include "nova_algo.h"

#include <stdio.h>
#include <string.h>




#define NOVA_COLOR_API    static inline




NOVA_COLOR_API
nova_Colori nova_ColorFromHex(const char *hex)
{
    nova_Colori color = {0,0,0,255};
    unsigned int value = 0;

    if (hex[0] == '#') hex++;

    sscanf(hex, "%x", &value);

    if (strlen(hex) <= 6) {
        color.r = (value >> 16) & 0xFF;
        color.g = (value >> 8)  & 0xFF;
        color.b = value & 0xFF;
    } else {
        color.r = (value >> 24) & 0xFF;
        color.g = (value >> 16) & 0xFF;
        color.b = (value >> 8)  & 0xFF;
        color.a = value & 0xFF;
    }

    return color;
}

/* colors */

#define NOVA_RGBA(r, g, b, a)     ((nova_Colori){(r), (g), (b), (a)})
#define NOVA_RGB(r, g, b)         NOVA_RGBA((r), (g), (b), NOVA_COLOR_MAX_OPACITY)




// basic colors

#define NOVA_COLOR_RED                NOVA_RGB(255, 0, 0)
#define NOVA_COLOR_BLUE               NOVA_RGB(0, 0, 255)
#define NOVA_COLOR_WHITE              NOVA_RGB(255, 255, 255)
#define NOVA_COLOR_BLACK              NOVA_RGB(0, 0, 0)
#define NOVA_COLOR_GREEN              NOVA_RGB(0, 128, 0)

// sage colors

#define NOVA_COLOR_NOVAGE_GREEN         NOVA_RGB(188, 203, 184)

// neon

#define NOVA_COLOR_NEON_GREEN         NOVA_RGB(57, 255, 20)

// other colors


#define NOVA_COLOR_GRAY               NOVA_RGB(128, 128, 128)
#define NOVA_COLOR_GREY               NOVA_RGB(128, 128, 128)
#define NOVA_COLOR_GREY_COOL          NOVA_RGB(108, 117, 125)
#define NOVA_COLOR_GRAY_COOL          NOVA_RGB(108, 117, 125)
#define NOVA_COLOR_DARK_GREY          NOVA_RGB(169, 169, 169)
#define NOVA_COLOR_DARK_GRAY          NOVA_RGB(169, 169, 169)


#define NOVA_COLOR_LIME               NOVA_RGB(0, 255, 0)

#define NOVA_COLOR_ORANGE             NOVA_RGB(255, 165, 0, 255)
#define NOVA_COLOR_SLATE_DARK         NOVA_RGB(44, 62, 80)
#define NOVA_COLOR_CANDY_APPLE_RED    NOVA_RGB(255, 8, 0)
#define NOVA_COLOR_ELECTRIC_BLUE      NOVA_RGB(125, 249, 255)
#define NOVA_COLOR_VIVID_VIOLET       NOVA_RGB(159, 0, 255)
#define NOVA_COLOR_GOLDEN_YELLOW      NOVA_RGB(255, 223, 0)
#define NOVA_COLOR_TERRACOTTA         NOVA_RGB(226, 114, 91)
#define NOVA_COLOR_MIDNIGHT_BLUE      NOVA_RGB(25, 25, 112)
#define NOVA_COLOR_OLIVE_DRAB         NOVA_RGB(107, 142, 35)
#define NOVA_COLOR_NOVAND_STONE         NOVA_RGB(194, 178, 128)
#define NOVA_COLOR_COTTON_CANDY       NOVA_RGB(255, 182, 193)
#define NOVA_COLOR_BABY_BLUE          NOVA_RGB(137, 207, 240)
#define NOVA_COLOR_MINT_CREAM         NOVA_RGB(245, 255, 250)
#define NOVA_COLOR_LAVENDER           NOVA_RGB(230, 230, 250)
#define NOVA_COLOR_PEACH_PUFF         NOVA_RGB(255, 218, 185)
#define NOVA_COLOR_MAUVE              NOVA_RGB(224, 176, 255)

#define NOVA_COLOR_AQUA               NOVA_RGB(0, 255, 255)
#define NOVA_COLOR_CORN_FLOWER_BLUE   NOVA_RGB(100, 149, 237)
#define NOVA_COLOR_ALICE_BLUE         NOVA_RGB(240, 248, 255)
#define NOVA_COLOR_ANTIQUE_WHITE      NOVA_RGB(250, 235, 215)
#define NOVA_COLOR_AQUA_MARINE        NOVA_RGB(127, 255, 212)
#define NOVA_COLOR_AZURE              NOVA_RGB(240, 255, 255)
#define NOVA_COLOR_BEIGE              NOVA_RGB(245, 245, 220)
#define NOVA_COLOR_BISQUE             NOVA_RGB(255, 228, 196)
#define NOVA_COLOR_BLANCHEDALMOND     NOVA_RGB(255, 235, 205)
#define NOVA_COLOR_BLUEVIOLET         NOVA_RGB(138, 43, 226)
#define NOVA_COLOR_BROWN              NOVA_RGB(165, 42, 42)
#define NOVA_COLOR_BURLYWOOD          NOVA_RGB(222, 184, 135)
#define NOVA_COLOR_CADET_BLUE         NOVA_RGB(95, 158, 160)
#define NOVA_COLOR_CHARTREUSE         NOVA_RGB(127, 255, 0)
#define NOVA_COLOR_CHOCOLATE          NOVA_RGB(210, 105, 30)
#define NOVA_COLOR_CORAL              NOVA_RGB(255, 127, 80)
#define NOVA_COLOR_CORNSILK           NOVA_RGB(255, 248, 220)
#define NOVA_COLOR_CRIMSON            NOVA_RGB(220, 20, 60)
#define NOVA_COLOR_CYAN               NOVA_RGB(0, 255, 255)
#define NOVA_COLOR_DARKBLUE           NOVA_RGB(0, 0, 139)
#define NOVA_COLOR_DARKCYAN           NOVA_RGB(0, 139, 139)
#define NOVA_COLOR_DARKGOLDENROD      NOVA_RGB(184, 134, 11)
#define NOVA_COLOR_TEAL               NOVA_RGB(0, 128, 128)
#define NOVA_COLOR_VIOLET             NOVA_RGB(238, 130, 238)
#define NOVA_COLOR_WHITESMOKE         NOVA_RGB(245, 245, 245)
#define NOVA_COLOR_YELLOW             NOVA_RGB(255, 255, 0)
#define NOVA_COLOR_TAN                NOVA_RGB(210, 180, 140)
#define NOVA_COLOR_SNOW               NOVA_RGB(255, 250, 250)
#define NOVA_COLOR_DEEPSKYBLUE        NOVA_RGB(0, 191, 255)
#define NOVA_COLOR_SILVER             NOVA_RGB(192, 192, 192)
#define NOVA_COLOR_ROYALBLUE          NOVA_RGB(65, 105, 225)
#define NOVA_COLOR_INDIGO             NOVA_RGB(75, 0, 130)
#define NOVA_COLOR_MAROON             NOVA_RGB(128, 0, 0)
#define NOVA_COLOR_NAVY               NOVA_RGB(0, 0, 128)






#define NOVA_RED                      NOVA_COLOR_RED
#define NOVA_LIME                     NOVA_COLOR_LIME
#define NOVA_BLUE                     NOVA_COLOR_BLUE
#define NOVA_WHITE                    NOVA_COLOR_WHITE
#define NOVA_BLACK                    NOVA_COLOR_BLACK
#define NOVA_GREEN                    NOVA_COLOR_GREEN
#define NOVA_ORANGE                   NOVA_COLOR_ORANGE

#define NOVA_GRAY                     NOVA_COLOR_GRAY
#define NOVA_GREY                     NOVA_COLOR_GREY // both are same just english difference use whatever you want
#define NOVA_GREY_COOL                NOVA_COLOR_GREY_COOL
#define NOVA_GRAY_COOL                NOVA_COLOR_GRAY_COOL
#define NOVA_DARK_GREY                NOVA_COLOR_DARK_GREY
#define NOVA_DARK_GRAY                NOVA_COLOR_DARK_GRAY



#define NOVA_SLATE_DARK               NOVA_COLOR_SLATE_DARK
#define NOVA_CANDY_APPLE_RED          NOVA_COLOR_CANDY_APPLE_RED





#define NOVA_ELECTRIC_BLUE            NOVA_COLOR_ELECTRIC_BLUE
#define NOVA_NEON_GREEN               NOVA_COLOR_NEON_GREEN
#define NOVA_VIVID_VIOLET             NOVA_COLOR_VIVID_VIOLET
#define NOVA_GOLDEN_YELLOW            NOVA_COLOR_GOLDEN_YELLOW
#define NOVA_NOVAGE_GREEN               NOVA_COLOR_NOVAGE_GREEN
#define NOVA_TERRACOTTA               NOVA_COLOR_TERRACOTTA
#define NOVA_MIDNIGHT_BLUE            NOVA_COLOR_MIDNIGHT_BLUE
#define NOVA_OLIVE_DRAB               NOVA_COLOR_OLIVE_DRAB
#define NOVA_NOVAND_STONE               NOVA_COLOR_NOVAND_STONE
#define NOVA_COTTON_CANDY             NOVA_COLOR_COTTON_CANDY
#define NOVA_BABY_BLUE                NOVA_COLOR_BABY_BLUE
#define NOVA_MINT_CREAM               NOVA_COLOR_MINT_CREAM
#define NOVA_LAVENDER                 NOVA_COLOR_LAVENDER
#define NOVA_PEACH_PUFF               NOVA_COLOR_PEACH_PUFF
#define NOVA_MAUVE                    NOVA_COLOR_MAUVE






#define NOVA_AQUA                     NOVA_COLOR_AQUA
#define NOVA_CORN_FLOWER_BLUE         NOVA_COLOR_CORN_FLOWER_BLUE
#define NOVA_ALICE_BLUE               NOVA_COLOR_ALICE_BLUE
#define NOVA_ANTIQUE_WHITE            NOVA_COLOR_ANTIQUE_WHITE
#define NOVA_AQUA_MARINE              NOVA_COLOR_AQUA_MARINE
#define NOVA_AZURE                    NOVA_COLOR_AZURE
#define NOVA_BEIGE                    NOVA_COLOR_BEIGE
#define NOVA_BISQUE                   NOVA_COLOR_BISQUE
#define NOVA_BLANCHEDALMOND           NOVA_COLOR_BLANCHEDALMOND
#define NOVA_BLUEVIOLET               NOVA_COLOR_BLUEVIOLET
#define NOVA_BROWN                    NOVA_COLOR_BROWN
#define NOVA_BURLYWOOD                NOVA_COLOR_BURLYWOOD
#define NOVA_CADET_BLUE               NOVA_COLOR_CADET_BLUE
#define NOVA_CHARTREUSE               NOVA_COLOR_CHARTREUSE
#define NOVA_CHOCOLATE                NOVA_COLOR_CHOCOLATE
#define NOVA_CORAL                    NOVA_COLOR_CORAL
#define NOVA_CORNSILK                 NOVA_COLOR_CORNSILK
#define NOVA_CRIMSON                  NOVA_COLOR_CRIMSON
#define NOVA_CYAN                     NOVA_COLOR_CYAN
#define NOVA_DARKBLUE                 NOVA_COLOR_DARKBLUE
#define NOVA_DARKCYAN                 NOVA_COLOR_DARKCYAN
#define NOVA_DARKGOLDENROD            NOVA_COLOR_DARKGOLDENROD
#define NOVA_TEAL                     NOVA_COLOR_TEAL
#define NOVA_VIOLET                   NOVA_COLOR_VIOLET
#define NOVA_WHITESMOKE               NOVA_COLOR_WHITESMOKE
#define NOVA_YELLOW                   NOVA_COLOR_YELLOW
#define NOVA_TAN                      NOVA_COLOR_TAN
#define NOVA_SNOW                     NOVA_COLOR_SNOW
#define NOVA_DEEPSKYBLUE              NOVA_COLOR_DEEPSKYBLUE
#define NOVA_SILVER                   NOVA_COLOR_SILVER
#define NOVA_ROYALBLUE                NOVA_COLOR_ROYALBLUE
#define NOVA_INDIGO                   NOVA_COLOR_INDIGO
#define NOVA_MAROON                   NOVA_COLOR_MAROON
#define NOVA_NAVY                     NOVA_COLOR_NAVY


