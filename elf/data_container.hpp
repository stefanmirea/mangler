#ifndef DATA_CONTAINER_HPP_
#define DATA_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class DataContainer : public Container
{
public:
    DataContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index);
    std::vector<Container *> &getInnerContainers();
    ~DataContainer();
private:
    unsigned int index;
};
}

#endif // DATA_CONTAINER_HPP_
