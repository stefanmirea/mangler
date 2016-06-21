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

#include "dynamic_entry_container.hpp"
#include <iomanip>
#include <sstream>

using namespace elf;

DynamicEntryContainer::DynamicEntryContainer(ELFFile *file, const std::pair<int, int> &interval,
    unsigned int sectionIndex, unsigned int dynamicIndex) : Container(file, true, interval),
    sectionIndex(sectionIndex), dynamicIndex(dynamicIndex)
{
    ELFIO::elfio *elfData = file->getELFIO();
    ELFIO::section *entry = elfData->sections[sectionIndex];
    ELFIO::dynamic_section_accessor dynamic(*elfData, entry);

    ELFIO::Elf_Xword entries_num = dynamic.get_entries_num();

    int digits = 0;
    do {
        ++digits;
        entries_num /= 10;
    } while (entries_num);

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(digits) << dynamicIndex << ": ";

    std::string str;
    dynamic.get_entry(dynamicIndex, tag, value, str);

    bool found = false;
    for (unsigned int i = 0; d_tag_strings[i].string; ++i)
        if (d_tag_strings[i].value == tag)
        {
            ss << d_tag_strings[i].string;
            found = true;
            break;
        }
    if (!found)
        ss << "unknown tag";

    if (str != "")
        ss << ", \"" << str << '\"';

    setName(ss.str());
}

std::vector<Container *> &DynamicEntryContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
        assert(efile != nullptr);
#endif
        ELFIO::elfio *interpretor = efile->getELFIO();

        ELFIO::section *section = interpretor->sections[sectionIndex];
        int offset = section->get_offset() + dynamicIndex * section->get_entry_size();

        Container *container = new Container(efile, false, std::make_pair(offset, offset +
            sizeof(ELFIO::Elf32_Sword)));
        bool found = false;
        for (unsigned int i = 0; d_tag_strings[i].string; ++i)
            if (d_tag_strings[i].value == tag)
            {
                container->setName(std::string("d_tag: ") + d_tag_strings[i].string);
                found = true;
                break;
            }
        if (!found)
            container->setName("d_tag: " + printHex(tag));
        addInnerContainer(container);
        offset += sizeof(ELFIO::Elf32_Sword);

        container = new Container(efile, false,
            std::make_pair(offset, offset + sizeof(ELFIO::Elf32_Word)));
        switch (tag)
        {
            case DT_NULL:
            case DT_SYMBOLIC:
            case DT_TEXTREL:
            case DT_BIND_NOW:
                /* ignored */
                container->setName("d_un: " + std::to_string(value) + " (ignored)");
                break;
            case DT_NEEDED:
            case DT_PLTRELSZ:
            case DT_RELASZ:
            case DT_RELAENT:
            case DT_STRSZ:
            case DT_SYMENT:
            case DT_SONAME:
            case DT_RPATH:
            case DT_RELSZ:
            case DT_RELENT:
            case DT_PLTREL:
            case DT_INIT_ARRAYSZ:
            case DT_FINI_ARRAYSZ:
            case DT_RUNPATH:
            case DT_FLAGS:
                /* using d_val */
                container->setName("d_un.d_val: " + std::to_string(value));
                break;
            case DT_PLTGOT:
            case DT_HASH:
            case DT_STRTAB:
            case DT_SYMTAB:
            case DT_RELA:
            case DT_INIT:
            case DT_FINI:
            case DT_REL:
            case DT_DEBUG:
            case DT_JMPREL:
            case DT_INIT_ARRAY:
            case DT_FINI_ARRAY:
            case DT_PREINIT_ARRAY:
                /* using d_ptr */
                container->setName("d_un.d_ptr: " + printHex(value));
                break;
            default:
                if (tag == DT_ENCODING || (tag > DT_HIOS && tag < DT_LOPROC))
                    /* not specified which member to use */
                    container->setName("d_un: " + std::to_string(value));
                else if (tag % 2 == 0)
                    /* using d_ptr */
                    container->setName("d_un.d_ptr: " + printHex(value));
                else
                    /* using d_val */
                    container->setName("d_un.d_val: " + std::to_string(value));
        }
        addInnerContainer(container);
    }
    return innerContainers;
}

DynamicEntryContainer::~DynamicEntryContainer() {}
