#ifndef PROGRAM_HEADER_TABLE_CONTAINER_HPP_
#define PROGRAM_HEADER_TABLE_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"

namespace elf
{
class ProgramHeaderTableContainer : public Container
{
public:
    ProgramHeaderTableContainer(ELFFile *file, const std::pair<int, int> &interval);
    std::vector<Container *> &getInnerContainers();
    ~ProgramHeaderTableContainer();
};
}

#endif
