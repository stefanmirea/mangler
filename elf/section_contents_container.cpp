#include "section_contents_container.hpp"

using namespace elf;

SectionContentsContainer::SectionContentsContainer(ELFFile *file) : Container(file, true)
{
    setName("Section contents");
}

std::vector<Container *> &SectionContentsContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        Container *container = new Container(getFile(), false);
        container->setName("Nothing here");
        addInnerContainer(container);
    }
    return innerContainers;
}

SectionContentsContainer::~SectionContentsContainer() {}
