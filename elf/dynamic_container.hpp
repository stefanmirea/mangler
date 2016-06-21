#ifndef DYNAMIC_CONTAINER_HPP_
#define DYNAMIC_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class DynamicContainer : public Container
{
public:
    DynamicContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index);
    std::vector<Container *> &getInnerContainers();
    ~DynamicContainer();
private:
    unsigned int index;
};
}

#endif // DYNAMIC_CONTAINER_HPP_
