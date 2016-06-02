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

#include "e_ident_container.hpp"
#include <iostream>

using namespace elf;

EIdentContainer::EIdentContainer(ELFFile *file) :
    Container(file, true, std::make_pair(0, EI_NIDENT))
{
    setName("e_ident");
}

std::vector<Container *> &EIdentContainer::getInnerContainers()
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
    }

    return innerContainers;
}

EIdentContainer::~EIdentContainer() {}
