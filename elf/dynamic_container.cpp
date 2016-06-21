#include "dynamic_container.hpp"
#include "dynamic_entry_container.hpp"

using namespace elf;

DynamicContainer::DynamicContainer(ELFFile *file, const std::pair<int, int> &interval,
    unsigned int index) : Container(file, true, interval), index(index)
{
    ELFIO::elfio *elfData = file->getELFIO();
    ELFIO::section *entry = elfData->sections[index];

    setName(entry->get_name());
}

std::vector<Container *> &DynamicContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
        assert(efile != nullptr);
#endif
        ELFIO::elfio *elfData = efile->getELFIO();
        ELFIO::section *entry = elfData->sections[index];
        ELFIO::dynamic_section_accessor dynamic(*elfData, entry);

        for (unsigned int i = 0; i < dynamic.get_entries_num(); ++i)
        {
            std::pair<int, int> interval;
            interval.first = entry->get_offset() + i * entry->get_entry_size();
            interval.second = interval.first + entry->get_entry_size();
            DynamicEntryContainer *container =
                new DynamicEntryContainer(efile, interval, index, i);
            addInnerContainer(container);
        }
    }

    return innerContainers;
}

DynamicContainer::~DynamicContainer() {}
