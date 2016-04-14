#ifndef ELF_FILE_H_
#define ELF_FILE_H_

#include "elfio/elfio.hpp"
#include "file_unit.h"
#include <string>

class ELFFile : public FileUnit
{
public:
    ELFFile(std::string &filename);
    bool getOpenStatus();
    bool save(std::string &filename);
    virtual ~ELFFile();

private:
    ELFIO::elfio *file;
    bool open;
};

#endif