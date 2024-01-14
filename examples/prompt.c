// gcc prompt.c -lncurses -o ./prompt

#include <curses.h>
#include <string.h>

void read_line(char* buffer, int buf_size) {
    int ch, index = 0;
    memset(buffer, 0, buf_size);

    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) { 
            if (index > 0) {
                index--;
                buffer[index] = '\0';
                printw("\b \b"); // move back, clear space, move back
            }
        } else if(index < buf_size - 1) {
            buffer[index] = ch;
            index++;
            addch(ch);
        }
    }
    buffer[index] = '\0';
}

int main() {
    char str[100];

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    for (;;) {
        printw("> ");
        addch(' ');
        refresh();

        read_line(str, sizeof(str));

        printw("\nAnswer: %s\n", str);
        refresh();

    }

    getch();
    endwin();

    return 0;
}

