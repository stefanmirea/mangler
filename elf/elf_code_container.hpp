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

#ifndef ELF_CODE_CONTAINER_HPP_
#define ELF_CODE_CONTAINER_HPP_

#include "elfio/elfio.hpp"
#include "code_container.hpp"
#include "elf_file.hpp"

namespace elf
{
/**
 * The CodeContainer responsible for managing ELF code sections.
 */

class ELFCodeContainer : public CodeContainer
{
public:
    ELFCodeContainer(ELFFile *file, const std::pair<int, int> &interval, unsigned int index);
    unsigned int addressToOffset(unsigned long long address);
    void getContent(std::vector<std::pair<unsigned long long, std::string>> &content);
    void overwrite(unsigned long long address, std::string newMachineCode);
    virtual ~ELFCodeContainer();

    unsigned int index;
};
}

#endif // ELF_CODE_CONTAINER_HPP_
