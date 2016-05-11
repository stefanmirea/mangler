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

    int offset = 0x00;
    int increment = 0;

    std::string val_display;
    unsigned char byte;

    byte = file->getELFIO()->get_elfmag0();
    val_display = std::to_string((int)byte);
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 1)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 1)),
                   "e_ident[EI_MAG0]", val_display);
    offset++;

    byte = file->getELFIO()->get_elfmag1();
    val_display = std::to_string((int)byte);
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 1)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 1)),
                   "e_ident[EI_MAG1]", val_display);
    offset++;

    byte = file->getELFIO()->get_elfmag2();
    val_display = std::to_string((int)byte);
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 1)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 1)),
                   "e_ident[EI_MAG2]", val_display);
    offset++;

    byte = file->getELFIO()->get_elfmag3();
    val_display = std::to_string((int)byte);
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 1)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 1)),
                   "e_ident[EI_MAG3]", val_display);
    offset++;


    byte = file->getELFIO()->get_class();
    val_display = std::to_string((int)byte);
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 1)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 1)),
                   "e_ident[EI_CLASS]", val_display);
    offset++;

    if(byte == 1)
    {
        increment = 4;
    }

    else
    {
        increment = 8;
    }

    byte = file->getELFIO()->get_encoding();
    val_display = std::to_string((int)byte);
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 1)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 1)),
                   "e_ident[EI_DATA]", val_display);
    offset++;

    byte = file->getELFIO()->get_elf_version();
    val_display = std::to_string((int)byte);
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 1)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 1)),
                    "e_ident[EI_VERSION]", val_display);
    offset++;

    byte = file->getELFIO()->get_os_abi();
    val_display = std::to_string((int)byte);
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 1)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 1)),
                    "e_ident[EI_OSABI]", val_display);
    offset++;

    byte = file->getELFIO()->get_abi_version();
    val_display = std::to_string((int)byte);
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 1)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 1)),
                    "e_ident[EI_ABIVERSION]", val_display);
    offset++;

    /* TODO: get value */
    val_display = std::to_string(file->getELFIO()->get_type());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 7)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 7)),
                    "e_ident[EI_PAD]", "*******");
    offset += 7;

    val_display = std::to_string(file->getELFIO()->get_type());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 2)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 2)),
                    "e_type", val_display);
    offset += 2;

    val_display = std::to_string(file->getELFIO()->get_machine());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 2)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 2)),
                    "e_machine", val_display);

    offset += 2;

    val_display = std::to_string(file->getELFIO()->get_version());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 4)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 4)),
                    "e_machine", val_display);

    offset += 4;

    val_display = std::to_string(file->getELFIO()->get_entry());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + increment)),
                   new Container(getFile(), false, std::make_pair(offset, offset + increment)),
                    "e_entry", val_display);

    offset += increment;

    val_display = std::to_string(file->getELFIO()->get_segments_offset());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + increment)),
                   new Container(getFile(), false, std::make_pair(offset, offset + increment)),
                    "e_phoff", val_display);

    offset += increment;

    val_display = std::to_string(file->getELFIO()->get_sections_offset());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + increment)),
                   new Container(getFile(), false, std::make_pair(offset, offset + increment)),
                    "e_shoff", val_display);

    offset += increment;

    val_display = std::to_string(file->getELFIO()->get_sections_offset());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 4)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 4)),
                    "e_flags", val_display);

    offset += 4;

    val_display = std::to_string(file->getELFIO()->get_header_size());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 2)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 2)),
                    "e_ehsize", val_display);

    offset += 2;

    val_display = std::to_string(file->getELFIO()->get_segment_entry_size());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 2)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 2)),
                    "e_phentsize", val_display);

    offset += 2;

    val_display = std::to_string(file->getELFIO()->get_segments_num());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 2)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 2)),
                    "e_phnum", val_display);

    offset += 2;

    val_display = std::to_string(file->getELFIO()->get_section_entry_size());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 2)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 2)),
                    "e_shentsize", val_display);

    offset += 2;

    val_display = std::to_string((file->getELFIO()->get_sections_num()));
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 2)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 2)),
                    "e_shnum", val_display);

    offset += 2;

    val_display = std::to_string(file->getELFIO()->get_section_name_str_index());
    addHeaderEntry(new Container(getFile(), true, std::make_pair(offset, offset + 2)),
                   new Container(getFile(), false, std::make_pair(offset, offset + 2)),
                    "e_shstrndx", val_display);

    offset += 2;
}

void ELFHeaderContainer::addHeaderEntry(Container *entry, Container *val, const std::string &entryName, const std::string &valName)
{
    entry->setName(entryName);
    val->setName(valName);
    entry->addInnerContainer(val);
    addInnerContainer(entry);
}

std::vector<Container *> &ELFHeaderContainer::getInnerContainers()
{
    return innerContainers;
}

ELFHeaderContainer::~ELFHeaderContainer() {}
