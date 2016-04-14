#ifndef ELFIO_WRAPPER_H_
#define ELFIO_WRAPPER_H_

#include "elfio/elfio.hpp"
#include <string>

class ElfioWrapper
{
public:
    ElfioWrapper(std::string& filename);

    virtual ~ElfioWrapper();

private:
    ELFIO::elfio *file;
};

#endif
