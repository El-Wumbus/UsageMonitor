#include <stdio.h>
#include <curses.h>

int main(int argc, char**argv)
{
  initscr(); // Setup the screen
  printw("%d argument(s) provided", argc); // Like printf but for curses
  refresh(); // Show all changes
  getch();
  endwin(); // Stop the screen
  return 0;
}
