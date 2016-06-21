#ifndef PHT_ENTRY_CONTAINER_HPP_
#define PHT_ENTRY_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"
#include "util.hpp"
#include "program_header_table_container.hpp"

namespace elf
{
class PHTEntryContainer : public Container
{
public:
    PHTEntryContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index);
    std::vector<Container *> &getInnerContainers();
    ~PHTEntryContainer();
private:
    unsigned int index;
};
}

static struct
{
    const ELFIO::Elf_Word value;
    const char *string;
} p_type_strings[] =
{
    TO_STRING(PT_NULL),
    TO_STRING(PT_LOAD),
    TO_STRING(PT_DYNAMIC),
    TO_STRING(PT_INTERP),
    TO_STRING(PT_NOTE),
    TO_STRING(PT_SHLIB),
    TO_STRING(PT_PHDR),
    TO_STRING(PT_TLS),
    { 0, nullptr },
};

static struct
{
    const ELFIO::Elf_Word value;
    const char *string;
} p_flags_strings[] =
{
    TO_STRING(PF_X),
    TO_STRING(PF_W),
    TO_STRING(PF_R),
    { 0, nullptr },
};

#endif // PHT_ENTRY_CONTAINER_HPP_
