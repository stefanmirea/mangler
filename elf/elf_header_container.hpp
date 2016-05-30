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

#ifndef ELF_HEADER_CONTAINER_HPP_
#define ELF_HEADER_CONTAINER_HPP_

#include "container.hpp"
#include "elf_file.hpp"
#include "elf_entry.hpp"
#include <iostream>

namespace elf
{
/**
 * Container associated with the ELF header.
 */
class ELFHeaderContainer : public Container
{
public:
    ELFHeaderContainer(ELFFile *file, const std::pair<int, int> &interval);
    std::vector<Container *> &getInnerContainers();

    class e_ident_ei_mag0_t : public ELFEntry
    {
    public:
        e_ident_ei_mag0_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_ident_ei_mag1_t : public ELFEntry
    {
    public:
        e_ident_ei_mag1_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_ident_ei_mag2_t : public ELFEntry
    {
    public:
        e_ident_ei_mag2_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_ident_ei_mag3_t : public ELFEntry
    {
    public:
        e_ident_ei_mag3_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class ei_class_t : public ELFEntry
    {
    public:
        ei_class_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class ei_data_t : public ELFEntry
    {
    public:
        ei_data_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class ei_version_t : public ELFEntry
    {
    public:
        ei_version_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class ei_osabi_t : public ELFEntry
    {
    public:
        ei_osabi_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class ei_abiversion_t : public ELFEntry
    {
    public:
        ei_abiversion_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_ident_ei_pad_t : public ELFEntry
    {
    public:
        e_ident_ei_pad_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_type_t : public ELFEntry
    {
    public:
        e_type_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_machine_t : public ELFEntry
    {
    public:
        e_machine_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_version_t : public ELFEntry
    {
    public:
        e_version_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_entry_t : public ELFEntry
    {
    public:
        e_entry_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_phoff_t : public ELFEntry
    {
    public:
        e_phoff_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_shoff_t : public ELFEntry
    {
    public:
        e_shoff_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_flags_t : public ELFEntry
    {
    public:
        e_flags_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_ehsize_t : public ELFEntry
    {
    public:
        e_ehsize_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_phentsize_t : public ELFEntry
    {
    public:
        e_phentsize_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_phnum_t : public ELFEntry
    {
    public:
        e_phnum_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_shentsize_t : public ELFEntry
    {
    public:
        e_shentsize_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_shnum_t : public ELFEntry
    {
    public:
        e_shnum_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    class e_shstrndx_t : public ELFEntry
    {
    public:
        e_shstrndx_t(ELFFile *file, const std::pair<int, int> &interval);
        void update(char *data);
    };

    ~ELFHeaderContainer();
};
}

#endif // ELF_HEADER_CONTAINER_HPP_
