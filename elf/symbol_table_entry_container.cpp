/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Ștefan-Gabriel Mirea, Adrian Dobrică
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "symbol_table_entry_container.hpp"
#include "util.hpp"

using namespace elf;

SymbolTableEntryContainer::SymbolTableEntryContainer(ELFFile *file,
                                                     const std::pair<int, int> &interval,
                                                     unsigned int sectionIndex,
                                                     unsigned int symbolIndex) :
    Container(file, true, interval), sectionIndex(sectionIndex), symbolIndex(symbolIndex)
{
    const ELFIO::elfio *elfData = file->getELFIO();
    ELFIO::section *entry = elfData->sections[sectionIndex];
    ELFIO::symbol_section_accessor symbol(*elfData, entry);

    std::string name;
    ELFIO::Elf64_Addr value;
    ELFIO::Elf_Xword size;
    unsigned char bind;
    unsigned char type;
    ELFIO::Elf_Half section_index;
    unsigned char other;

    symbol.get_symbol(symbolIndex, name, value, size, bind, type, section_index, other);

    if (entry)
    {
        if (name != "")
            setName(std::to_string(symbolIndex) + ": " + name);
        else
            setName(std::to_string(symbolIndex) + ": [unnamed]");
    }
}

std::vector<Container *> &SymbolTableEntryContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        Container *container;
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
        const ELFIO::elfio *elfData = efile->getELFIO();
        ELFIO::section *entry = elfData->sections[sectionIndex];
        ELFIO::symbol_section_accessor symbol(*elfData, entry);

        std::pair<int, int> interval;
        interval.first = entry->get_offset() + symbolIndex * entry->get_entry_size();
        interval.second = interval.first + entry->get_entry_size();

        std::string name;
        ELFIO::Elf64_Addr value;
        ELFIO::Elf_Xword size;
        unsigned char bind;
        unsigned char type;
        ELFIO::Elf_Half section_index;
        unsigned char other;

        symbol.get_symbol(symbolIndex, name, value, size, bind, type, section_index, other);

        int offset = interval.first;
        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        container->setName("st_name: " + ("\"" + name) + "\"");
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Word);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Addr)));
        container->setName("st_value: " + printHex(value));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Addr);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Addr)));
        container->setName("st_size: " + std::to_string(size));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Addr);

        std::string bind_string = "";

        switch(bind)
        {
            case STB_LOCAL:
                bind_string = "STB_LOCAL";
                break;
            case STB_GLOBAL:
                bind_string = "STB_GLOBAL";
                break;
            case STB_WEAK:
                bind_string = "STB_WEAK";
                break;
            case STB_LOPROC:
                bind_string = "STB_LOPROC";
                break;
            case STB_HIPROC:
                bind_string = "STB_HIPROC";
                break;
            default:
                bind_string = printHex(bind);
                break;
        }

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(unsigned char)));
        std::string type_string = "";

        switch(type)
        {
            case STT_NOTYPE:
                type_string = "STT_NOTYPE";
                break;
            case STT_OBJECT:
                type_string = "STT_OBJECT";
                break;
            case STT_FUNC:
                type_string = "STT_FUNC";
                break;
            case STT_SECTION:
                type_string = "STT_SECTION";
                break;
            case STT_FILE:
                type_string = "STT_FILE";
                break;
            case STT_LOPROC:
                type_string = "STT_LOPROC";
                break;
            case STT_HIPROC:
                type_string = "STT_HIPROC";
                break;
            default:
                type_string = printHex(type);
                break;
        }

        container->setName("st_info: " + bind_string + " " + type_string);
        addInnerContainer(container);
        offset += sizeof(unsigned char);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(unsigned char)));
        container->setName("st_other: " + std::to_string(other));
        addInnerContainer(container);
        offset += sizeof(unsigned char);

        container = new Container(getFile(), false, std::make_pair(offset, offset + sizeof(unsigned char)));
        container->setName("st_shndx: " + std::to_string(section_index));
        addInnerContainer(container);
        offset += sizeof(unsigned char);
    }

    return innerContainers;
}

SymbolTableEntryContainer::~SymbolTableEntryContainer()
{

}
