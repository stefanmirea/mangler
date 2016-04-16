#ifndef ELF_FILE_H_
#define ELF_FILE_H_

#include "elfio/elfio.hpp"
#include "file_unit.h"
#include <string>

class ELFFile : public FileUnit
{
public:
    ELFFile(const std::string &filename);
    bool getOpenStatus();
    bool save(std::string &filename);
    void modifyHex(size_t offset, std::string &newContent);
    virtual ~ELFFile();

private:
    ELFIO::elfio *file;
    bool open;
};

#endif
