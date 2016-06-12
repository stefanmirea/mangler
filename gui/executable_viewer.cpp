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
#include <stack>

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

        HierarchyNode *nodeOfInterest = dynamic_cast<HierarchyNode *>(
            hierarchicalViewer->getNodeOfInterest()
        );

#ifdef DEBUG
        assert(nodeOfInterest != nullptr);
#endif

        /* If the currently selected HierarchyNode's container wanted to keep its special
         * representation after being deselected, the QWidget will be deallocated in that
         * container's destructor. */
        if (nodeOfInterest->keepSpecialRepresentation())

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

bool ExecutableViewer::refresh(const std::string &fileName)
{
    /* Save the modified file. */
    if (!hexViewer->saveFile(QString(fileName.c_str())))
        return false;

    HierarchyNode *nodeOfInterest = hierarchicalViewer->getNodeOfInterest();
    bool keepSpecialRepresentation = nodeOfInterest && nodeOfInterest->keepSpecialRepresentation();
    int oldTopLevelItemCount = hierarchicalViewer->topLevelItemCount();

    /* Create new top-level containers. */
    std::vector<Container *> oldRootContainers;
    oldRootContainers.swap(fileUnit->getTopLevelContainers());

    if (!fileUnit->loadFile(fileName))
        QMessageBox::warning(this, QString("Warning"),
            QString("The file is not a valid %1 executable in the current form.\nWhile you can "
                "keep editing using the hexadecimal editor, you will not be able to take advantage "
                "of the hierarchical viewer. Make sure that your file is a valid %1 executable, "
                "then refresh your view.").arg(fileUnit->getFormatName().c_str()));

    /* Create new HierarchicalViewer top-level nodes. */
    std::vector<Container *> &rootContainers = fileUnit->getTopLevelContainers();
    for (unsigned int i = 0; i < rootContainers.size(); ++i)
        hierarchicalViewer->addRoot(rootContainers[i]);

    /* Identify new container graph with the old one. */
    std::unordered_map<Container *, Container *> counterparts;
    Container::resemble(oldRootContainers, rootContainers, counterparts);

    /* Create new special representations for the identified containers whose old counterparts had
     * such representations. */
    QWidget *specialRepToShow = nullptr;
    for (std::unordered_map<Container *, Container *>::iterator u = counterparts.begin();
            u != counterparts.end(); ++u)
    {
        bool keptSpecial = u->second->keepSpecialRepresentation() &&
                           u->second->getSpecialRepresentation(hexViewer);
        bool ofInterest = nodeOfInterest && nodeOfInterest->hasContainer(u->second);
        if (keptSpecial || ofInterest)
        {
            RepresentationState *state = nullptr;
            if (ofInterest)
            {
                /* The old representation can be temporary in this case. */
                QWidget *specialRep = split->widget(2);
                if (specialRep != defaultSpecialRep)
                    u->second->getRepresentationState(specialRep, state);
            }
            else
                u->second->getRepresentationState(u->second->getSpecialRepresentation(hexViewer),
                                                  state);
            QWidget *newSpecialRep = u->first->getSpecialRepresentation(hexViewer);
            if (!ofInterest && !u->first->keepSpecialRepresentation())
            {
                if (newSpecialRep)
                    delete newSpecialRep;
                if (state)
                    delete state;
                continue;
            }
            if (newSpecialRep && state)
                u->first->applyRepresentationState(newSpecialRep, state);
            if (ofInterest)
                /* newSpecialRep can be any of nullptr, kept or temporary (not kept). */
                specialRepToShow = newSpecialRep;
            if (state)
                delete state;
        }
    }
    if (!specialRepToShow)
        specialRepToShow = defaultSpecialRep;

    /* Restore previous HierarchicalViewer nodes expansion state. */
    HierarchyNode *toBeSelected = nullptr;
    std::stack<std::pair<HierarchyNode *, HierarchyNode *>> nodes;
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
        if (newNode->hasContainerCounterpart(oldNode, counterparts))
        {
            if (oldNode->getEverExpanded() &&
                    newNode->childIndicatorPolicy() == QTreeWidgetItem::ShowIndicator)
                nodes.push(std::make_pair(newNode, oldNode));
            if (oldNode == nodeOfInterest)
                toBeSelected = newNode;
        }
    }
    while (!nodes.empty())
    {
        HierarchyNode *newFirst = nodes.top().first;
        HierarchyNode *oldFirst = nodes.top().second;
        nodes.pop();
        hierarchicalViewer->expandItem(newFirst);
        for (int i = 0; i < newFirst->childCount() && i < oldFirst->childCount(); ++i)
        {
            HierarchyNode *oldNode = dynamic_cast<HierarchyNode *>(oldFirst->child(i));
            HierarchyNode *newNode = dynamic_cast<HierarchyNode *>(newFirst->child(i));
#ifdef DEBUG
            assert(oldNode != nullptr && newNode != nullptr);
#endif

            if (newNode->hasContainerCounterpart(oldNode, counterparts))
            {
                if (oldNode->getEverExpanded() &&
                        newNode->childIndicatorPolicy() == QTreeWidgetItem::ShowIndicator)
                    nodes.push(std::make_pair(newNode, oldNode));
                if (oldNode == nodeOfInterest)
                    toBeSelected = newNode;
            }
        }
        if (!oldFirst->isExpanded())
            hierarchicalViewer->collapseItem(newFirst);
    }

    /* Destroy old HierarchicalViewer nodes */
    hierarchicalViewer->setHandleSelection(false);
    for (int i = 0; i < oldTopLevelItemCount; ++i)
        delete hierarchicalViewer->takeTopLevelItem(0);
    hierarchicalViewer->setHandleSelection(true);

    /* Update the current selection and special representation. */
    hierarchicalViewer->setHandleSelection(false);
    hierarchicalViewer->clearSelection();
    hierarchicalViewer->reset();
    if (toBeSelected != nullptr)
        toBeSelected->setSelected(true);
    hierarchicalViewer->setHandleSelection(true);

    QWidget *currentSpecialRep = split->widget(2);
    if (currentSpecialRep != specialRepToShow)
    {
        currentSpecialRep->setParent(Q_NULLPTR);
        if (!keepSpecialRepresentation)
            delete currentSpecialRep;
        /* else, it will be deallocated in the container's destructor */
        split->addWidget(specialRepToShow);
    }

    /* Delete all of the old containers. */
    Container::deleteGraph(oldRootContainers);

    refreshable = false;

    return true;
}

