#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

int main(void) {
  initscr();
  noecho();
  curs_set(FALSE);

  WINDOW *window = newwin(10, 10, 20, 20);

  int max_x, max_y;
  while(1) {
    clear();
    getmaxyx(stdscr, max_y, max_x);
    border('|', '|', '-', '-', '+', '+', '+', '+');
    
    refresh();
    usleep(DELAY);
  }

  clear();
  endwin();
}
