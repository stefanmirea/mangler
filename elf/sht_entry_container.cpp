#include "sht_entry_container.hpp"
#include "util.hpp"

using namespace elf;

ShtEntryContainer::ShtEntryContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index) :
    Container(file, true, interval), index(index)
{
    ELFIO::elfio *elfData = file->getELFIO();
    ELFIO::section *entry = elfData->sections[index];

    if (entry)
    {
        setName(entry->get_name() + " header");
    }
}

std::vector<Container *> &ShtEntryContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        Container *container;
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
        ELFIO::elfio *elfData = efile->getELFIO();
        ELFIO::section *entry = elfData->sections[index];

        int offset = elfData->get_sections_offset() + index * elfData->get_section_entry_size();

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("sh_name: " + std::to_string(entry->get_name_string_offset()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        int sh_type = entry->get_type();
        std::string sh_type_string = "";

        switch(sh_type)
        {
            case SHT_NULL:
                sh_type_string = "SHT_NULL";
                break;
            case SHT_PROGBITS:
                sh_type_string = "SHT_PROGBITS";
                break;
            case SHT_SYMTAB :
                sh_type_string = "SHT_SYMTAB";
                break;
            case SHT_STRTAB:
                sh_type_string = "SHT_STRTAB";
                break;
            case SHT_RELA:
                sh_type_string = "SHT_RELA";
                break;
            case SHT_NOTE :
                sh_type_string = "SHT_NOTE";
                break;
            case SHT_REL:
                sh_type_string = "SHT_REL";
                break;
            case SHT_SHLIB:
                sh_type_string = "SHT_SHLIB";
                break;
            case SHT_DYNSYM:
                sh_type_string = "SHT_DYNSYM";
                break;
            case SHT_INIT_ARRAY:
                sh_type_string = "SHT_INIT_ARRAY";
                break;
            case SHT_FINI_ARRAY:
                sh_type_string = "SHT_FINI_ARRAY";
                break;
            case SHT_PREINIT_ARRAY:
                sh_type_string = "SHT_PREINIT_ARRAY";
                break;
            case SHT_GROUP:
                sh_type_string = "SHT_GROUP";
                break;
            case SHT_SYMTAB_SHNDX:
                sh_type_string = "SHT_SYMTAB_SHNDX";
                break;
            case SHT_LOOS:
                sh_type_string = "SHT_LOOS";
                break;
            case SHT_HIOS:
                sh_type_string = "SHT_HIOS";
                break;
            case SHT_LOPROC:
                sh_type_string = "SHT_LOPROC";
                break;
            case SHT_HIPROC:
                sh_type_string = "SHT_HIPROC";
                break;
            case SHT_LOUSER:
                sh_type_string = "SHT_LOUSER";
                break;
            case SHT_HIUSER:
                sh_type_string = "SHT_HIUSER";
                break;
            default:
                sh_type_string = printHex(sh_type);
                break;
        }

        container->setName("sh_type: " + sh_type_string);
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        std::string sh_flags_string = "";
        ELFIO::Elf_Xword flags = entry->get_flags();

        if (flags & SHF_WRITE)
            sh_flags_string += "SHF_WRITE ";
        if (flags & SHF_ALLOC)
            sh_flags_string += "SHF_ALLOC ";
        if (flags & SHF_EXECINSTR)
            sh_flags_string += "SHF_EXECINSTR ";
        if (flags & SHF_MERGE)
            sh_flags_string += "SHF_MERGE ";
        if (flags & SHF_STRINGS)
            sh_flags_string += "SHF_STRINGS ";
        if (flags & SHF_INFO_LINK)
            sh_flags_string += "SHF_INFO_LINK ";
        if (flags & SHF_LINK_ORDER)
            sh_flags_string += "SHF_LINK_ORDER ";
        if (flags & SHF_OS_NONCONFORMING)
            sh_flags_string += "SHF_OS_NONCONFORMING ";
        if (flags & SHF_GROUP)
            sh_flags_string += "SHF_GROUP ";
        if (flags & SHF_TLS)
            sh_flags_string += "SHF_TLS ";
        if (flags & SHF_GROUP)
            sh_flags_string += "SHF_MASKOS ";
        if (flags & SHF_TLS)
            sh_flags_string += "SHF_MASKPROC ";

        container->setName("sh_flags: " + sh_flags_string);
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Addr)));
        container->setName("sh_addr: " + printHex(entry->get_address()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Addr);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Off)));
        container->setName("sh_offset: " + printHex(entry->get_offset()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Off);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("sh_size: " + std::to_string(entry->get_size()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("sh_link: " + std::to_string(entry->get_link()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("sh_info: " + std::to_string(entry->get_info()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("sh_addralign: " + std::to_string(entry->get_addr_align()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("sh_entsize: " + std::to_string(entry->get_entry_size()));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);
    }

    return innerContainers;
}

ShtEntryContainer::~ShtEntryContainer()
{

}
