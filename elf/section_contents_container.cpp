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
        Container *container;

        container = new Container(getFile(), false, std::make_pair(30, 40));
        container->setName("[test] non-code section");
        addInnerContainer(container);

        container = new CodeContainer(getFile(), std::make_pair(40, 50));
        container->setName("[test] code section");
        addInnerContainer(container);
    }
    return innerContainers;
}

SectionContentsContainer::~SectionContentsContainer() {}
