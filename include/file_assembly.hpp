#ifndef FILE_ASSEMBLY_HPP_
#define FILE_ASSEMBLY_HPP_

#include <cstdint>
#include <string>

class FileAssembly
{
public:
    FileAssembly();

    class Disassembler
    {
    public:
        Disassembler();

        std::string disassembleCode(uint8_t *code, unsigned int length);

        virtual ~Disassembler();
    };

    class Assembler
    {
    public:
        Assembler();

        uint8_t *assembleCode(std::string &code);

        virtual ~Assembler();
    };

    virtual ~FileAssembly();

    Disassembler disassembler;
    Assembler assembler;
};

#endif
