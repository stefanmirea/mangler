#include "file_unit.h"
#include "elfio/elfio.hpp"

template <typename T>
FileUnit<T>::FileUnit(std::string &filename)
{
    fileWrapper = new T(filename);
    this->filename = filename;
}

template <typename T>
FileUnit<T>::~FileUnit()
{
    delete fileWrapper;
}

template <typename T>
bool FileUnit<T>::getOpenStatus()
{
    return fileWrapper->getOpenStatus();
}

template<typename T>
bool FileUnit<T>::save(std::string &filename)
{
    return fileWrapper->save(filename);
}

template<typename T>
std::string &FileUnit<T>::getName()
{
    return filename;
}

template class FileUnit<ElfioWrapper>;
