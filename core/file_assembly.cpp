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

#include "file_assembly.hpp"
#include <QString>

std::string FileAssembly::disassembleCode(const std::string &code)
{
    char instr1[] = {0x89, 0x85, 0x24, 0xff, 0xff, 0xff};
    char instr2[] = {0x8b, 0x85, 0x24, 0xff, 0xff, 0xff};
    if (code.size() == 6)
    {
        bool matches = true;
        for (unsigned int i = 0; i < 6; ++i)
            if (code[i] != instr1[i])
            {
                matches = false;
                break;
            }
        if (matches)
            return "mov DWORD PTR [rbp-0xdc],eax";
        matches = true;
        for (unsigned int i = 0; i < 6; ++i)
            if (code[i] != instr2[i])
            {
                matches = false;
                break;
            }
        if (matches)
            return "mov eax,DWORD PTR [rbp-0xdc]";
    }
    return std::string("nop");
}

std::string FileAssembly::assembleCode(const std::string &instruction)
{
    return "";
}
