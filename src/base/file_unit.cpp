#include "file_unit.h"
#include "elfio/elfio.hpp"

FileUnit::FileUnit(std::string &filename)
{
    this->filename = filename;
}

FileUnit::~FileUnit()
{
    for (unsigned int i = 0; i < topLevelEntries.size(); ++i)
        delete topLevelEntries[i];
}

std::string &FileUnit::getName()
{
    return filename;
}

std::vector<Entry *> &FileUnit::getTopLevelEntries()
{
    return topLevelEntries;
}
