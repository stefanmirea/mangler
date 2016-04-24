#ifndef SECTION_CONTENTS_CONTAINER_HPP_
#define SECTION_CONTENTS_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class SectionContentsContainer : public Container
{
public:
    SectionContentsContainer(ELFFile *file);
    std::vector<Container *> &getInnerContainers();
    ~SectionContentsContainer();
};
}

#endif
