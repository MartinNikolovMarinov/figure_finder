#pragma once

#ifdef FIGURE_FINDER_LIBRARY_SHARED
    /* It's a dynamic library. */
    #ifdef FIGURE_FINDER_LIBRARY_BUILD
        /* Building the library */
        #if defined(_MSC_VER)
            #define FIGURE_FINDER_API_EXPORT __declspec(dllexport)
        #elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
            #define FIGURE_FINDER_API_EXPORT __attribute__((visibility("default")))
        #else
            #define FIGURE_FINDER_API_EXPORT
        #endif
    #else
        /* Using the library */
        #ifdef _WIN32
            #define FIGURE_FINDER_API_EXPORT __declspec(dllimport)
        #else
            #define FIGURE_FINDER_API_EXPORT
        #endif
    #endif
#endif

#ifndef FIGURE_FINDER_API_EXPORT
    /* It's a static library, no need to import/export anything */
    #define FIGURE_FINDER_API_EXPORT
#endif
