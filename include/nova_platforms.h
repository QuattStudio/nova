/*
    nova Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the nova Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once

/* Allow forcing static build: */
#ifdef NOVA_STATIC
    #define NOVA_API
#else

/* Windows */
#if defined(_WIN32) || defined(__CYGWIN__)
// #   include <windows.h>
    #ifdef NOVA_BUILD        /* defined when building the DLL */
        #define NOVA_API __declspec(dllexport)
    #else
        #define NOVA_API __declspec(dllimport)
    #endif

/* POSIX (GCC/Clang) */
#else
    #if __GNUC__ >= 4
        #define NOVA_API __attribute__((visibility("default")))
    #else
        #define NOVA_API
    #endif
#endif

#endif /* NOVA_STATIC */



















