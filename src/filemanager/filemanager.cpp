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

vector<DirectoryEntry> FileManager::filesInCurrentDirectory()
{
    vector<DirectoryEntry> entries;

    if (currentDirectory.empty())
    {
        currentDirectory = filesystem::current_path();
    }

    for (const auto &entry : filesystem::directory_iterator(currentDirectory))
    {
        try
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
        catch (const std::exception &e)
        {
            continue;
        }
    }

    return entries;
}
void FileManager::createDirectory(const string &newDirectory, const int &row)
{
    if (filesystem::exists(currentDirectory + "/" + newDirectory))
    {
        mvprintw(row, 2, "A directory with that name already exist.");
        refresh();
        napms(2000);
    }
    else
    {
        if (filesystem::create_directory(currentDirectory + "/" + newDirectory))
        {
            mvprintw(row, 2, "Directory %s created successfully!", newDirectory.c_str());
            refresh();
            napms(1500);
        }
        else
        {
            mvprintw(row, 2, "Failed to create directory.");
            refresh();
            napms(2000);
        }
    }
    move(row, 0);
    clrtoeol();
    refresh();
};
void FileManager::createFile(const string &newFile, const int &row)
{
    if (filesystem::exists(currentDirectory + "/" + newFile))
    {
        mvprintw(row, 2, "A file with that name already exist.");
        refresh();
        napms(2000);
    }
    else
    {
        try
        {
            ofstream file(currentDirectory + "/" + newFile);
            if (!file)
            {
                mvprintw(row, 2, "Could not find file.");
                refresh();
                napms(2000);
            }
            file.close();
            mvprintw(row, 2, "File created.");
            refresh();
            napms(1500);
        }
        catch (const exception &e)
        {
            mvprintw(row, 2, "Error while creating file.");
            refresh();
            napms(2000);
        }
    }
    move(row, 0);
    clrtoeol();
    refresh();
};
bool FileManager::removeFile(const string &fileToRemove, const int &row)
{
    if (!filesystem::exists(currentDirectory + "/" + fileToRemove))
    {
        mvprintw(row, 2, "No file with that name exist.");
        refresh();
        napms(2000);
        return false;
    }
    if (filesystem::is_regular_file(currentDirectory + "/" + fileToRemove))
    {
        try
        {
            uintmax_t removed = filesystem::remove(currentDirectory + "/" + fileToRemove);
            if (removed > 0)
            {
                mvprintw(row, 2, "File removed successfully.");
                refresh();
                napms(2000);
                return true;
            }
            else
            {
                mvprintw(row, 2, "Could not remove file.");
                refresh();
                napms(2000);
                return false;
            }
        }
        catch (const exception &e)
        {
            mvprintw(row, 2, "Error while deleting file.");
            refresh();
            napms(2000);
            return false;
        }
    }
    else if (filesystem::is_directory(currentDirectory + "/" + fileToRemove))
    {
        try
        {
            uintmax_t removed = filesystem::remove_all(currentDirectory + "/" + fileToRemove);
            if (removed > 0)
            {
                mvprintw(row, 2, "Directory removed successfully.");
                refresh();
                napms(2000);
                return true;
            }
            else
            {
                mvprintw(row, 2, "Could not remove directory.");
                refresh();
                napms(2000);
                return false;
            }
        }
        catch (const exception &e)
        {
            mvprintw(row, 2, "Error while deleting directory.");
            refresh();
            napms(2000);
            return false;
        }
    }
    move(row, 0);
    clrtoeol();
    refresh();
    return true;
};

void FileManager::updateDirectory()
{
    size_t lastSlashPos = currentDirectory.find_last_of('/');

    if (lastSlashPos != string::npos)
    {
        currentDirectory = currentDirectory.substr(0, lastSlashPos);
    }
}
void FileManager::appendDirectory(const std::string &directory)
{
    if (directory.empty())
    {
        return;
    }

    std::string cleanDirectory = directory;
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
