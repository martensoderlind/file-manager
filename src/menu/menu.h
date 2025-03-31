#ifndef MENU_H
#define MENU_H

#include "types.h"
#include "filemanager.h"

class Menu
{
private:
    MenuState menuState;
    FileManager fileManager;

public:
    Menu() : menuState(DISPLAY) {};
    int mainMenu();
    int displayMenu(const std::vector<DirectoryEntry> &entries);
    int fileMenu(const int &row);
    int renderMenu();
    void stateChange(const int &option);
    void handelFileMenu(const int &option, const int &row);
};

#endif