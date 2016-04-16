#include "file_unit.h"
#include "elfio/elfio.hpp"

FileUnit::FileUnit(const std::string &filename)
{
    this->filename = filename;
}

FileUnit::~FileUnit()
{
    for (unsigned int i = 0; i < topLevelContainers.size(); ++i)
        delete topLevelContainers[i];
}

std::string &FileUnit::getName()
{
    return filename;
}

std::vector<Container *> &FileUnit::getTopLevelContainers()
{
    return topLevelContainers;
}
