#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include "file_unit.hpp"
#include <string>
#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>
#include <queue>

#define NO_INTERVAL -1

class FileUnit;

class Container
{
public:
    Container(FileUnit *file, bool expandable = false);
    Container(FileUnit *file, bool expandable, const std::pair<int, int> &interval);
    FileUnit *getFile();
    std::vector<Container *> &getParents();
    bool isExpandable();
    std::string &getName();
    void setName(const std::string &name);
    std::pair<int, int> &getInterval();

    virtual std::vector<Container *> &getInnerContainers();
    virtual bool doSpecialRepresentation();
    virtual ~Container();

    static bool isValidInterval(std::pair<int, int> &interval);
    static void invalidateInterval(std::pair<int, int> &interval);

protected:
    std::vector<Container *> innerContainers;
    bool addInnerContainer(Container *container);
    bool addInnerContainer(Container *container, size_t position);

private:
    FileUnit *file;
    std::vector<Container *> parents;
    bool expandable;
    std::pair<int, int> interval;
    std::string name;
};

#endif
