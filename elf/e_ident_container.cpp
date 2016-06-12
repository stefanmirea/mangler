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
#include <sstream>

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
        int elfmag0 = elfio->get_elfmag0();
        std::string elfmag0_string = "";

        if (elfmag0 == ELFMAG0)
            elfmag0_string = "ELFMAG0";
        else
        {
            std::stringstream ss;
            ss << std::hex << std::showbase << elfmag0;
            elfmag0_string = ss.str();
        }

        container->setName("e_ident[EI_MAG0]: " + elfmag0_string);
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        int elfmag1 = elfio->get_elfmag1();
        std::string elfmag1_string = "";

        if (elfmag1 == ELFMAG1)
            elfmag1_string = "ELFMAG1";
        else
        {
            std::stringstream ss;
            ss << std::hex << std::showbase << elfmag1;
            elfmag1_string = ss.str();
        }

        container->setName("e_ident[EI_MAG1]: " + elfmag1_string);
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        int elfmag2 = elfio->get_elfmag2();
        std::string elfmag2_string = "";

        if (elfmag2 == ELFMAG2)
            elfmag2_string = "ELFMAG2";
        else
        {
            std::stringstream ss;
            ss << std::hex << std::showbase << elfmag2;
            elfmag2_string = ss.str();
        }
        container->setName("e_ident[EI_MAG2]: " + elfmag2_string);
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        int elfmag3 = elfio->get_elfmag3();
        std::string elfmag3_string = "";

        if (elfmag3 == ELFMAG3)
            elfmag3_string = "ELFMAG3";
        else
        {
            std::stringstream ss;
            ss << std::hex << std::showbase << elfmag3;
            elfmag3_string = ss.str();
        }
        container->setName("e_ident[EI_MAG3]: " + elfmag3_string);
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        int ei_class = elfio->get_class();
        std::string ei_class_string = "";

        switch(ei_class)
        {
            case ELFCLASSNONE:
                ei_class_string = "ELFCLASSNONE";
                break;
            case ELFCLASS32:
                ei_class_string = "ELFCLASS32";
                break;
            case ELFCLASS64	:
                ei_class_string = "ELFCLASS64";
                break;
            default:
                ei_class_string = std::to_string(ei_class);
                break;
        }

        container->setName("e_ident[EI_CLASS]: " + ei_class_string);
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        int ei_data = elfio->get_encoding();
        std::string ei_data_string = "";

        switch(ei_data)
        {
            case ELFDATANONE:
                ei_data_string = "ELFDATANONE";
                break;
            case ELFDATA2LSB:
                ei_data_string = "ELFDATA2LSB";
                break;
            case ELFDATA2MSB:
                ei_data_string = "ELFDATA2MSB";
                break;
            default:
                ei_data_string = std::to_string(ei_data);
                break;
        }
        container->setName("e_ident[EI_DATA]: " + ei_data_string);
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        int ei_version = elfio->get_elf_version();
        std::string ei_version_string = "";

        switch(ei_version)
        {
            case EV_NONE:
                ei_version_string = "EV_NONE";
                break;
            case EV_CURRENT:
                ei_version_string = "EV_CURRENT";
                break;
            default:
                ei_version_string = std::to_string(ei_version);
                break;
        }

        container->setName("e_ident[EI_VERSION]: " + ei_version_string);
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        int ei_osabi = elfio->get_os_abi();
        std::string ei_osabi_string = "";

        switch(ei_osabi)
        {
            case ELFOSABI_NONE:
                ei_osabi_string = "ELFOSABI_NONE";
                break;
            case ELFOSABI_HPUX:
                ei_osabi_string = "ELFOSABI_HPUX";
                break;
            case ELFOSABI_NETBSD:
                ei_osabi_string = "ELFOSABI_NETBSD";
                break;
            case ELFOSABI_LINUX:
                ei_osabi_string = "ELFOSABI_LINUX";
                break;
            case ELFOSABI_SOLARIS:
                ei_osabi_string = "ELFOSABI_SOLARIS";
                break;
            case ELFOSABI_AIX:
                ei_osabi_string = "ELFOSABI_AIX";
                break;
            case ELFOSABI_IRIX:
                ei_osabi_string = "ELFOSABI_IRIX";
                break;
            case ELFOSABI_FREEBSD:
                ei_osabi_string = "ELFOSABI_FREEBSD";
                break;
            case ELFOSABI_TRU64:
                ei_osabi_string = "ELFOSABI_TRU64";
                break;
            case ELFOSABI_MODESTO:
                ei_osabi_string = "ELFOSABI_MODESTO";
                break;
            case ELFOSABI_OPENBSD:
                ei_osabi_string = "ELFOSABI_OPENBSD";
                break;
            case ELFOSABI_OPENVMS:
                ei_osabi_string = "ELFOSABI_OPENVMS";
                break;
            case ELFOSABI_NSK:
                ei_osabi_string = "ELFOSABI_NSK";
                break;
            case ELFOSABI_AROS:
                ei_osabi_string = "ELFOSABI_AROS";
                break;
            case ELFOSABI_FENIXOS:
                ei_osabi_string = "ELFOSABI_FENIXOS";
                break;
            default:
                ei_osabi_string = std::to_string(ei_class);
                break;
        }

        container->setName("e_ident[EI_OSABI]: " + ei_osabi_string);
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 1));
        container->setName("e_ident[EI_ABIVERSION]: " + std::to_string(elfio->get_abi_version()));
        addInnerContainer(container);
        offset++;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 7));
        container->setName("e_ident[EI_PAD]");
        addInnerContainer(container);
        offset += 7;
    }

    return innerContainers;
}

EIdentContainer::~EIdentContainer() {}
