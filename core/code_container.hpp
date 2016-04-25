#ifndef CODE_CONTAINER_HPP_
#define CODE_CONTAINER_HPP_

#include "container.hpp"

/**
 * Generic class for areas containing executable machine code.
 * Can be used for any executable file format.
 */
class CodeContainer : public Container
{
public:
    CodeContainer(FileUnit *file);
    CodeContainer(FileUnit *file, const std::pair<int, int> &interval);
    bool canInject();
    virtual std::vector<Container *> &getInnerContainers();
    virtual QWidget *doSpecialRepresentation(bool &keepAfterNodeDeselection);
    virtual void injectCode(size_t offset, std::string &newContent);
    virtual ~CodeContainer();

private:
    class ASMViewer;
    class ModifyASMBar;
    bool injectionPossible;
};

#endif
