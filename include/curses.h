#pragma once

#ifdef EMSCRIPTEN

#include <curses-original.h>

#include <emscripten.h>

int webcurses_wgetch(WINDOW* window) {
    fprintf(stderr, "Wrapper");
    
#ifdef EMSCRIPTEN
    emscripten_sleep(100);
#endif
    return 93;

    return wgetch(window);
}

#define wgetch(win) webcurses_wgetch(win)

#endif