#include <iostream>
#include <string>
#include "filemanager.h"

using namespace std;

int main()
{
    string path = "/home/marten/Documents/Programmering/file-manager";
    FileManager fileManager(path);
    fileManager.listCurrentDirectory();
    return 0;
}