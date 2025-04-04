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
    int displayMenu(const std::vector<DirectoryEntry> &entries);
    int fileMenu(const int &row);
    int renderMenu();
    void handelFileMenu(const int &option, const int &row);
    bool handleKeyInput(int key, int &choice, int num_options, bool &run);
    void initializeMenuOptions(vector<string> &options,
                               vector<string> &type,
                               vector<size_t> &size,
                               const vector<DirectoryEntry> &entries);
    void drawMenuHeader();
    string fileNameInput(const int row, const string message);
};

#endif