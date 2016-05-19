#include "elf_entry.hpp"

using namespace elf;

ELFEntry::ELFEntry(ELFFile *file, const std::pair<int, int> &interval) :
    Container(file, false, interval)
{

}
