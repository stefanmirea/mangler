#ifndef FILE_UNIT_H_
#define FILE_UNIT_H_

#include "elfio_wrapper.h"
#include <string>

template <typename T>
class FileUnit
{
public:
    FileUnit(std::string& filename);

    virtual ~FileUnit();

private:
    std::string filename;
    T *fileWrapper;
};

#endif
