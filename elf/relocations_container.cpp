#include "relocations_container.hpp"
#include "relocation_entry_container.hpp"

using namespace elf;

RelocationsContainer::RelocationsContainer(ELFFile *file, const std::pair<int, int> &interval,
    unsigned int index) : Container(file, true, interval), index(index)
{
    ELFIO::elfio *elfData = file->getELFIO();
    ELFIO::section *entry = elfData->sections[index];

    if (entry)
    {
        std::string section_name(entry->get_name());
        if (section_name != "")
            setName(section_name);
        else
            setName("[unnamed]");
    }
}

std::vector<Container *> &RelocationsContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
        assert(efile != nullptr);
#endif
        ELFIO::elfio *elfData = efile->getELFIO();
        ELFIO::section *entry = elfData->sections[index];
        ELFIO::relocation_section_accessor relocations(*elfData, entry);

        for (unsigned int i = 0; i < relocations.get_entries_num(); ++i)
        {
            std::pair<int, int> interval;
            interval.first = entry->get_offset() + i * entry->get_entry_size(); 
            interval.second = interval.first + entry->get_entry_size();
            RelocationEntryContainer *container =
                new RelocationEntryContainer(efile, interval, index, i);
            addInnerContainer(container);
        }
    }

    return innerContainers;
}

RelocationsContainer::~RelocationsContainer()
{

}
