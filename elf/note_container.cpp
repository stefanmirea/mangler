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

#include "note_container.hpp"
#include "note_entry_container.hpp"
#include "util.hpp"

using namespace elf;

NoteContainer::NoteContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index) :
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

std::vector<Container *> &NoteContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
        ELFIO::elfio *elfData = efile->getELFIO();
        ELFIO::section *entry = elfData->sections[index];
        ELFIO::note_section_accessor notes(*elfData, entry);

        std::vector<ELFIO::Elf_Xword> note_position(notes.note_start_positions);
        note_position.push_back(entry->get_size());

        for(unsigned int i = 0; i < note_position.size() - 1; i++)
        {
            NoteEntryContainer *container;
            std::pair<int, int> interval;
            interval.first = entry->get_offset() + i * (note_position[i + 1] - note_position[i]);
            interval.second = interval.first + (note_position[i + 1] - note_position[i]);

            container = new NoteEntryContainer(efile, interval, index, i, note_position[i],
                                               note_position[i + 1] - note_position[i]);
            addInnerContainer(container);
        }
    }

    return innerContainers;
}

NoteContainer::~NoteContainer()
{

}
