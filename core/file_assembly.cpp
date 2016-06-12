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

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>

#define MAXSIZE 5000

void FileAssembly::disassembleSection(const std::string &filename, const std::string &sectionName,
                         std::map<std::string, unsigned long long> &labels,
                         std::vector<asmInstr> &instructions)
{
    char buffer[MAXSIZE];
    FILE *fp;
    std::string cmd;
    bool foundSection = false;

    cmd = "objdump -s -j " + sectionName + " -M intel -D " + filename;

    if ((fp = popen(cmd.data(), "r")) == NULL)
    {
        std::cerr << "Error on pipe opening." << std::endl;
        return;
    }

    instructions.clear();
    labels.clear();

    while (fgets(buffer, MAXSIZE, fp) != NULL)
    {
        if (foundSection == false)
        {
            if (strstr(buffer, "Disassembly of section"))
            {
                foundSection = true;
                continue;
            }

            else
                continue;
        }

        else
        if (foundSection == true)
        {
            /* Search for labels */
            if (strstr(buffer, ">:\n"))
            {
                char *token;

                token = strtok(buffer, " ");
                if (token)
                {
                    char *end;
                    unsigned long long addr = strtoull(token, &end, 16);

                    token = strtok(NULL, " ");
                    if (token)
                    {
                        char *endtoken = strstr(token, ">:");
                        if (endtoken)
                        {
                            endtoken[1] = '\0';
                        }

                        labels.insert(std::pair<std::string, unsigned long long>(std::string(token), addr));
                    }
                }
            }

            /* Search for instructions */
            else
            if (strstr(buffer, ":\t"))
            {
                char *token;
                token = strtok(buffer + 1, "\t");

                if (token)
                {
                    asmInstr instr;
                    char *end;

                    /* Remove ':' */
                    token[strlen(token) - 1] = '\0';

                    /* Store the address of the instruction */
                    instr.address = strtoull(token, &end, 16);
                    token = strtok(NULL, "\t");

                    if (token)
                    {
                        /* Remove trailing spaces */
                        unsigned int iterator = strlen(token) - 1;
                        while (token[iterator] == ' ')
                            iterator--;

                        if (iterator < strlen(token) - 1)
                            token[iterator + 1] = '\0';

                        /* Store the assembled content */
                        instr.assembled = std::string(token);

                        token = strtok(NULL, "\t");
                        if (token)
                        {
                            /* Remove newline */
                            token[(strlen(token) - 1)] = '\0';

                            if (token)
                            {
                                char *opcode = strtok(token, " ");
                                if (opcode)
                                {
                                    /* Store the instruction opcode */
                                    instr.opcode = std::string(opcode);

                                    /* Store the arguments */
                                    char *arg = strtok(NULL, " ");
                                    while (arg)
                                    {
                                        instr.args += std::string(arg);
                                        instr.args += " ";
                                        arg = strtok(NULL, " ");
                                    }

                                    if (instr.args.size() > 0)
                                    {
                                        instr.args.pop_back();
                                    }
                                }
                            }
                        }

                        instructions.push_back(instr);
                    }
                }
            }
        }
    }

    if (pclose(fp))
    {
        std::cerr << "Error on pipe exit." << std::endl;
        return;
    }
}

void assembleInstruction(const std::string &instruction, asmInstr &result)
{
    std::string filename = "tmpasm";

    result.clear();

    std::ofstream asmfile(filename + ".s", std::ofstream::out);
    asmfile << ".intel_syntax noprefix" << std::endl << "main:"
            << std::endl << instruction << std::endl;
    asmfile.close();

    std::system(std::string("gcc -c " + filename + ".s " + "-o " + filename + ".o").data());

    std::ifstream assembled(filename + ".o", std::ifstream::in);
    if (assembled.good())
    {
        std::string cmd = "objdump -M intel -d " + filename + ".o";
        FILE *fp;
        char buffer[MAXSIZE];
        bool foundInstr = false;

        if ((fp = popen(cmd.data(), "r")) == NULL)
        {
            std::cerr << "Error on pipe opening." << std::endl;
            return;
        }

        while (fgets(buffer, MAXSIZE, fp) != NULL)
        {
            if (foundInstr == false)
            {
                if (strstr(buffer, "<main>:"))
                {
                    foundInstr = true;
                    continue;
                }

                else
                    continue;
            }

            else
            {
                char *token = strtok(buffer, "\t");

                if (token)
                {
                    token = strtok(NULL, "\t");

                    if (token)
                    {
                        unsigned int iterator = strlen(token) - 1;
                        while (token[iterator] == ' ')
                            iterator--;

                        if (iterator < strlen(token) - 1)
                            token[iterator + 1] = '\0';

                        /* Store the assembled content */
                        result.assembled = std::string(token);
                        token = strtok(NULL, "\t");

                        if (token)
                        {
                            /* Remove newline */
                            token[(strlen(token) - 1)] = '\0';

                            if (token)
                            {
                                char *opcode = strtok(token, " ");
                                if (opcode)
                                {
                                    /* Store the instruction opcode */
                                    result.opcode = std::string(opcode);

                                    /* Store the arguments */
                                    char *arg = strtok(NULL, " ");
                                    while (arg)
                                    {
                                        result.args += std::string(arg);
                                        result.args += " ";
                                        arg = strtok(NULL, " ");
                                    }

                                    if (result.args.size() > 0)
                                    {
                                        result.args.pop_back();
                                    }
                                }
                            }
                        }
                    }
                }

                break;
            }
        }

        if (pclose(fp))
        {
            std::cerr << "Error on pipe exit." << std::endl;
        }
    }

    assembled.close();

    std::remove(std::string(filename + ".s").data());
    std::remove(std::string(filename + ".o").data());
}


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
    std::string ret = "??? RAW:";
    for (unsigned int i = 0; i < code.size(); ++i)
    {
        ret += QString::number((code[i] & 0xF0) >> 4, 16).toUpper().toStdString();
        ret += QString::number(code[i] & 0xF, 16).toUpper().toStdString();
    }
    return ret;
}

std::string FileAssembly::assembleCode(const std::string &instruction, bool &ok)
{
    /* Temporary usage:
     * - the user provides the instruction machine code in hex (no spaces);
     * - the method returns the corresponding binary string. */

    std::string padded;
    if (instruction.size() % 2 == 1)
        padded = std::string("0") + instruction;
    else
        padded = instruction;
    std::string ret;
    bool digitOK;
    for (unsigned int i = 0; i < padded.size(); i += 2)
    {
        char c = QString(padded[i]).toInt(&digitOK, 16) << 4;
        if (!digitOK)
        {
            ok = false;
            return "";
        }
        c |= QString(padded[i + 1]).toInt(&digitOK, 16);
        if (!digitOK)
        {
            ok = false;
            return "";
        }
        ret += c;
    }
    ok = true;
    return ret;
}
