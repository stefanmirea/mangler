/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Adrian Dobrică, Ștefan-Gabriel Mirea
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

#include "relocation_info_container.hpp"

using namespace elf;

RelocationInfoContainer::RelocationInfoContainer(ELFFile *file,
    const std::pair<int, int> &interval, unsigned int sectionIndex, unsigned int relocationIndex) :
    Container(file, true, interval), sectionIndex(sectionIndex), relocationIndex(relocationIndex)
{
    ELFIO::elfio *elfData = file->getELFIO();
    ELFIO::section *entry = elfData->sections[sectionIndex];

    const ELFIO::Elf32_Rel *pEntry = reinterpret_cast<const ELFIO::Elf32_Rel *>(entry->get_data() +
        relocationIndex * entry->get_entry_size());
    const ELFIO::endianess_convertor &convertor = elfData->get_convertor();
    ELFIO::Elf_Word r_info = convertor(pEntry->r_info);

    setName("r_info: " + printHex(r_info));
}

std::vector<Container *> &RelocationInfoContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
        assert(efile != nullptr);
#endif
        ELFIO::elfio *interpretor = efile->getELFIO();
        ELFIO::section *section = interpretor->sections[sectionIndex];
        ELFIO::relocation_section_accessor relocations(*interpretor, section);

        int offset = section->get_offset() + relocationIndex * section->get_entry_size() +
            sizeof(ELFIO::Elf32_Addr);

        ELFIO::Elf64_Addr r_offset;
        ELFIO::Elf_Word symbol;
        ELFIO::Elf_Word type;
        ELFIO::Elf_Sxword addend;
        relocations.get_entry(relocationIndex, r_offset, symbol, type, addend);

        Container *symbolContainer, *typeContainer;
        if (interpretor->get_encoding() == ELFDATA2LSB)
        {
            typeContainer = new Container(efile, false, std::make_pair(offset, offset + 1));
            ++offset;
            symbolContainer = new Container(efile, false, std::make_pair(offset,
                offset + sizeof(ELFIO::Elf32_Word) - 1));
        }
        else
        {
            symbolContainer = new Container(efile, false, std::make_pair(offset, offset +
                sizeof(ELFIO::Elf32_Word) - 1));
            offset += sizeof(ELFIO::Elf32_Word) - 1;
            typeContainer = new Container(efile, false, std::make_pair(offset, offset + 1));
        }

        symbolContainer->setName("ELF32_R_SYM: " + std::to_string(symbol));
        bool found = false;
        for (unsigned int i = 0; r_type_strings[i].string; ++i)
            if (r_type_strings[i].value == type)
            {
                typeContainer->setName(std::string("ELF32_R_TYPE: ") + r_type_strings[i].string);
                found = true;
                break;
            }
        if (!found)
            typeContainer->setName("ELF32_R_TYPE: " + printHex(type));

        addInnerContainer(symbolContainer);
        addInnerContainer(typeContainer);
    }
    return innerContainers;
}

RelocationInfoContainer::~RelocationInfoContainer() {}
