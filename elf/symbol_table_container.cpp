#include "symbol_table_container.hpp"
#include "symbol_table_entry_container.hpp"
#include "util.hpp"

using namespace elf;

SymbolTableContainer::SymbolTableContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index) :
    Container(file, true, interval), index(index)
{
    ELFIO::elfio *elfData = file->getELFIO();
    ELFIO::section *entry = elfData->sections[index];

    if (entry)
    {
        setName(entry->get_name());
    }
}

std::vector<Container *> &SymbolTableContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
        ELFIO::elfio *elfData = efile->getELFIO();
        ELFIO::section *entry = elfData->sections[index];
        ELFIO::symbol_section_accessor symbols(*elfData, entry);

        for (unsigned int i = 0; i < symbols.get_symbols_num(); i++)
        {
            SymbolTableEntryContainer *container;
            std::pair<int, int> interval;
            interval.first = entry->get_offset() + i * entry->get_entry_size();
            interval.second = interval.first + entry->get_entry_size();

            container = new SymbolTableEntryContainer(efile, interval, index, i);
            addInnerContainer(container);
        }
    }

    return innerContainers;
}

SymbolTableContainer::~SymbolTableContainer()
{

}
