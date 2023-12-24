#include <curses.h>
#include <locale.h>
#include <stdlib.h>

int main() {
    // trace(TRACE_MAXIMUM);

    // setenv("TERM", "xterm", 1);

  setlocale(LC_ALL, "");
  initscr();
  noecho();
  
  //   resize_term(24, 52);
  printw("- (0, 0)\n");

  start_color();
  init_pair(1, COLOR_RED, COLOR_GREEN);
  init_pair(2, COLOR_GREEN, COLOR_BLUE);
  init_pair(3, COLOR_BLUE, COLOR_RED);
  attron(COLOR_PAIR(1));
  mvprintw(10, 40, "(10, 40)šūdas  🍔..\n");
  attroff(COLOR_PAIR(1));



  WINDOW *local_win;
int height = 16;
int width = 30;
int starty = 2;
 int startx = 3;
  local_win = newwin(height, width, starty, startx);
  wbkgd(local_win, COLOR_PAIR(2));

  box(local_win, 0 , 0);
  wborder(local_win, '|', '|', '-', '-', '+', '+', '+', '+');

  wattron(local_win, COLOR_PAIR(3));

  // Emojis are tricky still it is unclear what is the width of some
  // Printing them separately, and leavinig some trailing space
  // might help.
  mvwaddstr(local_win, 1, 2, "🍔  ");
  mvwaddstr(local_win, 1, 4, "hamburger");
  mvwaddstr(local_win, 2, 2, "⚡  ");
  mvwaddstr(local_win, 2, 4, "flash");
  mvwaddstr(local_win, 3, 2, "ė  ");
  mvwaddstr(local_win, 3, 4, "lithuanian");
  mvwaddstr(local_win, 4, 2, "א  ");
  mvwaddstr(local_win, 4, 4, "hebrew");
  mvwaddstr(local_win, 5, 2, "🥸  ");
  mvwaddstr(local_win, 5, 4, "ugly face");
  mvwaddstr(local_win, 6, 2, "🍀  ");
  mvwaddstr(local_win, 6, 4, "clover");
  mvwaddstr(local_win, 7, 2, "🐠 ");
  mvwaddstr(local_win, 7, 4, "fish");
  mvwaddstr(local_win, 8, 2, "🦄  ");
  mvwaddstr(local_win, 8, 4, "unicorn");

  refresh();

  wrefresh(local_win);




  getch();
  endwin();
    return 0;
}
