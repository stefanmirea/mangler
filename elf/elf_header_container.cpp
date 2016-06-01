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

#include "elf_header_container.hpp"
#include <iostream>

using namespace elf;

ELFHeaderContainer::ELFHeaderContainer(ELFFile *file, const std::pair<int, int> &interval) :
    Container(file, true, interval)
{
    setName("ELF Header");
}

std::vector<Container *> &ELFHeaderContainer::getInnerContainers()
{
    if (innerContainers.empty())
    {
        Container *container;
        ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
        ELFIO::elfio *elfio = efile->getELFIO();
        int offset = 0x00;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        container->setName("e_ident[EI_MAG0]: " + std::to_string(elfio->get_elfmag0()));
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        container->setName("e_ident[EI_MAG1]: " + std::to_string(elfio->get_elfmag1()));
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        container->setName("e_ident[EI_MAG2]: " + std::to_string(elfio->get_elfmag2()));
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        container->setName("e_ident[EI_MAG3]: " + std::to_string(elfio->get_elfmag3()));
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        container->setName("e_ident[EI_CLASS]: " + std::to_string(elfio->get_class()));
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        container->setName("e_ident[EI_DATA]: " + std::to_string(elfio->get_encoding()));
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        container->setName("e_ident[EI_VERSION]: " + std::to_string(elfio->get_elf_version()));
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        container->setName("e_ident[EI_OSABI]: " + std::to_string(elfio->get_os_abi()));
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        container->setName("e_ident[EI_ABIVERSION]: " + std::to_string(elfio->get_abi_version()));
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 7));
        container->setName("e_ident[EI_PAD]: " + std::string("00 00 00 00 00 00 00"));
        addInnerContainer(container);
        offset += 7;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 2));
        container->setName("e_type: " + std::to_string(elfio->get_type()));
        addInnerContainer(container);
        offset += 2;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 2));
        container->setName("e_machine: " + std::to_string(elfio->get_machine()));
        addInnerContainer(container);
        offset += 2;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 4));
        container->setName("e_version: " + std::to_string(elfio->get_version()));
        addInnerContainer(container);
        offset += 4;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 4));
        container->setName("e_entry: " + std::to_string(elfio->get_entry()));
        addInnerContainer(container);
        offset += 4;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 4));
        container->setName("e_phoff: " + std::to_string(elfio->get_segments_offset()));
        addInnerContainer(container);
        offset += 4;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 4));
        container->setName("e_shoff: " + std::to_string(elfio->get_sections_offset()));
        addInnerContainer(container);
        offset += 4;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 4));
        container->setName("e_flags: " + std::to_string(elfio->get_flags()));
        addInnerContainer(container);
        offset += 4;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 2));
        container->setName("e_ehsize: " + std::to_string(elfio->get_header_size()));
        addInnerContainer(container);
        offset += 2;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 2));
        container->setName("e_phentsize: " + std::to_string(elfio->get_segment_entry_size()));
        addInnerContainer(container);
        offset += 2;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 2));
        container->setName("e_phnum: " + std::to_string(elfio->get_segments_num()));
        addInnerContainer(container);
        offset += 2;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 2));
        container->setName("e_shentsize: " + std::to_string(elfio->get_section_entry_size()));
        addInnerContainer(container);
        offset += 2;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 2));
        container->setName("e_shnum: " + std::to_string(elfio->get_sections_num()));
        addInnerContainer(container);
        offset += 2;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 2));
        container->setName("e_shstrndx: " + std::to_string(elfio->get_section_name_str_index()));
        addInnerContainer(container);
        offset += 2;
    }

    return innerContainers;
}

ELFHeaderContainer::~ELFHeaderContainer() {}
