#ifndef FILE_UNIT_H_
#define FILE_UNIT_H_

#include <string>

class FileUnit
{
public:
    std::string filename;

    FileUnit(std::string& filename);

    virtual ~FileUnit();
};

#endif
