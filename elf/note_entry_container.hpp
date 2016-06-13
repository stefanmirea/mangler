#ifndef NOTE_ENTRY_CONTAINER_HPP_
#define NOTE_ENTRY_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class NoteEntryContainer : public Container
{
public:
    NoteEntryContainer(ELFFile *file, const std::pair<int, int> &interval,
                                             unsigned int sectionIndex,
                                             unsigned int noteIndex,
                                             unsigned int noteStart,
                                             unsigned int noteSize);
    std::vector<Container *> &getInnerContainers();

    unsigned int sectionIndex;
    unsigned int noteIndex;
    unsigned int noteSize;
    unsigned int noteStart;
    ~NoteEntryContainer();
};
}
#endif // SYMBOL_TABLE_ENTRY_CONTAINER_HPP_
