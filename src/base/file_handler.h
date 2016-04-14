#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_
#include "file_unit.h"
#include <string>
#include <vector>

template <typename T>
class FileHandler
{
public:
    FileHandler();

    bool open(std::string& filename);
    bool close(FileUnit<T> *file);
    bool save(FileUnit<T> *file);
    bool save(FileUnit<T> *file, std::string& newName);

    virtual ~FileHandler();

    std::vector<FileUnit<T>*> openedFiles;
};

#endif
