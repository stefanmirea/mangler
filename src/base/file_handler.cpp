#include "file_handler.h"
#include "elfio_wrapper.h"

FileHandler::FileHandler() {};

bool FileHandler::open(std::string &filename)
{
    FileUnit *file;

    /* check file type
     * TODO: use error codes instead of bool */
    file = new ElfioWrapper(filename);
    if (file->getOpenStatus())
    {
        openedFiles.push_back(file);
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
