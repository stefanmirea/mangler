#ifndef SYMBOL_TABLE_ENTRY_CONTAINER_HPP_
#define SYMBOL_TABLE_ENTRY_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class SymbolTableEntryContainer : public Container
{
public:
	SymbolTableEntryContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index);
    std::vector<Container *> &getInnerContainers();

    unsigned int index;
    ~SymbolTableEntryContainer();
};
}
#endif // SYMBOL_TABLE_ENTRY_CONTAINER_HPP_
