#ifndef RELOCATIONS_CONTAINER_HPP_
#define RELOCATIONS_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class RelocationsContainer : public Container
{
public:
    RelocationsContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index);
    std::vector<Container *> &getInnerContainers();
    ~RelocationsContainer();
private:
    unsigned int index;
};
}

#endif // RELOCATIONS_CONTAINER_HPP_
