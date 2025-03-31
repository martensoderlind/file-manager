#include "filemanager.h"
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <ncurses.h>
#include "types.h"

using namespace std;

FileManager::FileManager() {};
FileManager::FileManager(string initialPath) : currentDirectory(initialPath) {};

void FileManager::statusMessage(const int row, const string message, const int delay)
{
    mvprintw(row, 2, "%s", message.c_str());
    refresh();
    napms(delay);
}

vector<DirectoryEntry> FileManager::filesInCurrentDirectory()
{
    vector<DirectoryEntry> entries;

    if (currentDirectory.empty())
    {
        currentDirectory = filesystem::current_path();
    }

    for (const auto &entry : filesystem::directory_iterator(currentDirectory))
    {
        DirectoryEntry dirEntry;
        dirEntry.name = entry.path().filename().string();

        if (filesystem::is_directory(entry.status()))
        {
            dirEntry.type = "directory";
        }
        else if (filesystem::is_regular_file(entry.status()))
        {
            dirEntry.type = "file";
            dirEntry.size = filesystem::file_size(entry.path());
        }
        else
        {
            dirEntry.type = "other";
            dirEntry.size = 0;
        }
        entries.push_back(dirEntry);
    }
    return entries;
}

void FileManager::createDirectory(const string &newDirectory, const int &row)
{
    if (filesystem::exists(currentDirectory + "/" + newDirectory))
    {
        statusMessage(row, "A directory with that name already exist.", 2000);
    }
    else if (filesystem::create_directory(currentDirectory + "/" + newDirectory))
    {
        statusMessage(row, "Directory created successfully!", 1500);
    }
    else
    {
        statusMessage(row, "Failed to create directory.", 2000);
    }

    move(row, 0);
    clrtoeol();
    refresh();
};
void FileManager::createFile(const string &newFile, const int &row)
{
    if (filesystem::exists(currentDirectory + "/" + newFile))
    {
        statusMessage(row, "A file with that name already exist.", 2000);
    }
    else
    {
        try
        {
            ofstream file(currentDirectory + "/" + newFile);
            if (!file)
            {
                statusMessage(row, "Could not create file.", 2000);
            }
            file.close();
            statusMessage(row, "File created", 1500);
        }
        catch (const exception &e)
        {
            statusMessage(row, "Error while creating file.", 2000);
        }
    }
    move(row, 0);
    clrtoeol();
    refresh();
};

void FileManager::removeFile(const int &row, const string &fileToRemove)
{
    try
    {
        uintmax_t removed = filesystem::remove(currentDirectory + "/" + fileToRemove);
        if (removed > 0)
        {
            statusMessage(row, "File removed successfully.", 1500);
        }
        else
        {
            statusMessage(row, "Could not remove file.", 2000);
        }
    }
    catch (const exception &e)
    {
        mvprintw(row, 2, "Error while deleting file: %s", e.what());
        refresh();
        napms(2000);
    }
}
void FileManager::removeDirectory(const int &row, const string &fileToRemove)
{
    try
    {
        uintmax_t removed = filesystem::remove_all(currentDirectory + "/" + fileToRemove);
        if (removed > 0)
        {
            statusMessage(row, "Directory removed successfully.", 2000);
        }
        else
        {
            statusMessage(row, "Could not remove directory.", 2000);
        }
    }
    catch (const exception &e)
    {
        mvprintw(row, 2, "Error while deleting directory: %s", e.what());
        refresh();
        napms(2000);
    }
}
void FileManager::removeItem(const string &fileToRemove, const int &row)
{
    if (fileToRemove.empty())
    {
        statusMessage(row, "Please enter the name of the file/directory that you want to remove.", 3000);
    }
    else if (!filesystem::exists(currentDirectory + "/" + fileToRemove))
    {
        statusMessage(row, "No file with that name exist.", 2000);
    }
    else if (filesystem::is_regular_file(currentDirectory + "/" + fileToRemove))
    {
        removeFile(row, fileToRemove);
    }
    else if (filesystem::is_directory(currentDirectory + "/" + fileToRemove))
    {
        removeDirectory(row, fileToRemove);
    }
    move(row, 0);
    clrtoeol();
    refresh();
};

void FileManager::updateDirectory()
{
    size_t lastSlashPos = currentDirectory.find_last_of('/');

    if (lastSlashPos != string::npos)
    {
        currentDirectory = currentDirectory.substr(0, lastSlashPos);
    }
}
void FileManager::appendDirectory(const string &directory)
{
    if (directory.empty())
    {
        return;
    }

    string cleanDirectory = directory;
    if (cleanDirectory.front() == '/')
    {
        cleanDirectory.erase(0, 1);
    }

    if (!currentDirectory.empty() && currentDirectory.back() != '/')
    {
        currentDirectory += "/";
    }

    currentDirectory += cleanDirectory;
}
string FileManager::directory()
{
    return currentDirectory;
}
void FileManager::setCopyTo(const string &file)
{
    copyTo = currentDirectory + "/" + file;
}
void FileManager::setCopyFrom(const string &file)
{
    copyFrom = currentDirectory + "/" + file;
}
void FileManager::copy()
{
    filesystem::copy(copyFrom, copyTo);
    copyFrom = "";
    copyTo = "";
}
bool FileManager::CopyFromEmpty()
{
    return copyFrom.empty();
};
