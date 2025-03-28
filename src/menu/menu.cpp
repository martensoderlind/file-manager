#include <iostream>
#include <ncurses.h>
#include "menu.h"
#include <ncurses.h>
#include "types.h"

void Menu::stateChange(int option)
{
    switch (option)
    {
    case 0:
        menuState = DISPLAY;
        break;
    case 1:
        menuState = ADD_FILE;
        break;
    case 2:
        menuState = ADD_DIR;
        break;
    case 3:
        menuState = REMOVE;
        break;
    case 4:
        menuState = EXIT;
        break;

    default:
        break;
    }
}
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
int Menu::displayMenu(const std::vector<DirectoryEntry> &entries)
{
    int choice = 0;
    int key;
    bool run = true;

    std::vector<std::string> options;
    options.push_back(".. (Parent Directory)");

    for (const auto &entry : entries)
    {
        std::string entryDisplay = entry.name + " (" + entry.type + ")";
        options.push_back(entryDisplay);
    }

    options.push_back("Create file");
    options.push_back("Create directory");
    options.push_back("Delete File");
    options.push_back("Exit");

    int num_options = options.size();

    while (run)
    {
        clear();

        mvprintw(1, 2, "=====FILE MANAGER=====");

        for (int i = 0; i < num_options; i++)
        {
            if (i == choice)
            {
                attron(A_REVERSE);
            }
            mvprintw(i + 2, 2, "%s", options[i].c_str());
            attroff(A_REVERSE);
        }

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
            return choice;
        }
    }

    return -1;
}
int Menu::renderMenu()
{
    int option;
    vector<DirectoryEntry> files;
    switch (menuState)
    {
    case MAIN:
        option = mainMenu();
        // clear();
        stateChange(option);
        return 0;
        break;
    case DISPLAY:
        files = fileManager.filesInCurrentDirectory();
        displayMenu(files);
        return 0;
        break;
    case ADD_FILE:
        return 0;
        break;
    case ADD_DIR:
        return 0;
        break;
    case REMOVE:
        return 0;
        break;
    case EXIT:
        return 1;
        break;
    default:
        return 1;
        break;
    }
}
