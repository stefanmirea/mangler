#ifndef RELOCATION_INFO_CONTAINER_HPP_
#define RELOCATION_INFO_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"
#include "util.hpp"

namespace elf
{
class RelocationInfoContainer : public Container
{
public:
    RelocationInfoContainer(ELFFile *file, const std::pair<int, int> &interval,
                            unsigned int sectionIndex, unsigned int relocationIndex);
    std::vector<Container *> &getInnerContainers();
    ~RelocationInfoContainer();
private:
    unsigned int sectionIndex;
    unsigned int relocationIndex;
};
}

static struct
{
    const ELFIO::Elf_Word value;
    const char *string;
} r_type_strings[] =
{
    TO_STRING(R_386_NONE),
    TO_STRING(R_386_32),
    TO_STRING(R_386_PC32),
    TO_STRING(R_386_GOT32),
    TO_STRING(R_386_PLT32),
    TO_STRING(R_386_COPY),
    TO_STRING(R_386_GLOB_DAT),
    TO_STRING(R_386_JMP_SLOT),
    TO_STRING(R_386_RELATIVE),
    TO_STRING(R_386_GOTOFF),
    TO_STRING(R_386_GOTPC),
    { 0, nullptr },
};

#endif // RELOCATION_INFO_CONTAINER_HPP_
