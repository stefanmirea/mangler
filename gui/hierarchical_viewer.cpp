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
