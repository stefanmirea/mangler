#include "file_assembly.hpp"
#include "search_engine.hpp"
#include "container.hpp"
#include "code_container.hpp"
#include "file_unit.hpp"
#include "elf_file.hpp"
#include "file_handler.hpp"
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
