#include "file_unit.h"
#include "elfio/elfio.hpp"

template <typename T>
FileUnit<T>::FileUnit(std::string& filename)
{
    fileWrapper = new T(filename);
    this->filename = filename;
}

template <typename T>
FileUnit<T>::~FileUnit()
{
    delete fileWrapper;
}

template class FileUnit<ElfioWrapper>;
