#ifndef STRING_TABLE_CONTAINER_HPP_
#define STRING_TABLE_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class StringTableContainer : public Container
{
public:
	StringTableContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index);
    std::vector<Container *> &getInnerContainers();
    ~StringTableContainer();
private:
    unsigned int index;
};
}
#endif // STRING_TABLE_CONTAINER_HPP_
