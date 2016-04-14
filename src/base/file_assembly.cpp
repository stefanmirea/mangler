#include "file_assembly.h"

FileAssembly::FileAssembly() {}

FileAssembly::~FileAssembly() {}

FileAssembly::Disassembler::Disassembler() {}

FileAssembly::Disassembler::~Disassembler() {}

std::string FileAssembly::Disassembler::disassembleCode(uint8_t *code)
{
    return std::string("");
}

FileAssembly::Assembler::Assembler() {}

FileAssembly::Assembler::~Assembler() {}

uint8_t *FileAssembly::Assembler::assembleCode(std::string &code)
{
    return nullptr;
}
