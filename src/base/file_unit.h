#ifndef FILE_UNIT_H_
#define FILE_UNIT_H_

#include "entry.h"
#include <string>
#include <vector>

class Entry;

class FileUnit
{
public:
    FileUnit(std::string &filename);
    std::string &getName();
    std::vector<Entry *> &getTopLevelEntries();

    virtual bool getOpenStatus() = 0;
    virtual bool save(std::string &filename) = 0;
    virtual void modifyHex(size_t offset, std::string &newContent) = 0;
    virtual ~FileUnit();

private:
    std::string filename;
    std::vector<Entry *> topLevelEntries;
};

#endif
