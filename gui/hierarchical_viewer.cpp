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
    QWidget *parent) : QTreeWidget(parent), defaultSpecialRep(defaultSpecialRep), split(split)
{
    headerItem()->setHidden(true);
    connect(this, SIGNAL(itemExpanded(QTreeWidgetItem *)),
            this, SLOT(expand(QTreeWidgetItem *)));
    connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
            this, SLOT(change(QTreeWidgetItem *, QTreeWidgetItem *)));
}

HierarchyNode *HierarchicalViewer::addRoot(Container *container)
{
    HierarchyNode *item = new HierarchyNode(container, this);
    addTopLevelItem(item);
    return item;
}

HierarchyNode *HierarchicalViewer::addChild(HierarchyNode *parent, Container *container)
{
    HierarchyNode *item = new HierarchyNode(container, parent);
    parent->addChild(item);
    return item;
}

void HierarchicalViewer::expand(QTreeWidgetItem *item)
{
    HierarchyNode *node = dynamic_cast<HierarchyNode *>(item);
    if (node)
        node->createChildren();
}

void HierarchicalViewer::change(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    /* The 1st change call:
     *  performed automatically; previous: nullptr, current: first root, selectedItems().empty()
     * The 2nd change call:
     *  at the 1st click on a node; previous: first root, current: selected, selectedItems().empty()
     * The 3rd change call:
     *  at the 2nd click on a node; previous & current work as expected, !selectedItems().empty()
     * Etc. */

    HierarchyNode *currentNode = dynamic_cast<HierarchyNode *>(current);
    HierarchyNode *previousNode = dynamic_cast<HierarchyNode *>(previous);

    QWidget *currentSpecialRep = split->widget(2);

    QWidget *newSpecialRep = currentNode->getSpecialRepresentation();
    if (!newSpecialRep)
        newSpecialRep = defaultSpecialRep;

    if (newSpecialRep != currentSpecialRep)
    {
        if (!selectedItems().empty() && !previousNode->keepSpecialRepresentation())
            delete currentSpecialRep;
        else
            /* If the previous representation was the default, it will be deallocated in the
             * ExecutableViewer destructor; else, in the destructor of the HierarchyNode which kept
             * the QWidget. */
            currentSpecialRep->setParent(Q_NULLPTR);

        split->addWidget(newSpecialRep);
    }
}
