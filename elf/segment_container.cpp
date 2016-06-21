#include "segment_container.hpp"
#include "pht_entry_container.hpp"
#include "section_contents_container.hpp"
#include "util.hpp"
#include <iomanip>
#include <sstream>

using namespace elf;

SegmentContainer::SegmentContainer(ELFFile *file, const std::pair<int, int> &interval,
    unsigned int index) : Container(file, true, interval), index(index)
{
    setName(ProgramHeaderTableContainer::getSegmentTitle(file, index));
}

std::vector<Container *> &SegmentContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
        assert(efile != nullptr);
#endif
        ELFIO::elfio *interpretor = efile->getELFIO();
        ELFIO::segment *segment = interpretor->segments[index];

        std::vector<Container *> &topLevel = efile->getTopLevelContainers();
        SectionContentsContainer *sectionContents =
            dynamic_cast<SectionContentsContainer *>(topLevel[4]);
#ifdef DEBUG
        assert(sectionContents != nullptr);
#endif
        std::vector<Container *> &sections = sectionContents->getInnerContainers();

        for (unsigned int i = 0; i < segment->get_sections_num(); ++i)
            addInnerContainer(sections[segment->get_section_index_at(i)]);
    }

    return innerContainers;
}

SegmentContainer::~SegmentContainer() {}
