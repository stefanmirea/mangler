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
