#ifndef FILE_UNIT_H_
#define FILE_UNIT_H_

#include <string>

class FileUnit
{
public:
    FileUnit(std::string &filename);
    std::string &getName();
    virtual bool getOpenStatus() = 0;
    virtual bool save(std::string &filename) = 0;
    virtual ~FileUnit();

private:
    std::string filename;
};

#endif
