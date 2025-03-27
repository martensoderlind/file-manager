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
            // string fileSize;
            if (filesystem::is_directory(entry.status()))
            {
                fileType = "directory";
            }
            if (filesystem::is_regular_file(entry.status()))
            {
                fileType = "file";
                // fileSize = filesystem::file_size(entry.path());
            }
            else
            {
                fileType = "other";
                // fileSize = "-";
            }

            cout << left << setw(40) << entry.path().filename().string()
                 << setw(15) << fileType;
            // cout << fileSize << endl;
            if (std::filesystem::is_regular_file(entry.status()))
            {
                std::cout << setw(5) << filesystem::file_size(entry.path()) << " B" << endl;
            }
            else
            {
                std::cout << "-" << endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
};
void FileManager::createDirectory(string newDirectory)
{
    if (filesystem::exists(newDirectory))
    {
        cout << "Directory already exist." << endl;
    }
    else
    {
        if (filesystem::create_directory(newDirectory))
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
    try
    {
        ofstream file(newFile);
        if (!file)
        {
            cerr << "Could not create file." << endl;
        }
        file.close();
        cout << "file created." << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error while creating file: " << e.what() << '\n';
    }
};
