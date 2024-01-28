#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Choice 5",
    "Choice 6",
    "Choice 7",
    "Choice 8",
    "Choice 9",
    "Choice 10",
    "Choice 11",
    "Choice 12",
    "Choice 13",
    "Choice 14",
    "Choice 15",
    "Choice 16",
    "Choice 17",
    "Choice 18",
    "Choice 19",
    "Choice 20",
    "Exit",
    (char *) NULL,
};

void print_in_middle(
    WINDOW *win,
    int starty,
    int startx,
    int width,
    char *string,
    chtype color
);

void func(char *name);

int main() {
    ITEM **my_items;
    int c;
    MENU *my_menu;
    WINDOW *my_menu_win;
    int n_choices, i;

    ITEM *cur_item;

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    // Create items
    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **) calloc(n_choices + 1, sizeof(ITEM *));
    for (i = 0; i < n_choices; ++i) {
        my_items[i] = new_item(choices[i], choices[i]);
        set_item_userptr(my_items[i], func);
    }
    my_items[n_choices] = (ITEM *) NULL;
    item_opts_off(my_items[3], O_SELECTABLE);
    item_opts_off(my_items[6], O_SELECTABLE);

    // Create menu
    my_menu = new_menu((ITEM **) my_items);
    
    set_menu_fore(my_menu, COLOR_PAIR(1) | A_REVERSE);
    set_menu_back(my_menu, COLOR_PAIR(2));
    set_menu_grey(my_menu, COLOR_PAIR(3));

    menu_opts_off(my_menu, O_SHOWDESC);
    menu_opts_off(my_menu, O_ROWMAJOR);
    menu_opts_off(my_menu, O_ONEVALUE);

    // Create window
    //my_menu_win = newwin(10, 40, 4, 4);
    my_menu_win = newwin(10, 70, 4, 4);
    keypad(my_menu_win, TRUE);

    // Set main windwo and sub window
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 6, 68, 3, 1));
    //set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));
    //set_menu_format(my_menu, 5, 1);
    set_menu_format(my_menu, 5, 3);
    set_menu_mark(my_menu, " * ");

    // Print border around the main window
    box(my_menu_win, 0, 0);
    print_in_middle(my_menu_win, 1, 0, 70, "My Menu", COLOR_PAIR(1));
    mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
    mvwhline(my_menu_win, 2, 1, ACS_HLINE, 68);
    mvwaddch(my_menu_win, 2, 69, ACS_RTEE);

    // Post the menu
    post_menu(my_menu);
    refresh();

    attron(COLOR_PAIR(4));
    mvprintw(LINES - 2, 0, 
        "Use PageUp and PageDown to scroll down or up a page of items");
    mvprintw(LINES - 1, 0, "Arrow Keys to navigate (F1 to Exit)");
    attroff(COLOR_PAIR(4));
    refresh();

    while((c = getch()) != KEY_F(1)) {
        switch(c) {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(my_menu, REQ_LEFT_ITEM);
                break;
            case KEY_RIGHT:
                menu_driver(my_menu, REQ_RIGHT_ITEM);
                break;
            case KEY_NPAGE:
                menu_driver(my_menu, REQ_SCR_DPAGE);
                break;
            case KEY_PPAGE:
                menu_driver(my_menu, REQ_SCR_UPAGE);
                break;
            case ' ':
                menu_driver(my_menu, REQ_TOGGLE_ITEM);
                break;
            case 10:
                {
                    char temp[200];
                    ITEM **items;
                    ITEM *cur;
                    void (*p)(char *);

                    items = menu_items(my_menu);
                    temp[0] = '\0';
                    for (i = 0; i < item_count(my_menu); ++i) {
                        if (item_value(items[i]) == TRUE) {
                            strcat(temp, item_name(items[i]));
                            strcat(temp, " ");
                        }
                    }
                    move(20, 0);
                    clrtoeol();
                    mvprintw(20, 0, "%s", temp);

                    move(19, 0);
                    clrtoeol();
                    mvprintw(19, 0, "Item selected is : %s",
                        item_name(current_item(my_menu)));

                    cur = current_item(my_menu);
                    p = item_userptr(cur);
                    p((char *) item_name(cur));

                    pos_menu_cursor(my_menu);
                    refresh();
                }
                break;

        }
        wrefresh(my_menu_win);
    }

    unpost_menu(my_menu);
    free_menu(my_menu);
    for (i = 0; i < n_choices; ++i) {
        free_item(my_items[i]);
    }
    endwin();
}

void func(char *name) {
    move(18, 0);
    clrtoeol();
    mvprintw(18, 0, "Item selected in fucntion is: %s", name);
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

