#include "file_handler.hpp"
#include "elf_file.hpp"

FileHandler::FileHandler() {};

bool FileHandler::open(const std::string &filename)
{
    FileUnit *file;

    /* check file type
     * TODO: use error codes instead of bool */
    file = new ELFFile(filename);
    if (file->getOpenStatus())
    {
        openFiles.push_back(file);
        return true;
    }

    /* check other file types */

    /* unknown file format */
    return false;
}

bool FileHandler::close(FileUnit *file)
{
    return false;
}

bool FileHandler::save(FileUnit *file)
{
    return file->save(file->getName());
}

bool FileHandler::save(FileUnit *file, std::string &newName)
{
    return file->save(newName);
}

FileHandler::~FileHandler() {}
