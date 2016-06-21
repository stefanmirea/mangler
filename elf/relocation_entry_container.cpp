#include "relocation_entry_container.hpp"
#include "relocation_info_container.hpp"
#include "util.hpp"

using namespace elf;

RelocationEntryContainer::RelocationEntryContainer(ELFFile *file,
    const std::pair<int, int> &interval, unsigned int sectionIndex, unsigned int relocationIndex) :
    Container(file, true, interval), sectionIndex(sectionIndex), relocationIndex(relocationIndex)
{
    ELFIO::elfio *elfData = file->getELFIO();
    ELFIO::section *entry = elfData->sections[sectionIndex];
    ELFIO::relocation_section_accessor relocations(*elfData, entry);

    /* Get both the symbol index and the symbol name. */
    ELFIO::Elf_Word symbol;
    ELFIO::Elf_Word type;
    ELFIO::Elf_Sxword addend;
    ELFIO::Elf64_Addr symbolValue;
    std::string symbolName;
    ELFIO::Elf_Sxword calcValue;
    relocations.get_entry(relocationIndex, r_offset, symbol, type, addend);
    relocations.get_entry(relocationIndex, r_offset, symbolValue, symbolName, type, addend,
                          calcValue);

    std::string name = "Relocation for ";
    if (symbolName == "")
        name += "symbol no. " + std::to_string(symbol);
    else
        name += symbolName;
    setName(name);
}

std::vector<Container *> &RelocationEntryContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
        assert(efile != nullptr);
#endif
        ELFIO::elfio *interpretor = efile->getELFIO();

        ELFIO::section *section = interpretor->sections[sectionIndex];
        int offset = section->get_offset() + relocationIndex * section->get_entry_size();

        Container *container = new Container(efile, false, std::make_pair(offset, offset +
            sizeof(ELFIO::Elf32_Addr)));
        container->setName("r_offset: " + printHex(r_offset));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Addr);

        container = new RelocationInfoContainer(efile,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)), sectionIndex,
            relocationIndex);
        addInnerContainer(container);
    }
    return innerContainers;
}

RelocationEntryContainer::~RelocationEntryContainer() {}
