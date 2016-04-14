#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_
#include "file_unit.h"
#include <string>
#include <vector>

class FileHandler
{
public:
    FileHandler();

    bool open(std::string &filename);
    bool close(FileUnit *file);
    bool save(FileUnit *file);
    bool save(FileUnit *file, std::string &newName);

    virtual ~FileHandler();

    std::vector<FileUnit *> openedFiles;
};

#endif
