#ifndef SHT_ENTRY_CONTAINER_HPP_
#define SHT_ENTRY_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class SHTEntryContainer : public Container
{
public:
    SHTEntryContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index);
    std::vector<Container *> &getInnerContainers();
    ~SHTEntryContainer();
private:
    unsigned int index;
};
}
#endif // SHT_ENTRY_CONTAINER_HPP_