bool ExecutableViewer::save()
{
    return saveFile(fileUnit->getName());
}

bool ExecutableViewer::saveAs()
{
    QString originalName = QFileDialog::getSaveFileName(this, QString("Save As"),
        QString::fromStdString(fileUnit->getName()));
    if (originalName == "")
        return false;

    std::string name = QFileInfo(originalName).canonicalFilePath().toStdString();
    if (saveFile(name))
    {
        fileUnit->getName() = name;
        setWindowTitle(QString(name.c_str()) + "[*]");
        return true;
    }

    return false;
}

bool ExecutableViewer::saveFile(const std::string &fileName)
{
    if (!refresh(fileName))
    {
        QMessageBox::critical(this, QString("Error"),
            QString("Unable to save file %1.").arg(fileName.c_str()));
        return false;
    }
    setWindowModified(false);
    return true;
}

void ExecutableViewer::closeEvent(QCloseEvent *event)
{
    bool accept;

    if (!isWindowModified())
        accept = true;
    else
    {
        QMessageBox::StandardButton response = QMessageBox::warning(this, QString("Warning"),
            QString("\"%1\" has been modified. Save changes before closing?").
                arg(fileUnit->getName().c_str()),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (response == QMessageBox::Save)
            accept = saveFile(fileUnit->getName());
        else
            accept = response == QMessageBox::Discard;
    }

    accept ? event->accept() : event->ignore();
}
