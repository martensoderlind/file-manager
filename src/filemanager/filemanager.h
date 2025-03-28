#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <filesystem>
#include <fstream>
#include <string>
using namespace std;
class FileManager
{
private:
    string currentDirectory;

public:
    FileManager();
    FileManager(string initialPath);

    void listCurrentDirectory();
    void createDirectory(string newDirectory);
    void createFile(string newFile);
    bool removeFile(string fileToRemove);
};
#endif