#include "hierarchy_node.hpp"

HierarchyNode::HierarchyNode(Container *container, QTreeWidget *parent) : QTreeWidgetItem(parent)
{
    _HierarchyNode(container);
}

HierarchyNode::HierarchyNode(Container *container, QTreeWidgetItem *parent) :
    QTreeWidgetItem(parent)
{
    _HierarchyNode(container);
}

void HierarchyNode::_HierarchyNode(Container *container)
{
    this->container = container;
    setText(0, QString(container->getName().c_str()));
    if (container->isExpandable())
        setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    else
        setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicator);
    everExpanded = false;
    _keepSpecialRepresentation = false;
    specialRepresentation = nullptr;
}

bool HierarchyNode::createChildren()
{
    if (!everExpanded)
    {
        everExpanded = true;
        std::vector<Container *> children = container->getInnerContainers();
        for (unsigned int i = 0; i < children.size(); ++i)
            addChild(new HierarchyNode(children[i], this));
        return true;
    }
    return false;
}

bool HierarchyNode::keepSpecialRepresentation()
{
    return _keepSpecialRepresentation;
}

QWidget *HierarchyNode::getSpecialRepresentation()
{
    if (_keepSpecialRepresentation)
        return specialRepresentation;
    QWidget *representation = container->doSpecialRepresentation(_keepSpecialRepresentation);
    if (_keepSpecialRepresentation)
        specialRepresentation = representation;
    return representation;
}

HierarchyNode::~HierarchyNode()
{
    if (_keepSpecialRepresentation &&
            /* the default Container::doSpecialRepresentation() returns a must-keep nullptr */
            specialRepresentation != nullptr)
        delete specialRepresentation;
}