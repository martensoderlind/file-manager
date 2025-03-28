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
    string copyFrom;
    string copyTo;

public:
    FileManager();
    FileManager(string initialPath);

    vector<DirectoryEntry> filesInCurrentDirectory();
    void createDirectory(const string &newDirectory, const int &row);
    void createFile(const string &newFile, const int &row);
    bool removeFile(const string &fileToRemove);
    void updateDirectory();
    void appendDirectory(const string &directory);
    string directory();
    void setCopyFrom(const string &file);
    bool CopyFromEmpty();
    void setCopyTo(const string &file);
    void copy();
};
#endif