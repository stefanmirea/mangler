#ifndef SEGMENT_CONTENTS_CONTAINER_HPP_
#define SEGMENT_CONTENTS_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class SegmentContentsContainer : public Container
{
public:
    SegmentContentsContainer(ELFFile *file);
    std::vector<Container *> &getInnerContainers();
    ~SegmentContentsContainer();
};
}

#endif
