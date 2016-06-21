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

#include "program_header_table_container.hpp"
#include "pht_entry_container.hpp"
#include <iomanip>
#include <sstream>

using namespace elf;

ProgramHeaderTableContainer::ProgramHeaderTableContainer(ELFFile *file,
    const std::pair<int, int> &interval) : Container(file, true, interval)
{
    setName("Program header table");
}

std::vector<Container *> &ProgramHeaderTableContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *file = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
        assert(file != nullptr);
#endif
        ELFIO::elfio *interpretor = file->getELFIO();

        for (unsigned int i = 0; i < interpretor->get_segments_num(); ++i)
        {
            std::pair<int, int> entry_interval;
            entry_interval.first = interpretor->get_segments_offset() +
                                   i * interpretor->get_segment_entry_size();
            entry_interval.second = entry_interval.first + interpretor->get_segment_entry_size();
            PHTEntryContainer *entry = new PHTEntryContainer(file, entry_interval, i);
            addInnerContainer(entry);
        }
    }
    return innerContainers;
}

std::string ProgramHeaderTableContainer::getSegmentTitle(ELFFile *file, unsigned int index)
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

    return ss.str();
}

ProgramHeaderTableContainer::~ProgramHeaderTableContainer() {}
