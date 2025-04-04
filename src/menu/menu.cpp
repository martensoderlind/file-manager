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

void Menu::drawMenuHeader()
{
    string currentDirectory = fileManager.directory();

    clear();
    mvprintw(1, 2, "=====FILE MANAGER=====");
    mvprintw(2, 2, "%s", currentDirectory.c_str());
    mvprintw(3, 2, "Name");
    mvprintw(3, 40, "Type");
    mvprintw(3, 55, "Size [B]");
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
string Menu::fileNameInput(const int row, const string message)
{
    char input[10] = {0};
    mvprintw(row + 4, 2, "%s", message.c_str());
    refresh();
    getnstr(input, sizeof(input) - 1);
    return input;
}

int Menu::displayMenu(const vector<DirectoryEntry> &entries)
{
    int choice = 0;
    int key;
    bool run = true;

    const int nameColumn = 2;
    const int typeColumn = 40;
    const int sizeColumn = 55;

    vector<string> options;
    vector<string> type;
    vector<size_t> size;

    initializeMenuOptions(options, type, size, entries);
    int num_options = options.size();
    int num_type = type.size();
    int num_size = size.size();

    while (run)
    {
        drawMenuHeader();
        for (int i = 0; i < num_options; i++)
        {
            if (i == choice)
            {
                attron(A_REVERSE);
            }

            if (type[i] == "file")
            {
                mvprintw(i + 5, nameColumn, "%s", options[i].c_str());
                mvprintw(i + 5, typeColumn, "%s", type[i].c_str());
                mvprintw(i + 5, sizeColumn, "%zu", size[i]);
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
    bool copyEmpty = fileManager.CopyFromEmpty();

    if (!copyEmpty)
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

void Menu::handelFileMenu(const int &option, const int &row)
{
    echo();
    string input;
    switch (option)
    {
    case 0:
        input = fileNameInput(row, "Name of the file: ");
        fileManager.createFile(input, row + 2);
        break;
    case 1:
        input = fileNameInput(row, "Name of directory: ");
        fileManager.createDirectory(input, row + 2);
        break;
    case 2:
        input = fileNameInput(row, "Name of the file: ");
        fileManager.removeItem(input, row + 2);
        break;
    case 3:
        input = fileNameInput(row, "Name of the file: ");
        fileManager.setCopyFrom(input);
        break;
    case 4:
        if (!fileManager.CopyFromEmpty())
        {
            input = fileNameInput(row + 1, "Name the new file: ");
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
    int fileOption;
    vector<DirectoryEntry> files = fileManager.filesInCurrentDirectory();
    int displayOption = displayMenu(files);

    switch (displayOption)
    {
    case 0:
        clear();
        return 1;
        break;
    case 1:
        fileOption = fileMenu(files.size());
        handelFileMenu(fileOption, files.size() + 12);
        break;
    case 2:
        fileManager.updateDirectory();
        break;
    default:
        if (files[displayOption - 3].type == "directory")
        {
            fileManager.appendDirectory(files[displayOption - 3].name);
        }
        break;
    }
    return 0;
}
