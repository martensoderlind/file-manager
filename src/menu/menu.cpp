#include <iostream>
#include <ncurses.h>
#include <vector>
#include "menu.h"
#include "types.h"

void Menu::initializeMenuOptions(vector<string> &options,
                                 vector<string> &type,
                                 vector<size_t> &size,
                                 const vector<DirectoryEntry> &entries)
{
    options.push_back("[Exit]");
    type.push_back("action");
    size.push_back(0);

    options.push_back("[Options]");
    type.push_back("action");
    size.push_back(0);

    options.push_back("[..Parent Directory]");
    type.push_back("directory");
    size.push_back(0);

    for (const auto &entry : entries)
    {
        options.push_back(entry.name);
        type.push_back(entry.type);
        size.push_back(entry.size);
    }
}

void Menu::drawMenuHeader(const string &currentDirectory)
{
    clear();
    mvprintw(1, 2, "=====FILE MANAGER=====");
    mvprintw(2, 2, "%s", currentDirectory.c_str());
    mvprintw(3, 2, "Name");
    mvprintw(3, 40, "Type");
    mvprintw(3, 55, "Size");
    mvprintw(4, 1, "-----------------------------------------------------------");
}

bool Menu::handleKeyInput(int key, int &choice, int num_options, bool &run)
{
    switch (key)
    {
    case KEY_UP:
        choice = (choice - 1 + num_options) % num_options;
        return false;
        break;
    case KEY_DOWN:
        choice = (choice + 1) % num_options;
        return false;
        break;
    case '\n':
        run = false;
        return true;
    default:
        return false;
    }
}
int Menu::displayMenu(const vector<DirectoryEntry> &entries)
{
    int choice = 0;
    int key;
    bool run = true;

    const int nameCol = 2;
    const int typeCol = 40;
    const int sizeCol = 55;

    string currentDirectory = fileManager.directory();
    vector<string> options;
    vector<string> type;
    vector<size_t> size;

    initializeMenuOptions(options, type, size, entries);
    int num_options = options.size();
    int num_type = type.size();
    int num_size = size.size();

    while (run)
    {
        drawMenuHeader(currentDirectory);
        for (int i = 0; i < num_options; i++)
        {
            if (i == choice)
            {
                attron(A_REVERSE);
            }

            if (type[i] == "file")
            {
                mvprintw(i + 5, nameCol, "%s", options[i].c_str());
                mvprintw(i + 5, typeCol, "%s", type[i].c_str());
                mvprintw(i + 5, sizeCol, "%zu", size[i]);
            }
            else
            {
                mvprintw(i + 5, 2, "%s", options[i].c_str());
                mvprintw(i + 5, 40, "%s", type[i].c_str());
            }

            attroff(A_REVERSE);
        }

        refresh();

        key = getch();
        if (handleKeyInput(key, choice, num_options, run))
        {
            endwin();
            return choice;
        }
    }

    return -1;
}

int Menu::fileMenu(const int &row)
{
    int choice = 0;
    int key;
    bool run = true;
    vector<string> options = {"Add file", "Add directory", "Delete file/directory", "Copy", "Exit"};
    bool pasteEmpty = fileManager.CopyFromEmpty();
    if (!pasteEmpty)
    {
        options.insert(options.end() - 1, "Paste");
    }
    int num_options = options.size();

    while (run)
    {
        for (int i = 0; i < num_options; i++)
        {
            if (i == choice)
            {
                attron(A_REVERSE);
            }
            mvprintw(i + row + 9, 2, "%s", options[i].c_str());
            attroff(A_REVERSE);
        }
        mvprintw(row + 8, 1, "-----------------------------------------------------------");
        refresh();
        key = getch();
        if (handleKeyInput(key, choice, num_options, run))
        {
            endwin();
            return choice;
        }
    }
    return -1;
}
string Menu::fileNameInput(const int row, const string message)
{
    char input[10] = {0};
    mvprintw(row + 1, 2, "%s", message.c_str());
    refresh();
    getnstr(input, sizeof(input) - 1);
    return input;
}
void Menu::handelFileMenu(const int &option, const int &row)
{
    echo();
    string input;
    switch (option)
    {
    case 0:
        input = fileNameInput(row, "Name of file: ");
        fileManager.createFile(input, row + 2);
        break;
    case 1:
        input = fileNameInput(row, "Name of directory: ");
        fileManager.createDirectory(input, row + 2);
        break;
    case 2:
        input = fileNameInput(row, "Name of file: ");
        fileManager.removeFile(input, row + 2);
        break;
    case 3:
        input = fileNameInput(row, "Name of file: ");
        fileManager.setCopyFrom(input);
        break;
    case 4:
        if (!fileManager.CopyFromEmpty())
        {
            fileNameInput(row + 1, "Name the new file: ");
            fileManager.setCopyTo(input);
            fileManager.copy();
        }
        break;
    default:
        break;
    }
    noecho();
}
int Menu::renderMenu()
{
    int option;
    int displayOption;
    int fileOption;
    vector<DirectoryEntry> files;
    switch (menuState)
    {
    case DISPLAY:
        files = fileManager.filesInCurrentDirectory();
        displayOption = displayMenu(files);

        if (displayOption == 0)
        {
            clear();
            menuState = EXIT;
        }
        else if (displayOption == 1)
        {
            fileOption = fileMenu(files.size());
            handelFileMenu(fileOption, files.size() + 12);
        }
        else if (displayOption == 2)
        {
            fileManager.updateDirectory();
        }
        else
        {
            if (files[displayOption - 3].type == "directory")
            {
                fileManager.appendDirectory(files[displayOption - 3].name);
            }
        }
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
