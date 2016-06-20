#include "note_entry_container.hpp"
#include "util.hpp"

using namespace elf;

NoteEntryContainer::NoteEntryContainer(ELFFile *file,
                                       const std::pair<int, int> &interval,
                                       unsigned int sectionIndex,
                                       unsigned int noteIndex,
                                       unsigned int noteStart,
                                       unsigned int noteSize) :
    Container(file, true, interval), sectionIndex(sectionIndex),
    noteIndex(noteIndex), noteSize(noteSize), noteStart(noteStart)
{
    const ELFIO::elfio *elfData = file->getELFIO();
    ELFIO::section *entry = elfData->sections[sectionIndex];
    ELFIO::note_section_accessor notes(*elfData, entry);

    ELFIO::Elf_Word type;
    std::string name;
    ELFIO::Elf_Word nameSz;
    void *desc;
    ELFIO::Elf_Word descSize;

    notes.get_note(noteIndex, type, name, desc, descSize, nameSz);

    if (entry)
    {
        if (name != "")
            setName(std::to_string(noteIndex) + ": " + name);
        else
            setName(std::to_string(noteIndex) + ": " + "[unnamed]");
    }
}

std::vector<Container *> &NoteEntryContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        Container *container;
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
        const ELFIO::elfio *elfData = efile->getELFIO();
        ELFIO::section *entry = elfData->sections[sectionIndex];
        ELFIO::note_section_accessor notes(*elfData, entry);

        std::pair<int, int> interval;
        interval.first = entry->get_offset() + noteStart;

        ELFIO::Elf_Word type;
        std::string name;
        ELFIO::Elf_Word nameSz;
        void *desc;
        ELFIO::Elf_Word descSize;

        notes.get_note(noteIndex, type, name, desc, descSize, nameSz);

        interval.second = interval.first + sizeof(ELFIO::Elf_Word);
        std::string nameSz_string = std::to_string(nameSz);
        container = new Container(getFile(), false, interval);
        container->setName("namesz: " + nameSz_string);
        addInnerContainer(container);
        interval.first = interval.second;

        interval.second = interval.first + sizeof(ELFIO::Elf_Word);
        std::string descSize_string = std::to_string(descSize);
        container = new Container(getFile(), false, interval);
        container->setName("descsz: " + descSize_string);
        addInnerContainer(container);
        interval.first = interval.second;

        interval.second = interval.first + sizeof(ELFIO::Elf_Word);
        std::string type_string = printHex(type);
        container = new Container(getFile(), false, interval);
        container->setName("type: " + type_string);
        addInnerContainer(container);
        interval.first = interval.second;

        int wordsize = sizeof(ELFIO::Elf_Word);
        unsigned int nameAlignedSize = nameSz;

        if (nameSz % wordsize != 0)
        {
            int div = nameSz / wordsize;
            div++;
            nameAlignedSize = div * wordsize;
        }

        interval.second = interval.first + nameAlignedSize;
        container = new Container(getFile(), false, interval);
        container->setName("name: " + name);
        addInnerContainer(container);
        interval.first = interval.second;

        unsigned int descAlignedSize = descSize;

        if (descSize % wordsize != 0)
        {
            int div = descSize / wordsize;
            div++;
            descAlignedSize = div * wordsize;
        }

        interval.second = interval.first + descAlignedSize;
        container = new Container(getFile(), false, interval);
        container->setName("desc");
        addInnerContainer(container);
    }

    return innerContainers;
}

NoteEntryContainer::~NoteEntryContainer()
{

}
