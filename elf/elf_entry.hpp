#ifndef ELF_ENTRY_HPP_
#define ELF_ENTRY_HPP_

#include "core/container.hpp"
#include "elf_file.hpp"


namespace elf
{
class ELFEntry : public Container
{
public:
    ELFEntry(ELFFile *file, const std::pair<int, int> &interval);
    virtual void update(char *data) = 0;
};
}

#endif // ELF_ENTRY_HPP

