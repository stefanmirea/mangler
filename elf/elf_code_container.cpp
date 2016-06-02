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

#include "elf_code_container.hpp"

using namespace elf;

ELFCodeContainer::ELFCodeContainer(ELFFile *file, const std::pair<int, int> &interval) :
    CodeContainer(file, interval)
{
    injectionPossible = false;
}

unsigned int ELFCodeContainer::addressToOffset(unsigned long long address)
{
    /* TODO */
    return address - 0x400000;
}

void ELFCodeContainer::getContent(std::vector<std::pair<unsigned long long, std::string>> &content)
{
    ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
    assert(efile != nullptr);
#endif
    /* TODO: populate content using ELFIO */
    efile->getELFIO();

    content.clear();
    content.push_back(std::make_pair(4220471, "AB"));
    content.push_back(std::make_pair(4220477, "CDE"));
}

void ELFCodeContainer::overwrite(unsigned long long address, std::string newMachineCode)
{
    ELFFile *efile = dynamic_cast<ELFFile *>(getFile());
#ifdef DEBUG
    assert(efile != nullptr);
#endif
    /* TODO: update efile->getELFIO() */
    efile->getELFIO();
}

ELFCodeContainer::~ELFCodeContainer() {}
