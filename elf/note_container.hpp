#ifndef NOTE_CONTAINER_HPP_
#define NOTE_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class NoteContainer : public Container
{
public:
    NoteContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index);
    std::vector<Container *> &getInnerContainers();

    unsigned int index;
    ~NoteContainer();
};
}
#endif // NOTE_CONTAINER_HPP_
