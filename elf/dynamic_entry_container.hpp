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

#ifndef DYNAMIC_ENTRY_CONTAINER_HPP_
#define DYNAMIC_ENTRY_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"
#include "util.hpp"

namespace elf
{
class DynamicEntryContainer : public Container
{
public:
    DynamicEntryContainer(ELFFile *file, const std::pair<int, int> &interval,
                          unsigned int sectionIndex, unsigned int dynamicIndex);
    std::vector<Container *> &getInnerContainers();
    ~DynamicEntryContainer();
private:
    unsigned int sectionIndex;
    unsigned int dynamicIndex;
    ELFIO::Elf_Xword tag, value;
};
}

static struct
{
    const ELFIO::Elf_Xword value;
    const char *string;
} d_tag_strings[] =
{
    TO_STRING(DT_NULL),
    TO_STRING(DT_NEEDED),
    TO_STRING(DT_PLTRELSZ),
    TO_STRING(DT_PLTGOT),
    TO_STRING(DT_HASH),
    TO_STRING(DT_STRTAB),
    TO_STRING(DT_SYMTAB),
    TO_STRING(DT_RELA),
    TO_STRING(DT_RELASZ),
    TO_STRING(DT_RELAENT),
    TO_STRING(DT_STRSZ),
    TO_STRING(DT_SYMENT),
    TO_STRING(DT_INIT),
    TO_STRING(DT_FINI),
    TO_STRING(DT_SONAME),
    TO_STRING(DT_RPATH),
    TO_STRING(DT_SYMBOLIC),
    TO_STRING(DT_REL),
    TO_STRING(DT_RELSZ),
    TO_STRING(DT_RELENT),
    TO_STRING(DT_PLTREL),
    TO_STRING(DT_DEBUG),
    TO_STRING(DT_TEXTREL),
    TO_STRING(DT_JMPREL),
    TO_STRING(DT_BIND_NOW),
    TO_STRING(DT_INIT_ARRAY),
    TO_STRING(DT_FINI_ARRAY),
    TO_STRING(DT_INIT_ARRAYSZ),
    TO_STRING(DT_FINI_ARRAYSZ),
    TO_STRING(DT_RUNPATH),
    TO_STRING(DT_FLAGS),
    TO_STRING(DT_ENCODING),
    TO_STRING(DT_PREINIT_ARRAY),
    TO_STRING(DT_PREINIT_ARRAYSZ),
    { DT_MAXPOSTAGS, "DT_SYMTAB_SHNDX" },
    { 0, nullptr },
};

#endif // DYNAMIC_ENTRY_CONTAINER_HPP_
