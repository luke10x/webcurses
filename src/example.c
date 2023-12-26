#include <curses.h>
#include <locale.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

int main() {
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
//   wborder(local_win, '|', '|', '-', '-', '+', '+', '+', '+');

  wattron(local_win, COLOR_PAIR(3));

  int max = 1;

  while (max < 10) {
    int ch = getch();

    // if (ch == -1) {
    //   continue;; // Actually, this only happens when the user closes the active window
    // }
    max ++;

    char str[100];
    sprintf(str, "SS: %d\n", ch);
    mvwaddstr(local_win, max, 2, str);

    wrefresh(local_win);

#ifdef EMSCRIPTEN
    emscripten_sleep(1000);
#endif
  }


  refresh();

  getch();
  endwin();
  return 0;
}
