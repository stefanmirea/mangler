#include "code_entry.h"

CodeEntry::CodeEntry(FileUnit *file)
    : Entry(file, false), injectionPossible(false) {}

CodeEntry::CodeEntry(FileUnit *file, std::pair<int, int> &interval)
    : Entry(file, false, interval), injectionPossible(false) {}

bool CodeEntry::canInject()
{
    return injectionPossible;
}

std::vector<Entry *> &CodeEntry::getInnerEntries()
{
    return innerEntries;
}

bool CodeEntry::doSpecialRepresentation()
{
    /* create disassembly area */

    if (canInject())
    {
        /* create Inject options in the context menu and set the injectCode
         * method to be called from inside the handler */
    }
}

/**
 * In order to keep this class generic among different executable file formats,
 * do not fill up this method. If you want to implement code injection for your
 * file format, create a new class derived from CodeEntry.
 */
void CodeEntry::injectCode(size_t offset, std::string &newContent) {}

CodeEntry::~CodeEntry() {}
