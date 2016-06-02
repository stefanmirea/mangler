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
#include "asm_viewer.hpp"
#include "modify_asmbar.hpp"

#include <QVBoxLayout>
#include <QObject>

/**
 * Creates the contents of the right side of an open file subwindow when the selected HierarchyNode
 * represents a code area.
 */
QWidget *CodeContainer::doSpecialRepresentation(QHexEdit *hexEditor, bool &keepAfterNodeDeselection)
{
    /* create disassembly area */
    QWidget *area = new QWidget();

    asmView = new ASMViewer(this, area);
    asmBar = new ModifyASMBar(this, asmView, hexEditor, area);

    QObject::connect(asmView->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), asmBar,
        SLOT(changeViewerSelection(const QItemSelection &, const QItemSelection &)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(QMargins());
    layout->addWidget(asmView);
    layout->addWidget(asmBar);

    area->setLayout(layout);

    if (canInject())
    {
        /* TODO: create Inject options in the context menu and set the injectCode
         * method to be called from inside the handler */
    }

    keepAfterNodeDeselection = true;
    return area;
}
