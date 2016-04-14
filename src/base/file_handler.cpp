#include "file_handler.h"

template <typename T>
FileHandler<T>::FileHandler() {};

template <typename T>
bool FileHandler<T>::open(std::string &filename)
{
    FileUnit<T> *newFile = new FileUnit<T>(filename);
    openedFiles.push_back(newFile);
    return newFile->getOpenStatus();
}

template <typename T>
bool FileHandler<T>::close(FileUnit<T> *file)
{
    return false;
}

template <typename T>
bool FileHandler<T>::save(FileUnit<T> *file)
{
    return file->save(file->getName());
}

template <typename T>
bool FileHandler<T>::save(FileUnit<T> *file, std::string &newName)
{
    return file->save(newName);
}

template <typename T>
FileHandler<T>::~FileHandler() {}

template class FileHandler<ElfioWrapper>;
