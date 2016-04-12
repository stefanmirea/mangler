#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_
#include "elf_file.h"
#include <string>
#include <vector>

class FileHandler
{
public:
    std::vector<ElfFile*> openedFiles;

    FileHandler();

    bool open(std::string& filename);
    bool close(ElfFile* file);
    bool save(ElfFile* file);
    bool save(ElfFile* file, std::string& newName);

    virtual ~FileHandler();
};

#endif
