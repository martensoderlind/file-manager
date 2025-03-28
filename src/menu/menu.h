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
    Menu() : menuState(MAIN) {};
    int mainMenu();
    int renderMenu();
    void stateChange(int option);
};

#endif