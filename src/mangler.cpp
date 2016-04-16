#include "file_assembly.h"
#include "search_engine.h"
#include "container.h"
#include "code_container.h"
#include "file_unit.h"
#include "elf_file.h"
#include "file_handler.h"
#include "elfio/elfio.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <executable path>\n";
        return 1;
    }

    FileHandler *fh = new FileHandler;
    if (fh->open(std::string(argv[1])))
        std::cout << "It works.\n";
    else
        std::cout << "It doesn't work.\n";
    delete fh;

    return 0;
}
