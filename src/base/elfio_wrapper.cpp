#include "elfio_wrapper.h"

ElfioWrapper::ElfioWrapper(std::string& filename)
{
    file = new ELFIO::elfio();
    file->load(filename);
}

ElfioWrapper::~ElfioWrapper()
{
    delete file;
}
