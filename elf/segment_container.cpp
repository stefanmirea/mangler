/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Adrian Dobrică, Ștefan-Gabriel Mirea
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
