#ifndef ELF_HEADER_CONTAINER_HPP_
#define ELF_HEADER_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class ELFHeaderContainer : public Container
{
public:
    ELFHeaderContainer(ELFFile *file, const std::pair<int, int> &interval);
    std::vector<Container *> &getInnerContainers();
    ~ELFHeaderContainer();
};
}

#endif
