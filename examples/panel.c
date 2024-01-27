#include <panel.h>
#include <string.h>
#include <stdlib.h>

typedef struct _PANEL_DATA {
    int x, y, w, h;
    char label[80];
    int label_color;
    PANEL *next;
    int hide;
} PANEL_DATA;

#define NLINES 10
#define NCOLS  40

void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(
    WINDOW *win,
    int starty,
    int startx,
    int width,
    char* string,
    chtype color
);
void set_user_ptrs(PANEL **panels, int n);

int main() {
    WINDOW *my_wins[3];
    PANEL  *my_panels[3];
    PANEL_DATA *top;
    PANEL *stack_top;
    WINDOW *temp_win, *old_win;
    int ch;
    int newx, newy, neww, newh;
    int size = FALSE, move = FALSE;

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    init_wins(my_wins, 3);

    my_panels[0] = new_panel(my_wins[0]);
    my_panels[1] = new_panel(my_wins[1]);
    my_panels[2] = new_panel(my_wins[2]);

    set_user_ptrs(my_panels, 3);

    // my_panels[0].hide = FALSE;
    // my_panels[1].hide = FALSE;
    // my_panels[2].hide = FALSE;
    
    update_panels();

    attron(COLOR_PAIR(4));
    mvprintw(LINES - 4, 0, "Show or Hide a window with 'a'(First window) "
        "'b'(Second window) 'c'(Third window)");
    mvprintw(LINES - 3, 0, "Use 'm' for moving, 'r' for resizing");
    mvprintw(LINES - 2, 0, "Use TAB to browse throgh the windows (F1 to Exit)");
    attroff(COLOR_PAIR(4));
    doupdate();

    stack_top = my_panels[2];
    top = (PANEL_DATA *) panel_userptr(stack_top);
    newx = top->x;
    newy = top->y;
    neww = top->w;
    newh = top->h;

    PANEL_DATA *temp;

    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case 'a':
                temp = (PANEL_DATA *) panel_userptr(my_panels[0]);
                if (temp->hide == FALSE) {
                    hide_panel(my_panels[0]);
                    temp->hide = TRUE;
                } else {
                    show_panel(my_panels[0]);
                    temp->hide = FALSE;
                }
                break;
            case 'b':
                temp = (PANEL_DATA *) panel_userptr(my_panels[1]);
                if (temp->hide == FALSE) {
                    hide_panel(my_panels[1]);
                    temp->hide = TRUE;
                } else {
                    show_panel(my_panels[1]);
                    temp->hide = FALSE;
                }
                break;
            case 'c':
                temp = (PANEL_DATA *) panel_userptr(my_panels[2]);
                if (temp->hide == FALSE) {
                    hide_panel(my_panels[2]);
                    temp->hide = TRUE;
                } else {
                    show_panel(my_panels[2]);
                    temp->hide = FALSE;
                }
                break;
            case 9:
                top = (PANEL_DATA *) panel_userptr(stack_top);
                top_panel(top->next);
                stack_top = top->next;
                top = (PANEL_DATA *) panel_userptr(stack_top);
                newx = top->x;
                newy = top->y;
                neww = top->w;
                newh = top->h;
                break;
            case 'r':
                size = TRUE;
                attron(COLOR_PAIR(4));
                mvprintw(LINES - 4, 0, "Entered Resizing: "
                    "Use Arrow Keys to resize and press <ENTER> to end resizing"
                );
                refresh();
                attroff(COLOR_PAIR(4));
                break;
            case 'm':
                move = TRUE;
                attron(COLOR_PAIR(4));
                mvprintw(LINES - 4, 0, "Entered Moving: "
                    "Use Arrow Keys to move and press <ENTER> to end moving"
                );
                refresh();
                attroff(COLOR_PAIR(4));
                break;
            case KEY_LEFT:
                if (size == TRUE) {
                    --newx;
                    ++neww;
                    old_win = panel_window(stack_top);
                    temp_win = newwin(newh, neww, newy, newx);
                    replace_panel(stack_top, temp_win);
                    win_show(temp_win, top->label, top->label_color);
                    delwin(old_win);
                }
                if (move == TRUE) {
                    --newx;
                    move_panel(stack_top, newy, newx);
                }
                break;
            case KEY_RIGHT:
                if (size == TRUE) {
                    ++newx;
                    --neww;
                    old_win = panel_window(stack_top);
                    temp_win = newwin(newh, neww, newy, newx);
                    replace_panel(stack_top, temp_win);
                    win_show(temp_win, top->label, top->label_color);
                    delwin(old_win);
                }
                if (move == TRUE) {
                    ++newx;
                    move_panel(stack_top, newy, newx);
                }
                break;
            case KEY_UP:
                if (size == TRUE) {
                    --newy;
                    ++newh;
                    old_win = panel_window(stack_top);
                    temp_win = newwin(newh, neww, newy, newx);
                    replace_panel(stack_top, temp_win);
                    win_show(temp_win, top->label, top->label_color);
                    delwin(old_win);
                }
                if (move == TRUE) {
                    --newy;
                    move_panel(stack_top, newy, newx);
                }
                break;
            case KEY_DOWN:
                if (size == TRUE) {
                    ++newy;
                    --newh;
                    old_win = panel_window(stack_top);
                    temp_win = newwin(newh, neww, newy, newx);
                    replace_panel(stack_top, temp_win);
                    win_show(temp_win, top->label, top->label_color);
                    delwin(old_win);
                }
                if (move == TRUE) {
                    ++newy;
                    move_panel(stack_top, newy, newx);
                }
                break;
            case -1:
                
            case 10:
                move(LINES - 4, 0);
                clrtoeol();
                refresh();
                if (size == TRUE) {
                    size = FALSE;
                }
                if (move == TRUE) {
                    move = FALSE;
                }
                break;
        }
        attron(COLOR_PAIR(4));
        mvprintw(LINES - 3, 0, "Use 'm' for moving, 'r' for resizing");
        mvprintw(LINES - 2, 0, "Use TAB to browse through the windows (F1 to Exit)");
        attroff(COLOR_PAIR(4));
        refresh();
        update_panels();
        doupdate();
    }
    endwin();
    return 0;
}

