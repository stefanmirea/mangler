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

#include "segment_contents_container.hpp"
#include "segment_container.hpp"
#include "program_header_table_container.hpp"

using namespace elf;

SegmentContentsContainer::SegmentContentsContainer(ELFFile *file) : Container(file, true)
{
    setName("Segment contents");
}

std::vector<Container *> &SegmentContentsContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        Container *container;

        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
        assert(efile != nullptr);
#endif
        ELFIO::elfio *interpretor = efile->getELFIO();

        for (unsigned int i = 0; i < interpretor->get_segments_num(); ++i)
        {
            ELFIO::segment *segment = interpretor->segments[i];
            std::pair<int, int> interval;
            interval.first = segment->get_offset();
            interval.second = interval.first + segment->get_file_size();
            if (segment->get_sections_num())
                container = new SegmentContainer(efile, interval, i);
            else
            {
                container = new Container(efile, false, interval);
                container->setName(ProgramHeaderTableContainer::getSegmentTitle(efile, i));
            }
            addInnerContainer(container);
        }
    }
    return innerContainers;
}

SegmentContentsContainer::~SegmentContentsContainer() {}
