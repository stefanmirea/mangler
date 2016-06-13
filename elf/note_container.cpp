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
        setName(entry->get_name());
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
