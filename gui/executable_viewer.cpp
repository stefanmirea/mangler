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
#include <QMessageBox>
#include "qhexedit.hpp"
#include <iostream>
#include <qdebug.h>

ExecutableViewer::ExecutableViewer(MainWindow *mainWindow, FileUnit *fileUnit, QWidget *parent) :
    QWidget(parent), mainWindow(mainWindow), fileUnit(fileUnit)
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
    hexViewer->loadFile(fileUnit->getName().c_str());

    hierarchicalViewer = new HierarchicalViewer(split, defaultSpecialRep, hexViewer, this);

    std::vector<Container *> &rootContainers = fileUnit->getTopLevelContainers();
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
    refreshable = false;
}

MainWindow *ExecutableViewer::getMainWindow()
{
    return mainWindow;
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

bool ExecutableViewer::isRefreshable()
{
    return refreshable;
}

void ExecutableViewer::setRefreshable(bool refreshable)
{
    this->refreshable = refreshable;
    mainWindow->updateActions();
}

bool ExecutableViewer::refresh()
{
    /* Create a temporary copy of the modified file. */
    std::string tmpName = fileUnit->getName() + ".tmp";
    if (!hexViewer->saveFile(QString(tmpName.c_str())))
    {
        QMessageBox::critical(this, QString("Error"),
            QString("Unable to create temporary file. Cannot refresh the view."));
        return false;
    }

    HierarchyNode *nodeOfInterest = hierarchicalViewer->getNodeOfInterest();
    bool keepSpecialRepresentation = nodeOfInterest && nodeOfInterest->keepSpecialRepresentation();
    int oldTopLevelItemCount = hierarchicalViewer->topLevelItemCount();

    /* Create new top-level containers. */
    std::vector<Container *> oldRootContainers;
    oldRootContainers.swap(fileUnit->getTopLevelContainers());

    if (!fileUnit->loadFile(tmpName))
        QMessageBox::warning(this, QString("Warning"),
            QString("The file is not a valid %1 executable in the current form.\nWhile you can "
                "keep editing using the hexadecimal editor, you will not be able to take advantage "
                "of the hierarchical viewer. Make sure that your file is a valid %1 executable, "
                "then refresh your view.").arg(fileUnit->getFormatName().c_str()));

    /* Create new HierarchicalViewer top-level nodes. */
    std::vector<Container *> &rootContainers = fileUnit->getTopLevelContainers();
    for (unsigned int i = 0; i < rootContainers.size(); ++i)
        hierarchicalViewer->addRoot(rootContainers[i]);
    hierarchicalViewer->reset();

    /* Identify new container graph with the old one. */
    std::unordered_map<Container *, Container *> counterparts;
    Container::resemble(oldRootContainers, rootContainers, counterparts);

    /* Restore previous HierarchicalViewer nodes expansion state. */
    std::queue<std::pair<HierarchyNode *, HierarchyNode *>> nodes;
    for (int i = 0; i < hierarchicalViewer->topLevelItemCount() - oldTopLevelItemCount &&
        i < oldTopLevelItemCount; ++i)
    {
        HierarchyNode *oldNode = dynamic_cast<HierarchyNode *>(hierarchicalViewer->topLevelItem(i));
        HierarchyNode *newNode = dynamic_cast<HierarchyNode *>(
            hierarchicalViewer->topLevelItem(i + oldTopLevelItemCount)
        );
#ifdef DEBUG
        assert(oldNode != nullptr && newNode != nullptr);
#endif
        if (newNode->hasContainerCounterpart(oldNode, counterparts) && oldNode->isExpanded() &&
                newNode->childIndicatorPolicy() == QTreeWidgetItem::ShowIndicator)
            nodes.push(std::make_pair(newNode, oldNode));
    }
    while (!nodes.empty())
    {
        HierarchyNode *newFirst = nodes.front().first;
        HierarchyNode *oldFirst = nodes.front().second;
        nodes.pop();
        hierarchicalViewer->expandItem(newFirst);
        for (int i = 0; i < newFirst->childCount() && i < oldFirst->childCount(); ++i)
        {
            HierarchyNode *oldNode = dynamic_cast<HierarchyNode *>(oldFirst->child(i));
            HierarchyNode *newNode = dynamic_cast<HierarchyNode *>(newFirst->child(i));
#ifdef DEBUG
            assert(oldNode != nullptr && newNode != nullptr);
#endif

            if (newNode->hasContainerCounterpart(oldNode, counterparts) && oldNode->isExpanded() &&
                    newNode->childIndicatorPolicy() == QTreeWidgetItem::ShowIndicator)
                nodes.push(std::make_pair(newNode, oldNode));
        }
    }

    /* Destroy old HierarchicalViewer nodes */
    hierarchicalViewer->setDeletingContent(true);
    for (int i = 0; i < oldTopLevelItemCount; ++i)
    {
        QTreeWidgetItem *oldNode = hierarchicalViewer->takeTopLevelItem(0);
        delete oldNode;
    }
    hierarchicalViewer->setDeletingContent(false);

    /* Replace the current special representation with the default one. */
    QWidget *currentSpecialRep = split->widget(2);
    if (currentSpecialRep != defaultSpecialRep)
    {
        currentSpecialRep->setParent(Q_NULLPTR);
        if (!keepSpecialRepresentation)
            delete currentSpecialRep;
        /* else, it will be deallocated in the container's destructor */
        split->addWidget(defaultSpecialRep);
    }

    /* Delete all of the old containers. */
    Container::deleteGraph(oldRootContainers);

    return true;
}
