#ifndef CODE_ENTRY_H_
#define CODE_ENTRY_H_

#include "entry.h"

/**
 * Generic class for areas containing executable machine code.
 * Can be used for any executable file format.
 */
class CodeEntry : public Entry
{
public:
    CodeEntry(FileUnit *file);
    CodeEntry(FileUnit *file, std::pair<int, int> &interval);
    bool canInject();
    virtual std::vector<Entry *> &getInnerEntries();
    virtual bool doSpecialRepresentation();
    virtual void injectCode(size_t offset, std::string &newContent);
    virtual ~CodeEntry();

private:
    bool injectionPossible;
};

#endif
