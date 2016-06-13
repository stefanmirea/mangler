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
#include "e_ident_container.hpp"
#include "util.hpp"
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
#ifdef DEBUG
        assert(efile != nullptr);
#endif
        ELFIO::elfio *elfio = efile->getELFIO();

        addInnerContainer(new EIdentContainer(efile));
        int offset = EI_NIDENT;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 2));
        int e_type = elfio->get_type();
        std::string e_type_string = "";

        switch(e_type)
        {
            case ET_NONE:
                e_type_string = "ET_NONE";
                break;
            case ET_REL:
                e_type_string = "ET_REL";
                break;
            case ET_EXEC:
                e_type_string = "ET_EXEC";
                break;
            case ET_DYN:
                e_type_string = "ET_DYN";
                break;
            case ET_CORE:
                e_type_string = "ET_CORE";
                break;
            case ET_LOOS:
                e_type_string = "ET_LOOS";
                break;
            case ET_HIOS:
                e_type_string = "ET_HIOS";
                break;
            case ET_LOPROC:
                e_type_string = "ET_LOPROC";
                break;
            case ET_HIPROC:
                e_type_string = "ET_HIPROC";
                break;
            default:
                e_type_string = printHex(e_type);
                break;
        }

        container->setName("e_type: " + e_type_string);
        addInnerContainer(container);
        offset += 2;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 2));
        int e_machine = elfio->get_machine();
        std::string e_machine_string = "";

        switch(e_machine)
        {
            case EM_NONE:
                e_machine_string = "EM_NONE";
                break;
            case EM_M32:
                e_machine_string = "EM_M32";
                break;
            case EM_SPARC:
                e_machine_string = "EM_SPARC";
                break;
            case EM_386:
                e_machine_string = "EM_386";
                break;
            case EM_68K:
                e_machine_string = "EM_68K";
                break;
            case EM_88K:
                e_machine_string = "EM_88K";
                break;
            case EM_IAMCU:
                e_machine_string = "EM_IAMCU";
                break;
            case EM_860:
                e_machine_string = "EM_860";
                break;
            case EM_MIPS:
                e_machine_string = "EM_MIPS";
                break;
            case EM_S370:
                e_machine_string = "EM_S370";
                break;
            case EM_MIPS_RS3_LE:
                e_machine_string = "EM_MIPS_RS3_LE";
                break;
            case EM_PARISC:
                e_machine_string = "EM_PARISC";
                break;
            case EM_VPP500:
                e_machine_string = "EM_VPP500";
                break;
            case EM_SPARC32PLUS:
                e_machine_string = "EM_SPARC32PLUS";
                break;
            case EM_960:
                e_machine_string = "EM_960";
                break;
            case EM_PPC:
                e_machine_string = "EM_PPC";
                break;
            case EM_PPC64:
                e_machine_string = "EM_PPC64";
                break;
            case EM_S390:
                e_machine_string = "EM_S390";
                break;
            case EM_SPU:
                e_machine_string = "EM_SPU";
                break;
            case EM_V800:
                e_machine_string = "EM_V800";
                break;
            case EM_FR20:
                e_machine_string = "EM_FR20";
                break;
            case EM_RH32:
                e_machine_string = "EM_RH32";
                break;
            case EM_RCE:
                e_machine_string = "EM_RCE";
                break;
            case EM_ARM:
                e_machine_string = "EM_ARM";
                break;
            case EM_ALPHA:
                e_machine_string = "EM_ALPHA";
                break;
            case EM_SH:
                e_machine_string = "EM_SH";
                break;
            case EM_SPARCV9:
                e_machine_string = "EM_SPARCV9";
                break;
            case EM_TRICORE:
                e_machine_string = "EM_TRICORE";
                break;
            case EM_ARC:
                e_machine_string = "EM_ARC";
                break;
            case EM_H8_300:
                e_machine_string = "EM_H8_300";
                break;
            case EM_H8_300H:
                e_machine_string = "EM_H8_300H";
                break;
            case EM_H8S:
                e_machine_string = "EM_H8S";
                break;
            case EM_H8_500:
                e_machine_string = "EM_H8_500";
                break;
            case EM_IA_64:
                e_machine_string = "EM_IA_64";
                break;
            case EM_MIPS_X:
                e_machine_string = "EM_MIPS_X";
                break;
            case EM_COLDFIRE:
                e_machine_string = "EM_COLDFIRE";
                break;
            case EM_68HC12:
                e_machine_string = "EM_68HC12";
                break;
            case EM_MMA:
                e_machine_string = "EM_MMA";
                break;
            case EM_PCP:
                e_machine_string = "EM_PCP";
                break;
            case EM_NCPU:
                e_machine_string = "EM_NCPU";
                break;
            case EM_NDR1:
                e_machine_string = "EM_NDR1";
                break;
            case EM_STARCORE:
                e_machine_string = "EM_STARCORE";
                break;
            case EM_ME16:
                e_machine_string = "EM_ME16";
                break;
            case EM_ST100:
                e_machine_string = "EM_ST100";
                break;
            case EM_TINYJ:
                e_machine_string = "EM_TINYJ";
                break;
            case EM_X86_64:
                e_machine_string = "EM_X86_64";
                break;
            case EM_PDSP:
                e_machine_string = "EM_PDSP";
                break;
            case EM_PDP10:
                e_machine_string = "EM_PDP10";
                break;
            case EM_PDP11:
                e_machine_string = "EM_PDP11";
                break;
            case EM_ST9PLUS:
                e_machine_string = "EM_ST9PLUS";
                break;
            case EM_ST7:
                e_machine_string = "EM_ST7";
                break;
            case EM_68HC16:
                e_machine_string = "EM_68HC16";
                break;
            case EM_68HC11:
                e_machine_string = "EM_68HC11";
                break;
            case EM_68HC08:
                e_machine_string = "EM_68HC08";
                break;
            case EM_68HC05:
                e_machine_string = "EM_68HC05";
                break;
            case EM_SVX:
                e_machine_string = "EM_SVX";
                break;
            case EM_ST19:
                e_machine_string = "EM_ST19";
                break;
            case EM_VAX:
                e_machine_string = "EM_VAX";
                break;
            case EM_CRIS:
                e_machine_string = "EM_CRIS";
                break;
            case EM_JAVELIN:
                e_machine_string = "EM_JAVELIN";
                break;
            case EM_FIREPATH:
                e_machine_string = "EM_FIREPATH";
                break;
            case EM_ZSP:
                e_machine_string = "EM_ZSP";
                break;
            case EM_MMIX:
                e_machine_string = "EM_MMIX";
                break;
            case EM_HUANY:
                e_machine_string = "EM_HUANY";
                break;
            case EM_PRISM:
                e_machine_string = "EM_PRISM";
                break;
            case EM_AVR:
                e_machine_string = "EM_AVR";
                break;
            case EM_FR30:
                e_machine_string = "EM_FR30";
                break;
            case EM_D10V:
                e_machine_string = "EM_D10V";
                break;
            case EM_D30V:
                e_machine_string = "EM_D30V";
                break;
            case EM_V850:
                e_machine_string = "EM_V850";
                break;
            case EM_M32R:
                e_machine_string = "EM_M32R";
                break;
            case EM_MN10300:
                e_machine_string = "EM_MN10300";
                break;
            case EM_MN10200:
                e_machine_string = "EM_MN10200";
                break;
            case EM_PJ:
                e_machine_string = "EM_PJ";
                break;
            case EM_OPENRISC:
                e_machine_string = "EM_OPENRISC";
                break;
            case EM_ARC_COMPACT:
                e_machine_string = "EM_ARC_COMPACT";
                break;
            case EM_XTENSA:
                e_machine_string = "EM_XTENSA";
                break;
            case EM_VIDEOCORE:
                e_machine_string = "EM_VIDEOCORE";
                break;
            case EM_TMM_GPP:
                e_machine_string = "EM_TMM_GPP";
                break;
            case EM_NS32K:
                e_machine_string = "EM_NS32K";
                break;
            case EM_TPC:
                e_machine_string = "EM_TPC";
                break;
            case EM_SNP1K:
                e_machine_string = "EM_SNP1K";
                break;
            case EM_ST200:
                e_machine_string = "EM_ST200";
                break;
            case EM_IP2K:
                e_machine_string = "EM_IP2K";
                break;
            case EM_MAX:
                e_machine_string = "EM_MAX";
                break;
            case EM_CR:
                e_machine_string = "EM_CR";
                break;
            case EM_F2MC16:
                e_machine_string = "EM_F2MC16";
                break;
            case EM_MSP430:
                e_machine_string = "EM_MSP430";
                break;
            case EM_BLACKFIN:
                e_machine_string = "EM_BLACKFIN";
                break;
            case EM_SE_C33:
                e_machine_string = "EM_SE_C33";
                break;
            case EM_SEP:
                e_machine_string = "EM_SEP";
                break;
            case EM_ARCA:
                e_machine_string = "EM_ARCA";
                break;
            case EM_UNICORE:
                e_machine_string = "EM_UNICORE";
                break;
            case EM_EXCESS:
                e_machine_string = "EM_EXCESS";
                break;
            case EM_DXP:
                e_machine_string = "EM_DXP";
                break;
            case EM_ALTERA_NIOS2:
                e_machine_string = "EM_ALTERA_NIOS2";
                break;
            case EM_CRX:
                e_machine_string = "EM_CRX";
                break;
            case EM_XGATE:
                e_machine_string = "EM_XGATE";
                break;
            case EM_C166:
                e_machine_string = "EM_C166";
                break;
            case EM_M16C:
                e_machine_string = "EM_M16C";
                break;
            case EM_DSPIC30F:
                e_machine_string = "EM_DSPIC30F";
                break;
            case EM_CE:
                e_machine_string = "EM_CE";
                break;
            case EM_M32C:
                e_machine_string = "EM_M32C";
                break;
            case EM_TSK3000:
                e_machine_string = "EM_TSK3000";
                break;
            case EM_RS08:
                e_machine_string = "EM_RS08";
                break;
            case EM_SHARC:
                e_machine_string = "EM_SHARC";
                break;
            case EM_ECOG2:
                e_machine_string = "EM_ECOG2";
                break;
            case EM_SCORE7:
                e_machine_string = "EM_SCORE7";
                break;
            case EM_DSP24:
                e_machine_string = "EM_DSP24";
                break;
            case EM_VIDEOCORE3:
                e_machine_string = "EM_VIDEOCORE3";
                break;
            case EM_LATTICEMICO32:
                e_machine_string = "EM_LATTICEMICO32";
                break;
            case EM_SE_C17:
                e_machine_string = "EM_SE_C17";
                break;
            case EM_TI_C6000:
                e_machine_string = "EM_TI_C6000";
                break;
            case EM_TI_C2000:
                e_machine_string = "EM_TI_C2000";
                break;
            case EM_TI_C5500:
                e_machine_string = "EM_TI_C5500";
                break;
            case EM_TI_ARP32:
                e_machine_string = "EM_TI_ARP32";
                break;
            case EM_TI_PRU:
                e_machine_string = "EM_TI_PRU";
                break;
            case EM_MMDSP_PLUS:
                e_machine_string = "EM_MMDSP_PLUS";
                break;
            case EM_CYPRESS_M8C:
                e_machine_string = "EM_CYPRESS_M8C";
                break;
            case EM_R32C:
                e_machine_string = "EM_R32C";
                break;
            case EM_TRIMEDIA:
                e_machine_string = "EM_TRIMEDIA";
                break;
            case EM_QDSP6:
                e_machine_string = "EM_QDSP6";
                break;
            case EM_8051:
                e_machine_string = "EM_8051";
                break;
            case EM_STXP7X:
                e_machine_string = "EM_STXP7X";
                break;
            case EM_NDS32:
                e_machine_string = "EM_NDS32";
                break;
            case EM_ECOG1X:
                e_machine_string = "EM_ECOG1X";
                break;
            case EM_MAXQ30:
                e_machine_string = "EM_MAXQ30";
                break;
            case EM_XIMO16:
                e_machine_string = "EM_XIMO16";
                break;
            case EM_MANIK:
                e_machine_string = "EM_MANIK";
                break;
            case EM_CRAYNV2:
                e_machine_string = "EM_CRAYNV2";
                break;
            case EM_RX:
                e_machine_string = "EM_RX";
                break;
            case EM_METAG:
                e_machine_string = "EM_METAG";
                break;
            case EM_MCST_ELBRUS:
                e_machine_string = "EM_MCST_ELBRUS";
                break;
            case EM_ECOG16:
                e_machine_string = "EM_ECOG16";
                break;
            case EM_CR16:
                e_machine_string = "EM_CR16";
                break;
            case EM_ETPU:
                e_machine_string = "EM_ETPU";
                break;
            case EM_SLE9X:
                e_machine_string = "EM_SLE9X";
                break;
            case EM_L10M:
                e_machine_string = "EM_L10M";
                break;
            case EM_K10M:
                e_machine_string = "EM_K10M";
                break;
            case EM_AARCH64:
                e_machine_string = "EM_AARCH64";
                break;
            case EM_STM8:
                e_machine_string = "EM_STM8";
                break;
            case EM_TILE64:
                e_machine_string = "EM_TILE64";
                break;
            case EM_TILEPRO:
                e_machine_string = "EM_TILEPRO";
                break;
            case EM_MICROBLAZE:
                e_machine_string = "EM_MICROBLAZE";
                break;
            case EM_CUDA:
                e_machine_string = "EM_CUDA";
                break;
            case EM_TILEGX:
                e_machine_string = "EM_TILEGX";
                break;
            case EM_CLOUDSHIELD:
                e_machine_string = "EM_CLOUDSHIELD";
                break;
            case EM_COREA_1ST:
                e_machine_string = "EM_COREA_1ST";
                break;
            case EM_COREA_2ND:
                e_machine_string = "EM_COREA_2ND";
                break;
            case EM_ARC_COMPACT2:
                e_machine_string = "EM_ARC_COMPACT2";
                break;
            case EM_OPEN8:
                e_machine_string = "EM_OPEN8";
                break;
            case EM_RL78:
                e_machine_string = "EM_RL78";
                break;
            case EM_VIDEOCORE5:
                e_machine_string = "EM_VIDEOCORE5";
                break;
            case EM_56800EX:
                e_machine_string = "EM_56800EX";
                break;
            case EM_BA1:
                e_machine_string = "EM_BA1";
                break;
            case EM_BA2:
                e_machine_string = "EM_BA2";
                break;
            case EM_XCORE:
                e_machine_string = "EM_XCORE";
                break;
            case EM_MCHP_PIC:
                e_machine_string = "EM_MCHP_PIC";
                break;
            case EM_INTEL205:
                e_machine_string = "EM_INTEL205";
                break;
            case EM_INTEL206:
                e_machine_string = "EM_INTEL206";
                break;
            case EM_INTEL207:
                e_machine_string = "EM_INTEL207";
                break;
            case EM_INTEL208:
                e_machine_string = "EM_INTEL208";
                break;
            case EM_INTEL209:
                e_machine_string = "EM_INTEL209";
                break;
            case EM_KM32:
                e_machine_string = "EM_KM32";
                break;
            case EM_KMX32:
                e_machine_string = "EM_KMX32";
                break;
            case EM_KMX16:
                e_machine_string = "EM_KMX16";
                break;
            case EM_KMX8:
                e_machine_string = "EM_KMX8";
                break;
            case EM_KVARC:
                e_machine_string = "EM_KVARC";
                break;
            case EM_CDP:
                e_machine_string = "EM_CDP";
                break;
            case EM_COGE:
                e_machine_string = "EM_COGE";
                break;
            case EM_COOL:
                e_machine_string = "EM_COOL";
                break;
            case EM_NORC:
                e_machine_string = "EM_NORC";
                break;
            case EM_CSR_KALIMBA:
                e_machine_string = "EM_CSR_KALIMBA";
                break;
            case EM_Z80:
                e_machine_string = "EM_Z80";
                break;
            case EM_VISIUM:
                e_machine_string = "EM_VISIUM";
                break;
            case EM_FT32:
                e_machine_string = "EM_FT32";
                break;
            case EM_MOXIE:
                e_machine_string = "EM_MOXIE";
                break;
            case EM_AMDGPU:
                e_machine_string = "EM_AMDGPU";
                break;
            case EM_RISCV:
                e_machine_string = "EM_RISCV";
                break;
            default:
                e_machine_string = printHex(e_machine);
                break;
        }

        container->setName("e_machine: " + e_machine_string);
        addInnerContainer(container);
        offset += 2;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 4));
        int e_version = elfio->get_version();
        std::string e_version_string = "";

        switch(e_version)
        {
            case EV_NONE:
                e_version_string = "EV_NONE";
                break;
            case EV_CURRENT:
                e_version_string = "EV_CURRENT";
                break;
            default:
                e_version_string = std::to_string(e_version);
                break;
        }

        container->setName("e_version: " + e_version_string);
        addInnerContainer(container);
        offset += 4;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 4));
        container->setName("e_entry: " + printHex(elfio->get_entry()));
        addInnerContainer(container);
        offset += 4;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 4));
        container->setName("e_phoff: " + printHex(elfio->get_segments_offset()));
        addInnerContainer(container);
        offset += 4;

        container = new Container(getFile(), false, std::make_pair(offset, offset + 4));
        container->setName("e_shoff: " + printHex(elfio->get_sections_offset()));
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
