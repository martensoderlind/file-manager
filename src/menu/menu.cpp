#include <iostream>
#include <ncurses.h>
#include "menu.h"
#include <ncurses.h>

int Menu::mainMenu()
{
    int choice = 0;
    int key;
    bool run = true;
    const char *options[] = {"List files", "Create file", "Create directory", "Delete File", "Exit"};
    int num_options = sizeof(options) / sizeof(options[0]);

    while (run)
    {
        for (int i = 0; i < num_options; i++)
        {
            if (i == choice)
            {
                attron(A_REVERSE);
            }
            mvprintw(i + 2, 2, "%s", options[i]);
            attroff(A_REVERSE);
        }
        mvprintw(1, 2, "=====FILE MANAGER=====");
        refresh();
        key = getch();

        switch (key)
        {
        case KEY_UP:
            choice = (choice - 1 + num_options) % num_options;
            break;
        case KEY_DOWN:
            choice = (choice + 1) % num_options;
            break;
        case '\n':
            run = false;
            endwin();
            return choice;
        }
    }
    return -1;
}
void Menu::renderMenu()
{
    switch (menuState)
    {
    case MAIN:
        mainMenu();
        break;
    case DISPLAY:
        break;
    case ADD_FILE:
        break;
    case ADD_DIR:
        break;
    case REMOVE:
        break;
    case EXIT:
        break;
    default:
        break;
    }
}
