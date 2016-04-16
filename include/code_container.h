#ifndef CODE_CONTAINER_H_
#define CODE_CONTAINER_H_

#include "container.h"

/**
 * Generic class for areas containing executable machine code.
 * Can be used for any executable file format.
 */
class CodeContainer : public Container
{
public:
    CodeContainer(FileUnit *file);
    CodeContainer(FileUnit *file, std::pair<int, int> &interval);
    bool canInject();
    virtual std::vector<Container *> &getInnerContainers();
    virtual bool doSpecialRepresentation();
    virtual void injectCode(size_t offset, std::string &newContent);
    virtual ~CodeContainer();

private:
    bool injectionPossible;
};

#endif
