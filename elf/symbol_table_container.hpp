#ifndef SYMBOL_TABLE_CONTAINER_HPP_
#define SYMBOL_TABLE_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class SymbolTableContainer : public Container
{
public:
	SymbolTableContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index);
    std::vector<Container *> &getInnerContainers();
    ~SymbolTableContainer();
private:
    unsigned int index;
};
}
#endif // SYMBOL_TABLE_CONTAINER_HPP_
