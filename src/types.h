#ifndef TYPES_H
#define TYPES_H

using namespace std;

enum MenuState
{
    DISPLAY,
    ADD_FILE,
    ADD_DIR,
    REMOVE,
    EXIT
};
struct DirectoryEntry
{
    string name;
    string type;
    size_t size;
};

#endif