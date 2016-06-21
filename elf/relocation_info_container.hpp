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

#ifndef RELOCATION_INFO_CONTAINER_HPP_
#define RELOCATION_INFO_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"
#include "util.hpp"

namespace elf
{
class RelocationInfoContainer : public Container
{
public:
    RelocationInfoContainer(ELFFile *file, const std::pair<int, int> &interval,
                            unsigned int sectionIndex, unsigned int relocationIndex);
    std::vector<Container *> &getInnerContainers();
    ~RelocationInfoContainer();
private:
    unsigned int sectionIndex;
    unsigned int relocationIndex;
};
}

static struct
{
    const ELFIO::Elf_Word value;
    const char *string;
} r_type_strings[] =
{
    TO_STRING(R_386_NONE),
    TO_STRING(R_386_32),
    TO_STRING(R_386_PC32),
    TO_STRING(R_386_GOT32),
    TO_STRING(R_386_PLT32),
    TO_STRING(R_386_COPY),
    TO_STRING(R_386_GLOB_DAT),
    TO_STRING(R_386_JMP_SLOT),
    TO_STRING(R_386_RELATIVE),
    TO_STRING(R_386_GOTOFF),
    TO_STRING(R_386_GOTPC),
    { 0, nullptr },
};

#endif // RELOCATION_INFO_CONTAINER_HPP_
