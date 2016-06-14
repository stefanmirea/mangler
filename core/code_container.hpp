/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Adrian Dobrică, Ștefan-Gabriel Mirea
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CODE_CONTAINER_HPP_
#define CODE_CONTAINER_HPP_

class CodeContainer;

#include "container.hpp"
#include "special_representation/code/asm_viewer.hpp"
#include "special_representation/code/modify_asmbar.hpp"

/**
 * Generic class for areas containing executable machine code.
 * Can be used for any executable file format.
 */
class CodeContainer : public Container
{
public:
    class CodeRepresentationState : public RepresentationState
    {
    public:
        int selectedIndex;
        QString modifyBarContent;
        virtual ~CodeRepresentationState() {}
    };

    CodeContainer(FileUnit *file);
    CodeContainer(FileUnit *file, const std::pair<int, int> &interval);
    bool canInject();
    virtual std::vector<Container *> &getInnerContainers();
    virtual QWidget *doSpecialRepresentation(QHexEdit *hexEditor, bool &keepAfterNodeDeselection);
    virtual void injectCode(size_t offset, std::string &newContent);
    virtual void getRepresentationState(QWidget *specialRepresentation, RepresentationState *&state);
    virtual bool applyRepresentationState(QWidget *specialRepresentation,
                                          RepresentationState *state);
    virtual ~CodeContainer();

    virtual unsigned int addressToOffset(unsigned long long address) = 0;
    virtual void getContent(std::vector<std::pair<unsigned long long, std::string>> &content) = 0;
    virtual void overwrite(unsigned long long address, std::string newMachineCode) = 0;

    /* not really universal, but temporarily used for disassembling instructions in ELF files */
    virtual std::string getSectionName() = 0;

protected:
    bool injectionPossible;

private:
    ASMViewer *asmView;
    ModifyASMBar *asmBar;
    bool getASMWidgets(QWidget *specialRepresentation, ASMViewer *&asmView, ModifyASMBar *&asmBar);
};

#endif // CODE_CONTAINER_HPP_
