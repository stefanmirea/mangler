#include "pht_entry_container.hpp"
#include "util.hpp"
#include <iomanip>
#include <sstream>

using namespace elf;

PHTEntryContainer::PHTEntryContainer(ELFFile *file, const std::pair<int, int> &interval,
    unsigned int index) : Container(file, true, interval), index(index)
{
    ELFIO::elfio *elfData = file->getELFIO();
    ELFIO::segment *segment = elfData->segments[index];
#ifdef DEBUG
    assert(segment != nullptr);
#endif
    ELFIO::Elf_Half segments_num = elfData->get_segments_num();

    int digits = 0;
    do {
        ++digits;
        segments_num /= 10;
    } while (segments_num);

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(digits) << index << ": ";

    ELFIO::Elf_Word p_type = segment->get_type();
    bool found = false;
    for (unsigned int i = 0; p_type_strings[i].string; ++i)
        if (p_type == p_type_strings[i].value)
        {
            ss << p_type_strings[i].string;
            found = true;
            break;
        }
    if (!found)
        ss << printHex(p_type);
    ss << ", ";

    bool first = true;
    ELFIO::Elf_Word p_flags = segment->get_flags();
    for (unsigned int i = 0; p_flags_strings[i].string; ++i)
        if (p_flags & p_flags_strings[i].value)
        {
            if (!first)
                ss << '+';
            ss << p_flags_strings[i].string;
            first = false;
        }

    setName(ss.str() + " header");
}

std::vector<Container *> &PHTEntryContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
        assert(efile != nullptr);
#endif
        ELFIO::elfio *interpretor = efile->getELFIO();
        ELFIO::segment *segment = interpretor->segments[index];

        int offset = interpretor->get_segments_offset() +
                     index * interpretor->get_segment_entry_size();

        Container *container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        ELFIO::Elf_Word p_type = segment->get_type();
        bool found = false;
        for (unsigned int i = 0; p_type_strings[i].string; ++i)
            if (p_type == p_type_strings[i].value)
            {
                container->setName(std::string("p_type: ") + p_type_strings[i].string);
                found = true;
                break;
            }
        if (!found)
            container->setName("p_type: " + printHex(p_type));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Off)));
        container->setName("p_offset: " + printHex(segment->get_offset()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Off);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Addr)));
        container->setName("p_vaddr: " + printHex(segment->get_virtual_address()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Addr);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Addr)));
        container->setName("p_paddr: " + printHex(segment->get_physical_address()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Addr);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("p_filesz: " + printHex(segment->get_file_size()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("p_memsz: " + printHex(segment->get_memory_size()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        bool first = true;
        std::string name;
        ELFIO::Elf_Word p_flags = segment->get_flags();
        for (unsigned int i = 0; p_flags_strings[i].string; ++i)
            if (p_flags & p_flags_strings[i].value)
            {
                if (!first)
                    name += '+';
                name += p_flags_strings[i].string;
                first = false;
            }
        container->setName("p_flags: " + name);
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("p_align: " + printHex(segment->get_align()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);
    }

    return innerContainers;
}

PHTEntryContainer::~PHTEntryContainer() {}