void init_wins(WINDOW **wins, int n) {
    int x, y, i;
    char label[80];

    y = 2;
    x = 10;
    for (i = 0; i < n; ++i) {
        wins[i] = newwin(NLINES, NCOLS, y, x);
        sprintf(label, "Window Number %d", i + 1);
        win_show(wins[i], label, i + 1);
        y += 3;
        x += 7;
    }
}

void set_user_ptrs(PANEL **panels, int n) {
    PANEL_DATA *ptrs;
    WINDOW *win;
    int x, y, w, h, i;
    char temp[80];

    ptrs = (PANEL_DATA *) calloc(n, sizeof(PANEL_DATA));

    for (i = 0; i < n; ++i) {
        win = panel_window(panels[i]);
        getbegyx(win, y, x);
        getmaxyx(win, h, w);
        ptrs[i].x = x;
        ptrs[i].y = y;
        ptrs[i].w = w;
        ptrs[i].h = h;
        ptrs[i].hide = FALSE;
        sprintf(temp, "Window Number %d", i + 1);
        strcpy(ptrs[i].label, temp);
        ptrs[i].label_color = i + 1;
        if (i + 1 == n) {
            ptrs[i].next = panels[0];
        } else {
            ptrs[i].next = panels[i + 1];
        }
        set_panel_userptr(panels[i], &ptrs[i]);
    }
}

void win_show(WINDOW *win, char *label, int label_color) {
    int startx, starty, height, width;

    getbegyx(win, starty, startx);
    getmaxyx(win, height, width);

    box(win, 0, 0);
    mvwaddch(win, 2, 0, ACS_LTEE);
    mvwhline(win, 2, 1, ACS_HLINE, width - 2);
    mvwaddch(win, 2, width - 1, ACS_RTEE);

    print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void print_in_middle(
    WINDOW *win,
    int starty,
    int startx,
    int width,
    char *string,
    chtype color
) {
    int length, x, y;
    float temp;

    if (win == NULL) {
        win = stdscr;
    }
    getyx(win, y, x);
    if (startx != 0) {
        x = startx;
    }
    if (starty != 0) {
        y = starty;
    }
    if (width == 0) {
        width = 80;
    }

    length = strlen(string);
    temp = (width - length) / 2;
    x = startx + (int) temp;
    wattron(win, color);
    mvwprintw(win, y, x, "%s", string);
    wattroff(win, color);
    refresh();
}





