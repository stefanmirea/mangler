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
