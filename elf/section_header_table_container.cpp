#include "section_header_table_container.hpp"

using namespace elf;

SectionHeaderTableContainer::SectionHeaderTableContainer(ELFFile *file,
    const std::pair<int, int> &interval) : Container(file, true, interval)
{
    setName("Section header table");
}

std::vector<Container *> &SectionHeaderTableContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        Container *container = new Container(getFile(), false);
        container->setName("Nothing here");
        addInnerContainer(container);
    }
    return innerContainers;
}

SectionHeaderTableContainer::~SectionHeaderTableContainer() {}
