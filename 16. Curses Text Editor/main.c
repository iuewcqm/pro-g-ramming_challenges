#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

int main(void) {
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(FALSE);
  
  border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

  move(1,1);

  while(1) {
    char ch = getch();
    // printw("%c", ch);
    addch(ch | A_STANDOUT);
    
    refresh();
    usleep(DELAY);
  }
  
  clear();
  endwin();

  return 0;
}
