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
void FileManager::createDirectory(const string &newDirectory)
{
    if (filesystem::exists(currentDirectory + "/" + newDirectory))
    {
        cout << "Directory already exist." << endl;
    }
    else
    {
        if (filesystem::create_directory(currentDirectory + "/" + newDirectory))
        {
            cout << "Directory: " << newDirectory << " created successfully!" << endl;
        }
        else
        {
            cout << "failed to create directory." << endl;
        }
    }
};
void FileManager::createFile(const string &newFile)
{
    if (filesystem::exists(currentDirectory + "/" + newFile))
    {
        cout << "A file with that name already exist." << endl;
    }
    else
    {
        try
        {
            ofstream file(currentDirectory + "/" + newFile);
            if (!file)
            {
                cerr << "Could not create file." << endl;
            }
            file.close();
            cout << "file created." << endl;
        }
        catch (const exception &e)
        {
            cerr << "Error while creating file: " << e.what() << '\n';
        }
    }
};
bool FileManager::removeFile(const string &fileToRemove)
{
    if (!filesystem::exists(currentDirectory + "/" + fileToRemove))
    {
        cout << "No file with that name exist." << endl;
        return false;
    }
    if (!filesystem::is_regular_file(currentDirectory + "/" + fileToRemove))
    {

        cout << "No file with that name exist." << endl;
        return false;
    }
    try
    {
        uintmax_t removed = filesystem::remove(currentDirectory + "/" + fileToRemove);
        if (removed > 0)
        {
            cout << "File removed successfully." << endl;
            return true;
        }
        else
        {
            cout << "Could not removed file." << endl;
            return false;
        }
    }
    catch (const exception &e)
    {
        cerr << "Error while deleting file: " << e.what() << '\n';
        return false;
    }
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