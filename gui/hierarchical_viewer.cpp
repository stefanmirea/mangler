#include "hierarchical_viewer.hpp"

HierarchicalViewer::HierarchicalViewer(QWidget *parent) : QTreeWidget(parent)
{
    headerItem()->setHidden(true);
}

QTreeWidgetItem *HierarchicalViewer::addRoot(const char *name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(this);
    item->setText(0, QString(name));
    addTopLevelItem(item);
    return item;
}

QTreeWidgetItem *HierarchicalViewer::addChild(QTreeWidgetItem *parent, const char *name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, QString(name));
    parent->addChild(item);
    return item;
}
