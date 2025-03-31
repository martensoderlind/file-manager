#ifndef TYPES_H
#define TYPES_H

using namespace std;

enum MenuState
{
    DISPLAY,
    EXIT
};
struct DirectoryEntry
{
    string name;
    string type;
    size_t size;
};

#endif