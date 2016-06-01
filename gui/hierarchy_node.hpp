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

#ifndef HIERARCHY_NODE_HPP_
#define HIERARCHY_NODE_HPP_

#include <QTreeWidgetItem>
#include "container.hpp"

/**
 * An item of the HierarchicalViewer. The relationship between HierarchyNodes and areas in the input
 * files is many to one. That is, different nodes can represent the same file area. See also the
 * Container class.
 */
class HierarchyNode : public QTreeWidgetItem
{
public:
    explicit HierarchyNode(Container *container, QTreeWidget *parent = 0);
    explicit HierarchyNode(Container *container, QTreeWidgetItem *parent = 0);
    bool createChildren();
    QWidget *getSpecialRepresentation();
    bool keepSpecialRepresentation();
    bool sharesContainer(HierarchyNode *node);
    Container *getContainer();
private:
    void _HierarchyNode(Container *container);
    Container *container;
    bool everExpanded;
};

#endif // HIERARCHY_NODE_HPP_
