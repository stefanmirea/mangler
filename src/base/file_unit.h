#ifndef FILE_UNIT_H_
#define FILE_UNIT_H_

#include <string>

template <typename T>
class FileUnit
{
public:
    std::string filename;
    T *file;

    FileUnit(std::string& filename);

    virtual ~FileUnit();
};

#endif
