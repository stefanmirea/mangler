#include "segment_contents_container.hpp"

using namespace elf;

SegmentContentsContainer::SegmentContentsContainer(ELFFile *file) : Container(file, true)
{
    setName("Segment contents");
}

std::vector<Container *> &SegmentContentsContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        Container *container = new Container(getFile(), false);
        container->setName("Nothing here");
        addInnerContainer(container);
    }
    return innerContainers;
}

SegmentContentsContainer::~SegmentContentsContainer() {}
