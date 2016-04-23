#ifndef FILE_HANDLER_HPP_
#define FILE_HANDLER_HPP_
#include "file_unit.hpp"
#include <string>
#include <vector>

class FileHandler
{
public:
    FileHandler();

    bool open(const std::string &filename);
    bool close(FileUnit *file);
    bool save(FileUnit *file);
    bool save(FileUnit *file, std::string &newName);

    virtual ~FileHandler();

    std::vector<FileUnit *> openFiles;
};

#endif
