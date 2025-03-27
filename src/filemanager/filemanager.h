#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <filesystem>
#include <string>
using namespace std;
class FileManager
{
private:
    filesystem::path currentDirectory;

public:
    // Konstruktorer
    FileManager();
    FileManager(string &initialPath);
};
#endif