#include "file_assembly.hpp"

FileAssembly::FileAssembly() {}

FileAssembly::~FileAssembly() {}

FileAssembly::Disassembler::Disassembler() {}

FileAssembly::Disassembler::~Disassembler() {}

std::string FileAssembly::Disassembler::disassembleCode(uint8_t *code, unsigned int length)
{
    return std::string("");
}

FileAssembly::Assembler::Assembler() {}

FileAssembly::Assembler::~Assembler() {}

uint8_t *FileAssembly::Assembler::assembleCode(std::string &code)
{
    return nullptr;
}
