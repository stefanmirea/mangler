#ifndef RELOCATION_ENTRY_CONTAINER_HPP_
#define RELOCATION_ENTRY_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class RelocationEntryContainer : public Container
{
public:
    RelocationEntryContainer(ELFFile *file, const std::pair<int, int> &interval,
                             unsigned int sectionIndex, unsigned int relocationIndex);
    std::vector<Container *> &getInnerContainers();
    ~RelocationEntryContainer();
private:
    unsigned int sectionIndex;
    unsigned int relocationIndex;
    ELFIO::Elf64_Addr r_offset;
};
}

#endif // RELOCATION_ENTRY_CONTAINER_HPP_
