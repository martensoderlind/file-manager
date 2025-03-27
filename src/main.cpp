#include <iostream>
#include <string>
#include "filemanager.h"

using namespace std;

int main()
{
    string path = "/home/marten/Documents/Programmering/file-manager";
    FileManager fileManager(path);

    bool run = true;
    while (run)
    {
        cout << "====FILE MANAGER====" << endl;
        cout << "[1] show files" << endl;
        cout << "[2] create file" << endl;
        cout << "[3] create directory" << endl;
        cout << "[4] delete file/directory" << endl;
        cout << "[0] Exit" << endl;
        cout << "Write the alternativ that you want to perform: ";

        int alternativ;
        string newFile;
        string fileToDelete;
        string newDirectory;
        cin >>
            alternativ;
        switch (alternativ)
        {
        case 1:
            fileManager.listCurrentDirectory();
            break;
        case 2:
            // newFile = "../test.cpp";
            cout << "Enter the name of the file: ";
            cin >> newFile;
            fileManager.createFile(newFile);
            break;
        case 3:
            cout << "Enter the name of the directory: ";
            cin >> newDirectory;
            fileManager.createDirectory(newDirectory);
            break;
        case 4:
            cout << "Enter the name of the file: ";
            cin >> fileToDelete;
            fileManager.removeFile(fileToDelete);
            break;
        case 0:
            run = false;
            break;

        default:
            cout << "Pleas enter a valid input." << endl;
            break;
        }
    }
    return 0;
}