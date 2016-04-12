#ifndef ELF_FILE_H_
#define ELF_FILE_H_

#include <string>

class ElfFile
{
public:
    std::string filename;

    ElfFile(std::string& filename);

    virtual ~ElfFile();
};

#endif
