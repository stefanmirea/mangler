#ifndef SEGMENT_CONTAINER_HPP_
#define SEGMENT_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"
#include "util.hpp"

namespace elf
{
class SegmentContainer : public Container
{
public:
    SegmentContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index);
    std::vector<Container *> &getInnerContainers();
    ~SegmentContainer();
private:
    unsigned int index;
};
}

#endif // SEGMENT_CONTAINER_HPP_
