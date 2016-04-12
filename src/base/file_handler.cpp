#include "file_handler.h"

FileHandler::FileHandler() {};

bool open(std::string& filename)
{
    return false;
}

bool close(ElfFile* file)
{
    return false;
}

bool save(ElfFile* file)
{
    return false;
}

bool save(ElfFile* file, std::string& newName)
{
    return false;
}

FileHandler::~FileHandler() {}
