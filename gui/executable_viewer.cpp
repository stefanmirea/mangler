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

#include "executable_viewer.hpp"
#include "QDesktopWidget"
#include "QApplication"
#include <QFile>
#include "qhexedit.hpp"
#include <iostream>
#include <qdebug.h>

ExecutableViewer::ExecutableViewer(FileUnit *fileUnit, QWidget *parent) :
    QWidget(parent), fileUnit(fileUnit)
{
    setWindowModified(false);
    setWindowTitle(QString(fileUnit->getName().c_str()) + "[*]");

    QWidget *left = new QWidget(this);
    QWidget *center = new QWidget(this);

    split = new QSplitter(this);

    /* Right extra component */
    defaultSpecialRep = createDefaultSpecialRep();

    /* Left panel - hierarchy */
    QHBoxLayout *hv = new QHBoxLayout;
    hv->setContentsMargins(QMargins());
    left->setLayout(hv);

    /* Center hex viewer and search bar */
    hexViewer = new QHexEdit(this, this);
    hexViewer->loadFile();

    hierarchicalViewer = new HierarchicalViewer(split, defaultSpecialRep, hexViewer, this);

    std::vector<Container *> rootContainers = fileUnit->getTopLevelContainers();
    for (unsigned int i = 0; i < rootContainers.size(); ++i)
        hierarchicalViewer->addRoot(rootContainers[i]);

    hv->addWidget(hierarchicalViewer);

    searchBar = new SearchBar(hexViewer);
    QVBoxLayout *hexaLayout = new QVBoxLayout;
    hexaLayout->setContentsMargins(QMargins());
    hexaLayout->addWidget(hexViewer);
    hexaLayout->addWidget(searchBar);
    center->setLayout(hexaLayout);

    /* Split the three components */
    split->addWidget(left);
    split->addWidget(center);
    split->addWidget(defaultSpecialRep);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(QMargins());
    layout->addWidget(split);

    setLayout(layout);
}

FileUnit *ExecutableViewer::getFileUnit()
{
    return fileUnit;
}

ExecutableViewer::~ExecutableViewer()
{
    if (split->widget(2) != defaultSpecialRep)
    {
        delete defaultSpecialRep;

        HierarchyNode *currentItem = dynamic_cast<HierarchyNode *>(
            hierarchicalViewer->currentItem()
        );

#ifdef DEBUG
        assert(currentItem != nullptr);
#endif

        /* If the currently selected HierarchyNode's container wanted to keep its special
         * representation after being deselected, the QWidget will be deallocated in that
         * container's destructor. */
        if (currentItem->keepSpecialRepresentation())

        /* The widget must be disconnected from the splitter, otherwise the splitter will
         * try to deallocate it too. Setting the parent to null is safe as the splitter will get
         * notified about its child being reparented. */
            split->widget(2)->setParent(Q_NULLPTR);
    }
    /* else defaultSpecialRep will be deallocated automatically by the splitter destructor */

    delete fileUnit;
}

bool ExecutableViewer::refresh(std::string &tmpName)
{
    return fileUnit->refresh(tmpName);
}
