#include <curses.h>
#include <locale.h>

int main() {
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  keypad(stdscr, FALSE);   // Do not capture high key values, use esc sequences instead
  nodelay(stdscr, FALSE);  // Start in blocking mode
  
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

  char str[100];
  while (true) {
    unsigned int ch = getch();

    if (ch == 27) {
      nodelay(local_win, FALSE);
      timeout(10);

      int next = getch();

      nodelay(local_win, TRUE);
      timeout(-1);

      if (next == -1 || next == 27) {
        goto end;
      }

      ungetch(next);
    }

 
    sprintf(str, "SET: %d\n", ch);
    waddstr(local_win, str);

    wrefresh(local_win);
  }

end:

  addstr("BAIGTAS DARBAS");
  refresh();

  getch();
  endwin();
  return 0;
}
