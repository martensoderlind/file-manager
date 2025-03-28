#include "filemanager.h"
#include <string>
#include <iostream>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <ncurses.h>
using namespace std;

FileManager::FileManager() {};
FileManager::FileManager(string initialPath) : currentDirectory(initialPath) {};

void FileManager::listCurrentDirectory()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    if (currentDirectory.empty())
    {
        currentDirectory = filesystem::current_path();
    }
    // cout << "CurrentDirectory:" << currentDirectory << endl;
    mvprintw(1, 2, "CurrentDirectory: %s", currentDirectory.c_str());

    mvprintw(2, 1, "---------------------------------------------------------------------");
    // cout << "---------------------------------------------------------------------" << endl;
    mvprintw(3, 2, "Name");
    mvprintw(3, 40, "Type");
    mvprintw(3, 55, "File size");
    // cout << left << setw(40) << "Name"
    // << setw(15) << "Type";
    // cout << "File size" << endl;
    // cout << "---------------------------------------------------------------------" << endl;
    mvprintw(4, 1, "---------------------------------------------------------------------");
    int row = 5;
    for (const auto &entry : filesystem::directory_iterator(currentDirectory))
    {
        try
        {
            string fileType;
            if (filesystem::is_directory(entry.status()))
            {
                fileType = "directory";
            }
            else if (filesystem::is_regular_file(entry.status()))
            {
                fileType = "file";
            }
            else
            {
                fileType = "other";
            }
            mvprintw(row, 2, "%s", entry.path().filename().string().c_str());
            mvprintw(row, 40, "%s", fileType.c_str());

            // cout << left << setw(40) << entry.path().filename().string()
            //  << setw(15) << fileType;
            if (filesystem::is_regular_file(entry.status()))
            {
                mvprintw(row, 55, "%lu", filesystem::file_size(entry.path()));
                // cout << setw(5) << filesystem::file_size(entry.path()) << " B" << endl;
            }
            else
            {
                mvprintw(row, 55, "-");
                // cout << "-" << endl;
            }
            row++;
        }
        catch (const std::exception &e)
        {
            cerr << e.what() << '\n';
        }
    }
    refresh();
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
