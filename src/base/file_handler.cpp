#include "file_handler.h"

FileHandler::FileHandler() {};

bool open(std::string& filename)
{
    return false;
}

bool close(FileUnit* file)
{
    return false;
}

bool save(FileUnit* file)
{
    return false;
}

bool save(FileUnit* file, std::string& newName)
{
    return false;
}

FileHandler::~FileHandler() {}
