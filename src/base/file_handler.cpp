#include "file_handler.h"

template <typename T>
FileHandler<T>::FileHandler() {};

template <typename T>
bool FileHandler<T>::open(std::string& filename)
{
    return false;
}

template <typename T>
bool FileHandler<T>::close(FileUnit<T>* file)
{
    return false;
}

template <typename T>
bool FileHandler<T>::save(FileUnit<T>* file)
{
    return false;
}

template <typename T>
bool FileHandler<T>::save(FileUnit<T>* file, std::string& newName)
{
    return false;
}

template <typename T>
FileHandler<T>::~FileHandler() {}
