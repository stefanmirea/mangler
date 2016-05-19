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
#include "elf_entry.hpp"
#include <iostream>

using namespace elf;

ELFHeaderContainer::e_ident_ei_mag0_t::e_ident_ei_mag0_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_elfmag0();
    std::string val_display = "e_ident[EI_MAG0]:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_ident_ei_mag0_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_ident_ei_mag1_t::e_ident_ei_mag1_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_elfmag1();
    std::string val_display = "e_ident[EI_MAG1]:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_ident_ei_mag1_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_ident_ei_mag2_t::e_ident_ei_mag2_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_elfmag2();
    std::string val_display = "e_ident[EI_MAG2]:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_ident_ei_mag2_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_ident_ei_mag3_t::e_ident_ei_mag3_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_elfmag3();
    std::string val_display = "e_ident[EI_MAG3]:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_ident_ei_mag3_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::ei_class_t::ei_class_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_class();
    std::string val_display = "e_ident[EI_CLASS]:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::ei_class_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::ei_data_t::ei_data_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_encoding();
    std::string val_display = "e_ident[EI_DATA]:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::ei_data_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::ei_version_t::ei_version_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_elf_version();
    std::string val_display = "e_ident[EI_VERSION]:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::ei_version_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::ei_osabi_t::ei_osabi_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_os_abi();
    std::string val_display = "e_ident[EI_OSABI]:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::ei_osabi_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::ei_abiversion_t::ei_abiversion_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_abi_version();
    std::string val_display = "e_ident[EI_ABIVERSION]:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::ei_abiversion_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_ident_ei_pad_t::e_ident_ei_pad_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    std::string val_display = "e_ident[EI_PAD]:    *******";
    setName(val_display);
}

void ELFHeaderContainer::e_ident_ei_pad_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_type_t::e_type_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_type();
    std::string val_display = "e_type:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_type_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_machine_t::e_machine_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_machine();
    std::string val_display = "e_machine:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_machine_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_version_t::e_version_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_version();
    std::string val_display = "e_version:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_version_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_entry_t::e_entry_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_entry();
    std::string val_display = "e_entry:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_entry_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_phoff_t::e_phoff_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_segments_offset();
    std::string val_display = "e_phoff:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_phoff_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_shoff_t::e_shoff_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_sections_offset();
    std::string val_display = "e_shoff:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_shoff_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_flags_t::e_flags_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_flags();
    std::string val_display = "e_flags:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_flags_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_ehsize_t::e_ehsize_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_header_size();
    std::string val_display = "e_ehsize:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_ehsize_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_phentsize_t::e_phentsize_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_segment_entry_size();
    std::string val_display = "e_phentsize:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_phentsize_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_phnum_t::e_phnum_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_segments_num();
    std::string val_display = "e_phnum:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_phnum_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_shentsize_t::e_shentsize_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_section_entry_size();
    std::string val_display = "e_shentsize:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_shentsize_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_shnum_t::e_shnum_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_sections_num();
    std::string val_display = "e_shnum:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_shnum_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

ELFHeaderContainer::e_shstrndx_t::e_shstrndx_t(ELFFile *file,
                                                         const std::pair<int, int> &interval) :
   ELFEntry::ELFEntry(file, interval)
{
    unsigned char byte = file->getELFIO()->get_section_name_str_index();
    std::string val_display = "e_shstrndx:    " + std::to_string((int)byte);
    setName(val_display);
}

