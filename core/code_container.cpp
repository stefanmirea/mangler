#include "code_container.hpp"

CodeContainer::CodeContainer(FileUnit *file)
    : Container(file, false), injectionPossible(false) {}

CodeContainer::CodeContainer(FileUnit *file, std::pair<int, int> &interval)
    : Container(file, false, interval), injectionPossible(false) {}

bool CodeContainer::canInject()
{
    return injectionPossible;
}

std::vector<Container *> &CodeContainer::getInnerContainers()
{
    return innerContainers;
}

bool CodeContainer::doSpecialRepresentation()
{
    /* create disassembly area */

    if (canInject())
    {
        /* create Inject options in the context menu and set the injectCode
         * method to be called from inside the handler */
    }

    return true;
}

/**
 * In order to keep this class generic among different executable file formats,
 * do not fill up this method. If you want to implement code injection for your
 * file format, create a new class derived from CodeContainer.
 */
void CodeContainer::injectCode(size_t offset, std::string &newContent) {}

CodeContainer::~CodeContainer() {}
