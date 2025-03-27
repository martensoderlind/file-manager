#include "filemanager.h"
#include <string>
#include <iostream>
using namespace std;

FileManager::FileManager() {};
FileManager::FileManager(string &initialPath) : currentDirectory(initialPath) {};

bool FileManager::listCurrentDirectory()
{
    currentDirectory = filesystem::current_path();
    cout << "currentDirectory:" << currentDirectory << endl;
    return 0;
};
