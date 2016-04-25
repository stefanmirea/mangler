#include "program_header_table_container.hpp"

using namespace elf;

ProgramHeaderTableContainer::ProgramHeaderTableContainer(ELFFile *file,
    const std::pair<int, int> &interval) : Container(file, true, interval)
{
    setName("Program header table");
}

std::vector<Container *> &ProgramHeaderTableContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        Container *container = new Container(getFile(), false, std::make_pair(10, 20));
        container->setName("Nothing here");
        addInnerContainer(container);
    }
    return innerContainers;
}

ProgramHeaderTableContainer::~ProgramHeaderTableContainer() {}
