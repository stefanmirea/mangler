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
