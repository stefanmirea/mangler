#ifndef HIERARCHY_NODE_HPP
#define HIERARCHY_NODE_HPP

#include <QTreeWidgetItem>
#include "container.hpp"

class HierarchyNode : public QTreeWidgetItem
{
public:
    explicit HierarchyNode(Container *container, QTreeWidget *parent = 0);
    explicit HierarchyNode(Container *container, QTreeWidgetItem *parent = 0);
    bool createChildren();
    bool keepSpecialRepresentation();
    QWidget *getSpecialRepresentation();
    virtual ~HierarchyNode();
private:
    void _HierarchyNode(Container *container);
    Container *container;
    bool everExpanded;
    bool _keepSpecialRepresentation;
    QWidget *specialRepresentation;
};

#endif
