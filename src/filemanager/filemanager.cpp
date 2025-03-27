#include "filemanager.h"
#include <string>
#include <iostream>
#include <cassert>
#include <filesystem>
#include <fstream>
using namespace std;

FileManager::FileManager() {};
FileManager::FileManager(string initialPath) : currentDirectory(initialPath) {};

void FileManager::listCurrentDirectory()
{
    if (currentDirectory.empty())
    {
        currentDirectory = filesystem::current_path();
    }
    cout << "CurrentDirectory:" << currentDirectory << endl;

    cout << "---------------------------------------------------------------------" << endl;
    cout << left << setw(40) << "Name"
         << setw(15) << "Type";
    cout << "File size" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    for (const auto &entry : filesystem::directory_iterator(currentDirectory))
    {
        try
        {
            string fileType;
            if (filesystem::is_directory(entry.status()))
            {
                fileType = "directory";
            }
            if (filesystem::is_regular_file(entry.status()))
            {
                fileType = "file";
            }
            else
            {
                fileType = "other";
            }

            cout << left << setw(40) << entry.path().filename().string()
                 << setw(15) << fileType;
            if (filesystem::is_regular_file(entry.status()))
            {
                cout << setw(5) << filesystem::file_size(entry.path()) << " B" << endl;
            }
            else
            {
                cout << "-" << endl;
            }
        }
        catch (const std::exception &e)
        {
            cerr << e.what() << '\n';
        }
    }
};
void FileManager::createDirectory(string newDirectory)
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
void FileManager::createFile(string newFile)
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
bool FileManager::removeFile(string fileToRemove)
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
