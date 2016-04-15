#ifndef ENTRY_H_
#define ENTRY_H_

#include "file_unit.h"
#include <string>
#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>
#include <queue>

#define NO_INTERVAL -1

class FileUnit;

class Entry
{
public:
    Entry(FileUnit *file, bool expandable = false);
    Entry(FileUnit *file, bool expandable, std::pair<int, int> &interval);
    FileUnit *getFile();
    std::vector<Entry *> &getParents();
    bool isExpandable();
    std::string &getName();
    void setName(std::string &name);
    std::pair<int, int> &getInterval();

    virtual std::vector<Entry *> &getInnerEntries();
    virtual bool doSpecialRepresentation();
    virtual ~Entry();

    static bool isValidInterval(std::pair<int, int> &interval);
    static void invalidateInterval(std::pair<int, int> &interval);

protected:
    std::vector<Entry *> innerEntries;
    bool addInnerEntry(Entry *entry);
    bool addInnerEntry(Entry *entry, size_t position);

private:
    FileUnit *file;
    std::vector<Entry *> parents;
    std::pair<int, int> interval;
    bool expandable;
    std::string name;
};

#endif
