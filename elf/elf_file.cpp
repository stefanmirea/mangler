/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Ștefan-Gabriel Mirea, Adrian Dobrică
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

#include "elf_file.hpp"
#include "elf_header_container.hpp"
#include "program_header_table_container.hpp"
#include "section_header_table_container.hpp"
#include "segment_contents_container.hpp"
#include "section_contents_container.hpp"
#include <utility>

using namespace elf;

ELFFile::ELFFile(const std::string &filename) : FileUnit(filename), formatName("ELF")
{
    loadFile(filename);
}

const std::string &ELFFile::getFormatName()
{
    return formatName;
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

ELFIO::elfio *ELFFile::getELFIO()
{
    return file;
}

bool ELFFile::loadFile(const std::string &filename)
{
    file = new ELFIO::elfio();
    try
    {
        open = file->load(filename);
    }
    catch (std::exception &e)
    {
#ifdef DEBUG
        std::cerr << "Caught " << e.what() << " in LEFIO::load.\n";
#endif
        open = false;
    }

    if (open && file->get_type() != ET_EXEC)
        open = false;

    std::vector<Container *> &topLevelContainers = getTopLevelContainers();
    topLevelContainers.clear();

    if (open)
    {
        topLevelContainers.push_back(new ELFHeaderContainer(this, std::make_pair(0, file->get_header_size())));
        topLevelContainers.push_back(new ProgramHeaderTableContainer(this, std::make_pair(10, 20)));
        topLevelContainers.push_back(new SectionHeaderTableContainer(this, std::make_pair(20, 30)));
        topLevelContainers.push_back(new SegmentContentsContainer(this));
        topLevelContainers.push_back(new SectionContentsContainer(this));
    }

    return open;
}
