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

#include "hierarchical_viewer.hpp"

HierarchicalViewer::HierarchicalViewer(QSplitter *split, QWidget *defaultSpecialRep,
    QHexEdit *hexViewer, QWidget *parent) : QTreeWidget(parent), defaultSpecialRep(defaultSpecialRep),
                                            split(split), hexViewer(hexViewer)
{
    headerItem()->setHidden(true);
    setFont(QFont("Monospace", 10));
    previous = nullptr;
    handleSelection = true;

    connect(this, SIGNAL(itemExpanded(QTreeWidgetItem *)),
            this, SLOT(expand(QTreeWidgetItem *)));
    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(select()));
}

HierarchyNode *HierarchicalViewer::addRoot(Container *container)
{
    HierarchyNode *item = new HierarchyNode(container, hexViewer, this);
    addTopLevelItem(item);
    return item;
}

HierarchyNode *HierarchicalViewer::addChild(HierarchyNode *parent, Container *container)
{
    HierarchyNode *item = new HierarchyNode(container, hexViewer, parent);
    parent->addChild(item);
    return item;
}

void HierarchicalViewer::reset()
{
    previous = nullptr;
}

void HierarchicalViewer::setHandleSelection(bool handleSelection)
{
    this->handleSelection = handleSelection;
}

/* getNodeOfInterest() vs. selected node:
 *     if the user pressed Ctrl + click to deselect the node, getNodeOfInterest() will still return
 *     that node's address, although no node will be selected at that time;
 * getNodeOfInterest() vs. current node:
 *     if the HierarchicalViewer has received focus before the first manual user selection, the
 *     current node will be the first one by default, while getNodeOfInterest() will return nullptr.
 */
HierarchyNode *HierarchicalViewer::getNodeOfInterest()
{
    return previous;
}

void HierarchicalViewer::expand(QTreeWidgetItem *item)
{
    HierarchyNode *node = dynamic_cast<HierarchyNode *>(item);
#ifdef DEBUG
    assert(node != nullptr);
#endif
    node->createChildren();
}

void HierarchicalViewer::select()
{
    if (!selectedItems().size())
        /* After deselection using Ctrl + click. */
        return;

    HierarchyNode *current = dynamic_cast<HierarchyNode *>(selectedItems()[0]);
#ifdef DEBUG
    assert(current != nullptr);
#endif

    if (handleSelection)
    {
        if (!current->sharesContainer(previous))
        {
            QWidget *currentSpecialRep = split->widget(2);

            QWidget *newSpecialRep = current->getSpecialRepresentation();
            if (!newSpecialRep)
                newSpecialRep = defaultSpecialRep;

            if (newSpecialRep != currentSpecialRep)
            {
                if (previous && !previous->keepSpecialRepresentation())
                    delete currentSpecialRep;
                else
                    /* If the previous representation was the default one, it will be deallocated in
                     * the ExecutableViewer destructor; else, in the destructor of the Container
                     * which kept the QWidget. */
                    currentSpecialRep->setParent(Q_NULLPTR);

                split->addWidget(newSpecialRep);
            }
        }

        std::pair<int, int> interval = current->getInterval();
        if (Container::isValidInterval(interval))
            hexViewer->selectData(interval.first, interval.second - interval.first);
    }

    previous = current;
}
