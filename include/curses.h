#pragma once

#ifdef EMSCRIPTEN

#include <curses-original.h>

#include <emscripten.h>

static int esc_sequence_started = false;
static int multibyte_sequence_started = false;
static int webcurses_delay = -1;

static int webcurses_wgetch(WINDOW* window) {
    int ch;
    do { 
#ifdef EMSCRIPTEN
    emscripten_sleep(webcurses_delay >= 0 ? webcurses_delay : 10);
#endif
        ch = wgetch(window);

        if (ch == -1) {
            multibyte_sequence_started = false;
            esc_sequence_started = false;
            if (webcurses_delay >= 0) {
                fprintf(stderr, "DEBUG GETCH: -1\n");
                return -1;
            }
            continue;
        }
        if (ch == 27) {
            esc_sequence_started = true;
            fprintf(stderr, "DEBUG GETCH: ESC\n");
            return 27;
        }
        if (!esc_sequence_started) {
            int next_ch;

            wtimeout(window, -1);
            nodelay(window, TRUE);

            next_ch = wgetch(window);
            if (next_ch != -1) {
                ungetch(next_ch);
                multibyte_sequence_started = true;
            }

            wtimeout(window, webcurses_delay);
            nodelay(window, FALSE);
        }
        if (ch != -1) {
            if (multibyte_sequence_started) {
                fprintf(stderr, "DEBUG GETCH: %d (MB char)\n", ch + 128);
                return ch + 128;
            }
            fprintf(stderr, "DEBUG GETCH: %d\n", ch);
            
            return ch;
        }
    } while (true);
}
#define wgetch(win) webcurses_wgetch(win)

static void webcurses_wtimeout (WINDOW * win, int delay) {
    webcurses_delay = delay;
    wtimeout(win, delay);
}
#define wtimeout(win, delay) webcurses_wtimeout(win, delay);

// Rogue requires it
#define _getch() getch()

#endif

