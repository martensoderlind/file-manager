#include "filemanager.h"
#include <string>
FileManager::FileManager() {};
FileManager::FileManager(string &initialPath) : currentDirectory(initialPath) {};