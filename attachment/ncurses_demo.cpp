#include <ncurses.h>

#define REG_COLOR_NUM 1
#define CUS_COLOR_NUM 2

int main()
{ 
    initscr(); /* Start curses mode */
    raw();
    noecho();
    keypad(stdscr, true); /*stdscr is the regular window*/

    // init color
    start_color();
    init_pair(REG_COLOR_NUM, COLOR_WHITE, COLOR_BLACK);
    init_pair(CUS_COLOR_NUM, COLOR_YELLOW, COLOR_CYAN);

    // set stdscr color
    wbkgd(stdscr, COLOR_PAIR(REG_COLOR_NUM));
    wrefresh(stdscr);

    // check window size is illegal
    // LINES and COLS store the total line and cols of stdscr
    if (LINES < 5) {
        fprintf(stderr, "window line size is small than 5");
        endwin();
        return 0;
    }

    // create customized window
    WINDOW *win = newwin(5, COLS, 0, 0); /*create a 5*10 window in (0, 0)*/
    keypad(win, true);
    wbkgd(win, COLOR_PAIR(CUS_COLOR_NUM)); /*set customized window color*/
    wrefresh(win);

    wprintw(win, "Press Esc to Exit");
    wmove(win, 2, 2);
    wprintw(win, "Hello, world!"); /* Print Hello World */
    mvwprintw(win, 3, 2, "This is MiniVim, your input will appear on the next line."); /*Move and Print*/
    wrefresh(win); /* Print it on to the real screen */

    wmove(win, 4, 2);
    int ch = 0;
    // get char in loop until get `Esc`
    while ((ch = getch()) != 27) {
        wprintw(win, "%c", ch);
        wrefresh(win);
    }
    endwin(); /* End curses mode */
    return 0;
}
