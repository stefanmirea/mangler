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

#include "data_container.hpp"

using namespace elf;

DataContainer::DataContainer(ELFFile *file, const std::pair<int, int> &interval,
    unsigned int index) : Container(file, true, interval), index(index)
{
    ELFIO::elfio *elfData = file->getELFIO();
    ELFIO::section *entry = elfData->sections[index];
    setName(entry->get_name());
}

std::vector<Container *> &DataContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
        assert(efile != nullptr);
#endif
        ELFIO::elfio *interpretor = efile->getELFIO();

        ELFIO::section *current = interpretor->sections[index];
        std::pair<int, int> &currentInterval = getInterval();

        for (unsigned int s_index = 0; s_index < interpretor->get_sections_num(); s_index++)
            if (interpretor->sections[s_index]->get_type() == SHT_SYMTAB ||
                interpretor->sections[s_index]->get_type() == SHT_DYNSYM)
            {
                ELFIO::section *entry = interpretor->sections[s_index];
                ELFIO::symbol_section_accessor symbols(*interpretor, entry);
                for (unsigned int i = 0; i < symbols.get_symbols_num(); i++)
                {
                    std::string name;
                    ELFIO::Elf64_Addr value;
                    ELFIO::Elf_Xword size;
                    unsigned char bind;
                    unsigned char type;
                    ELFIO::Elf_Half section_index;
                    unsigned char other;
                    symbols.get_symbol(i, name, value, size, bind, type, section_index, other);
                    if (section_index == index)
                    {
                        std::pair<int, int> interval;
                        interval.first = current->get_offset() + value - current->get_address();
                        interval.second = interval.first + size;
                        if (interval.first < currentInterval.first ||
                            interval.second > currentInterval.second)
                            interval.first = interval.second = current->get_offset();
                        Container *container = new Container(efile, false, interval);
                        if (name != "")
                            container->setName(name);
                        else
                            container->setName("Symbol no. " + std::to_string(i) + " in " +
                                               entry->get_name());
                        addInnerContainer(container);
                    }
                }
            }
    }

    return innerContainers;
}

DataContainer::~DataContainer() {}
