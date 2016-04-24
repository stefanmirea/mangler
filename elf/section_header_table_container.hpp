#ifndef SECTION_HEADER_TABLE_CONTAINER_HPP_
#define SECTION_HEADER_TABLE_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class SectionHeaderTableContainer : public Container
{
public:
    SectionHeaderTableContainer(ELFFile *file, const std::pair<int, int> &interval);
    std::vector<Container *> &getInnerContainers();
    ~SectionHeaderTableContainer();
};
}

#endif
