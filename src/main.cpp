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
    while (run)
    {
        menu.renderMenu();
    }

    return 0;
}