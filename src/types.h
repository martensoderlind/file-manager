#ifndef TYPES_H
#define TYPES_H

enum MenuState
{
    MAIN,
    DISPLAY,
    ADD_FILE,
    ADD_DIR,
    REMOVE,
    EXIT
};
struct DirectoryEntry
{
    std::string name;
    std::string type;
    std::size_t size;
};

#endif