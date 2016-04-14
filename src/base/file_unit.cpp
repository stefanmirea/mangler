#include "file_unit.h"
#include "elfio/elfio.hpp"

FileUnit::FileUnit(std::string &filename)
{
    this->filename = filename;
}

FileUnit::~FileUnit() {}

std::string &FileUnit::getName()
{
    return filename;
}
