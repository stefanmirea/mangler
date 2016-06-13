#ifndef SHT_ENTRY_CONTAINER_HPP_
#define SHT_ENTRY_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class ShtEntryContainer : public Container
{
public:
    ShtEntryContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index);
    std::vector<Container *> &getInnerContainers();

    unsigned int index;
    ~ShtEntryContainer();
};
}
#endif // SHT_ENTRY_CONTAINER_HPP_
