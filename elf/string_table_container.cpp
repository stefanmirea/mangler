#include "string_table_container.hpp"
#include "util.hpp"

using namespace elf;

StringTableContainer::StringTableContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index) :
    Container(file, true, interval), index(index)
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

std::vector<Container *> &StringTableContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *handler = dynamic_cast<ELFFile *>(getFile());
        ELFIO::elfio *elfData = handler->getELFIO();
        ELFIO::section *entry = elfData->sections[index];
        std::pair<int, int> interval;

        interval.first = entry->get_offset();
        interval.second = interval.first;

        ELFIO::string_section_accessor stringAccess(entry);

        unsigned int pos = 0;
        unsigned int sectionSize = entry->get_size();
        unsigned int entryOffset = entry->get_offset();

        while (pos < sectionSize)
        {
            std::string entry_string = std::string(stringAccess.get_string(pos));
            interval.first = entryOffset + pos;
            interval.second = interval.first + entry_string.size() + 1;
            Container *container = new Container(getFile(), false, interval);
            if (entry_string != "")
                container->setName(entry_string);
            else
                container->setName("[blank]");
            addInnerContainer(container);

            pos += (entry_string.size() + 1);
        }
    }

    return innerContainers;
}

StringTableContainer::~StringTableContainer()
{

}