void ELFHeaderContainer::e_shstrndx_t::update(char *data)
{
    std::string val_display(data);
    setName(val_display);
}

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

    ELFHeaderContainer::e_ident_ei_mag0_t *e_ident_ei_mag0 =
            new ELFHeaderContainer::e_ident_ei_mag0_t(file, std::make_pair(offset, offset + 1));
    addInnerContainer(e_ident_ei_mag0);

    offset++;

    ELFHeaderContainer::e_ident_ei_mag1_t *e_ident_ei_mag1 =
            new ELFHeaderContainer::e_ident_ei_mag1_t(file, std::make_pair(offset, offset + 1));
    addInnerContainer(e_ident_ei_mag1);

    offset++;

    ELFHeaderContainer::e_ident_ei_mag2_t *e_ident_ei_mag2 =
            new ELFHeaderContainer::e_ident_ei_mag2_t(file, std::make_pair(offset, offset + 1));
    addInnerContainer(e_ident_ei_mag2);
    offset++;

    ELFHeaderContainer::e_ident_ei_mag3_t *e_ident_ei_mag3 =
            new ELFHeaderContainer::e_ident_ei_mag3_t(file, std::make_pair(offset, offset + 1));
    addInnerContainer(e_ident_ei_mag3);
    offset++;

    ELFHeaderContainer::ei_class_t *ei_class =
            new ELFHeaderContainer::ei_class_t(file, std::make_pair(offset, offset + 1));
    addInnerContainer(ei_class);
    offset++;

    increment = 4;

    ELFHeaderContainer::ei_data_t *ei_data =
            new ELFHeaderContainer::ei_data_t(file, std::make_pair(offset, offset + 1));
    addInnerContainer(ei_data);
    offset++;

    ELFHeaderContainer::ei_version_t *ei_version =
            new ELFHeaderContainer::ei_version_t(file, std::make_pair(offset, offset + 1));
    addInnerContainer(ei_version);
    offset++;

    ELFHeaderContainer::ei_osabi_t *ei_osabi =
            new ELFHeaderContainer::ei_osabi_t(file, std::make_pair(offset, offset + 1));
    addInnerContainer(ei_osabi);
    offset++;

    ELFHeaderContainer::ei_abiversion_t *ei_abiversion =
            new ELFHeaderContainer::ei_abiversion_t(file, std::make_pair(offset, offset + 1));
    addInnerContainer(ei_abiversion);
    offset++;

    /* TODO: get value */
    ELFHeaderContainer::e_ident_ei_pad_t  *e_ident_ei_pad =
            new ELFHeaderContainer::e_ident_ei_pad_t(file, std::make_pair(offset, offset + 7));
    addInnerContainer(e_ident_ei_pad);
    offset += 7;

    ELFHeaderContainer::e_type_t  *e_type =
            new ELFHeaderContainer::e_type_t(file, std::make_pair(offset, offset + 2));
    addInnerContainer(e_type);
    offset += 2;

    ELFHeaderContainer::e_machine_t  *machine =
            new ELFHeaderContainer::e_machine_t(file, std::make_pair(offset, offset + 2));
    addInnerContainer(machine);
    offset += 2;

    ELFHeaderContainer::e_version_t  *e_version =
            new ELFHeaderContainer::e_version_t(file, std::make_pair(offset, offset + 4));
    addInnerContainer(e_version);
    offset += 4;

    ELFHeaderContainer::e_entry_t  *e_entry =
            new ELFHeaderContainer::e_entry_t(file, std::make_pair(offset, offset + increment));
    addInnerContainer(e_entry);
    offset += increment;

    ELFHeaderContainer::e_phoff_t  *e_phoff =
            new ELFHeaderContainer::e_phoff_t(file, std::make_pair(offset, offset + increment));
    addInnerContainer(e_phoff);
    offset += increment;

    ELFHeaderContainer::e_shoff_t  *e_shoff =
            new ELFHeaderContainer::e_shoff_t(file, std::make_pair(offset, offset + increment));
    addInnerContainer(e_shoff);
    offset += increment;

    ELFHeaderContainer::e_flags_t  *e_flags =
            new ELFHeaderContainer::e_flags_t(file, std::make_pair(offset, offset + 4));
    addInnerContainer(e_flags);
    offset += 4;


    ELFHeaderContainer::e_ehsize_t  *e_ehsize =
            new ELFHeaderContainer::e_ehsize_t(file, std::make_pair(offset, offset + 2));
    addInnerContainer(e_ehsize);
    offset += 2;

    ELFHeaderContainer::e_phentsize_t  *e_phentsize =
            new ELFHeaderContainer::e_phentsize_t(file, std::make_pair(offset, offset + 2));
    addInnerContainer(e_phentsize);
    offset += 2;

    ELFHeaderContainer::e_phnum_t  *e_phnum =
            new ELFHeaderContainer::e_phnum_t(file, std::make_pair(offset, offset + 2));
    addInnerContainer(e_phnum);
    offset += 2;

    ELFHeaderContainer::e_shentsize_t  *e_shentsize =
            new ELFHeaderContainer::e_shentsize_t(file, std::make_pair(offset, offset + 2));
    addInnerContainer(e_shentsize);
    offset += 2;

    ELFHeaderContainer::e_shnum_t  *e_shnum =
            new ELFHeaderContainer::e_shnum_t(file, std::make_pair(offset, offset + 2));
    addInnerContainer(e_shnum);
    offset += 2;

    ELFHeaderContainer::e_shstrndx_t  *e_shstrndx =
            new ELFHeaderContainer::e_shstrndx_t(file, std::make_pair(offset, offset + 2));
    addInnerContainer(e_shstrndx);
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
