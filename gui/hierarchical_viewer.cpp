#include "hierarchical_viewer.hpp"

HierarchicalViewer::HierarchicalViewer(QWidget *parent) : QTreeWidget(parent)
{
    headerItem()->setHidden(true);
    connect(this, SIGNAL(itemExpanded(QTreeWidgetItem *)),
            this, SLOT(expand(QTreeWidgetItem *)));
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
