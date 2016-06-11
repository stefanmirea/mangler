/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Ștefan-Gabriel Mirea, Adrian Dobrică
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

#include "hierarchy_node.hpp"

HierarchyNode::HierarchyNode(Container *container, QHexEdit *hexEditor, QTreeWidget *parent) :
    QTreeWidgetItem(parent), hexEditor(hexEditor)
{
    _HierarchyNode(container);
}

HierarchyNode::HierarchyNode(Container *container, QHexEdit *hexEditor, QTreeWidgetItem *parent) :
    QTreeWidgetItem(parent), hexEditor(hexEditor)
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
}

bool HierarchyNode::createChildren()
{
    if (!everExpanded)
    {
        everExpanded = true;
        std::vector<Container *> children = container->getInnerContainers();
        for (unsigned int i = 0; i < children.size(); ++i)
            addChild(new HierarchyNode(children[i], hexEditor, this));
        return true;
    }
    return false;
}

QWidget *HierarchyNode::getSpecialRepresentation()
{
    return container->getSpecialRepresentation(hexEditor);
}

bool HierarchyNode::keepSpecialRepresentation()
{
    return container->keepSpecialRepresentation();
}

bool HierarchyNode::sharesContainer(HierarchyNode *node)
{
    return node && container == node->container;
}

bool HierarchyNode::hasContainerCounterpart(HierarchyNode *oldNode,
    std::unordered_map<Container *, Container *> &counterparts)
{
    return counterparts[container] == oldNode->container;
}

std::pair<int, int> &HierarchyNode::getInterval()
{
    return container->getInterval();
}
