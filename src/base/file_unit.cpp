#include "file_unit.h"
#include "elfio/elfio.hpp"

template <typename T>
FileUnit<T>::FileUnit(std::string& filename) {}

template <typename T>
FileUnit<T>::~FileUnit() {}

template class FileUnit<ELFIO::elfio>;