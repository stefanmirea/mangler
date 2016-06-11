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

#include "code_container.hpp"

CodeContainer::CodeContainer(FileUnit *file)
    : Container(file, false) {}

CodeContainer::CodeContainer(FileUnit *file, const std::pair<int, int> &interval)
    : Container(file, false, interval) {}

bool CodeContainer::canInject()
{
    return injectionPossible;
}

std::vector<Container *> &CodeContainer::getInnerContainers()
{
    return innerContainers;
}

/**
 * In order to keep this class generic among different executable file formats,
 * do not fill up this method. If you want to implement code injection for your
 * file format, create a new class derived from CodeContainer.
 */
void CodeContainer::injectCode(size_t offset, std::string &newContent) {}

bool CodeContainer::getASMWidgets(QWidget *specialRepresentation, ASMViewer *&asmView,
                                  ModifyASMBar *&asmBar)
{
    asmView = nullptr;
    asmBar = nullptr;

    const QObjectList &children = specialRepresentation->children();
    for (QList<QObject *>::const_iterator u = children.begin(); u != children.end(); ++u)
    {
        if (!asmView)
        {
            ASMViewer *tempAsmView = dynamic_cast<ASMViewer *>(*u);
            if (tempAsmView)
                asmView = tempAsmView;
        }
        if (!asmBar)
        {
            ModifyASMBar *tempAsmBar = dynamic_cast<ModifyASMBar *>(*u);
            if (tempAsmBar)
                asmBar = tempAsmBar;
        }
    }

    return asmView && asmBar;
}

void CodeContainer::getRepresentationState(QWidget *specialRepresentation,
                                           RepresentationState *&state)
{
    ASMViewer *asmView;
    ModifyASMBar *asmBar;

    if (!getASMWidgets(specialRepresentation, asmView, asmBar))
        state = nullptr;
    else
    {
        CodeRepresentationState *codeState = new CodeRepresentationState;
        QModelIndexList list = asmView->selectionModel()->selectedIndexes();
        if (!list.size())
            codeState->selectedIndex = -1;
        else
            codeState->selectedIndex = list[0].row();
        codeState->modifyBarContent = asmBar->getText();
        state = codeState;
    }
}

bool CodeContainer::applyRepresentationState(QWidget *specialRepresentation,
                                             RepresentationState *state)
{
    CodeRepresentationState *codeState = dynamic_cast<CodeRepresentationState *>(state);
    if (!codeState)
        return false;

    ASMViewer *asmView;
    ModifyASMBar *asmBar;
    if (!getASMWidgets(specialRepresentation, asmView, asmBar))
        return false;

    if (codeState->selectedIndex > -1)
    {
        QStandardItemModel *model = asmView->getModel();
        int row = codeState->selectedIndex;
        if (row >= model->rowCount())
            row = model->rowCount() - 1;

        asmBar->setHandleSelection(false);
        asmView->selectionModel()->select(QItemSelection(
                model->index(row, 0),
                model->index(row, model->columnCount() - 1)),
            QItemSelectionModel::Select);
        asmBar->setHandleSelection(true);

        asmView->scrollTo(model->index(row, 0), QAbstractItemView::PositionAtCenter);
    }
    asmBar->setText(codeState->modifyBarContent);
    return true;
}

CodeContainer::~CodeContainer() {}
