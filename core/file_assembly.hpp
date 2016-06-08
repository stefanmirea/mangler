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

#ifndef FILE_ASSEMBLY_HPP_
#define FILE_ASSEMBLY_HPP_

#include <cstdint>
#include <string>
#include <map>
#include <vector>
/**
 * Provides methods for converting from machine code instructions to assembly language and vice
 * versa.
 */

struct asmInstr
{
    unsigned long long address;
    std::string assembled;
    std::string opcode;
    std::string args;

    void clear()
    {
        address = 0LL;
        assembled.clear();
        opcode.clear();
        args.clear();
    }
};

class FileAssembly
{
public:
    static std::string disassembleCode(const std::string &machineCode);
    static std::string assembleCode(const std::string &instruction, bool &ok);
    static void disassemble_section(const std::string &filename, const std::string &sectionName,
                             std::map<std::string, unsigned long long> &labels,
                             std::vector<asmInstr> &instructions);
};

#endif // FILE_ASSEMBLY_HPP_
