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

#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include "file_unit.hpp"
#include <string>
#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>
#include <queue>
#include <QWidget>
#include <unordered_map>

#define NO_INTERVAL -1

class FileUnit;
class QHexEdit;

/**
 * Information associated with a HierarchyNode. While HierarchyNodes are arranged in a tree
 * structure, Containers make up a directed acyclic graph. That's because different nodes
 * corresponding to the same area in the input file share the same Container object.
 */
class Container
{
public:
    /* Use this form with expandable = false only if you want to set de interval later
     * (after obtaining its reference by using getInterval()) */
    Container(FileUnit *file, bool expandable = false);

    Container(FileUnit *file, bool expandable, const std::pair<int, int> &interval);

    FileUnit *getFile();
    std::vector<Container *> &getParents();
    bool isExpandable();
    std::string &getName();
    void setName(const std::string &name);
    std::pair<int, int> &getInterval();
    QWidget *getSpecialRepresentation(QHexEdit *hexViewer);
    bool keepSpecialRepresentation();

    virtual std::vector<Container *> &getInnerContainers();
    virtual ~Container();
    static void deleteGraph(std::vector<Container *> &topLevelContainers);
    static void resemble(std::vector<Container *> &oldTopLevel,
                         std::vector<Container *> &newTopLevel,
                         std::unordered_map<Container *, Container *> &counterparts);

    static bool isValidInterval(std::pair<int, int> &interval);
    static void invalidateInterval(std::pair<int, int> &interval);

protected:
    std::vector<Container *> innerContainers;
    bool addInnerContainer(Container *container);
    bool addInnerContainer(Container *container, size_t position);

private:
    FileUnit *file;
    std::vector<Container *> parents;
    bool expandable;
    std::pair<int, int> interval;
    std::string name;
    bool _keepSpecialRepresentation;
    QWidget *specialRepresentation;
    virtual QWidget *doSpecialRepresentation(QHexEdit *hexEditor, bool &keepAfterNodeDeselection);
};

#endif // CONTAINER_HPP_
