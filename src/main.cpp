#include <iostream>
#include <string>
#include <ncurses.h>
#include "filemanager.h"
#include "menu/menu.h"
#include "types.h"

using namespace std;

int main()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    bool run = true;
    Menu menu;
    int renderMenu = 0;
    while (run)
    {
        renderMenu = menu.renderMenu();
        if (renderMenu == 1)
        {
            run = false;
        }
    }
    endwin();
    return 0;
}