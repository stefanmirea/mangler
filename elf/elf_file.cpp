#include "elf_file.hpp"
#include "elf_header_container.hpp"
#include "program_header_table_container.hpp"
#include "section_header_table_container.hpp"
#include "segment_contents_container.hpp"
#include "section_contents_container.hpp"
#include <utility>

using namespace elf;

ELFFile::ELFFile(const std::string &filename) : FileUnit(filename)
{
    file = new ELFIO::elfio();
    open = file->load(filename);

    std::vector<Container *> &topLevelContainers = getTopLevelContainers();
    topLevelContainers.push_back(new ELFHeaderContainer(this, std::make_pair(0, 10)));
    topLevelContainers.push_back(new ProgramHeaderTableContainer(this, std::make_pair(10, 20)));
    topLevelContainers.push_back(new SectionHeaderTableContainer(this, std::make_pair(20, 30)));
    topLevelContainers.push_back(new SegmentContentsContainer(this));
    topLevelContainers.push_back(new SectionContentsContainer(this));
}

ELFFile::~ELFFile()
{
    delete file;
}

bool ELFFile::getOpenStatus()
{
    return open;
}

bool ELFFile::save(std::string &filename)
{
    return file->save(filename);
}

void ELFFile::modifyHex(size_t offset, std::string &newContent) {}
