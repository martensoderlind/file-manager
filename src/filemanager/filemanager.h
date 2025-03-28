#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include "types.h"
using namespace std;
class FileManager
{
private:
    string currentDirectory;

public:
    FileManager();
    FileManager(string initialPath);

    vector<DirectoryEntry> filesInCurrentDirectory();
    void createDirectory(string newDirectory);
    void createFile(string newFile);
    bool removeFile(string fileToRemove);
    void updateDirectory();
    string directory();
};
#endif