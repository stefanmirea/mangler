#ifndef FILE_UNIT_HPP_
#define FILE_UNIT_HPP_

#include "container.hpp"
#include <string>
#include <vector>

class Container;

class FileUnit
{
public:
    FileUnit(const std::string &filename);
    std::string &getName();
    std::vector<Container *> &getTopLevelContainers();

    virtual bool getOpenStatus() = 0;
    virtual bool save(std::string &filename) = 0;
    virtual void modifyHex(size_t offset, std::string &newContent) = 0;
    virtual ~FileUnit();

private:
    std::string filename;
    std::vector<Container *> topLevelContainers;
};

#endif
