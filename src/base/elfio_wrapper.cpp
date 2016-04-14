#include "elfio_wrapper.h"

ElfioWrapper::ElfioWrapper(std::string &filename)
{
    file = new ELFIO::elfio();
    open = file->load(filename);
}

ElfioWrapper::~ElfioWrapper()
{
    delete file;
}

bool ElfioWrapper::getOpenStatus()
{
    return open;
}

bool ElfioWrapper::save(std::string &filename)
{
    return file->save(filename);
}
