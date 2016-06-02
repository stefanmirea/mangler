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

#include "container.hpp"

Container::Container(FileUnit *file, bool expandable) :
    file(file), expandable(expandable)
{
    _keepSpecialRepresentation = false;
    specialRepresentation = nullptr;
    invalidateInterval(interval);
}

Container::Container(FileUnit *file, bool expandable, const std::pair<int, int> &interval)
    : file(file), expandable(expandable), interval(interval)
{
    _keepSpecialRepresentation = false;
    specialRepresentation = nullptr;
}

FileUnit *Container::getFile()
{
    return file;
}

std::vector<Container *> &Container::getParents()
{
    return parents;
}

bool Container::isExpandable()
{
    return expandable;
}

std::string &Container::getName()
{
    return name;
}

void Container::setName(const std::string &name)
{
    this->name = name;
}

std::pair<int, int> &Container::getInterval()
{
#ifdef DEBUG
    assert(isExpandable() || isValidInterval(interval));
    if (isValidInterval(interval))
        for (unsigned int i = 0; i < parents.size(); ++i)
        {
            std::pair<int, int> &parentInterval = parents[i]->getInterval();
            if (isValidInterval(parentInterval))
                assert(parentInterval.first <= interval.first &&
                       interval.second <= parentInterval.second);
        }
#endif
    return interval;
}

QWidget *Container::getSpecialRepresentation(QHexEdit *hexEditor)
{
    if (_keepSpecialRepresentation)
        return specialRepresentation;
    QWidget *representation = doSpecialRepresentation(hexEditor, _keepSpecialRepresentation);
    if (_keepSpecialRepresentation)
        specialRepresentation = representation;
    return representation;
}

bool Container::keepSpecialRepresentation()
{
    return _keepSpecialRepresentation;
}

/* For expandable containers, this method will generate the child containers when called for the
 * first time */
std::vector<Container *> &Container::getInnerContainers()
{
    return innerContainers;
}

Container::~Container()
{
    if (_keepSpecialRepresentation &&
            /* the default Container::doSpecialRepresentation() returns a must-keep nullptr */
            specialRepresentation != nullptr)
        delete specialRepresentation;

    for (unsigned int i = 0; i < parents.size(); ++i)
    {
        std::vector<Container *> &siblings = parents[i]->getInnerContainers();
        siblings.erase(std::remove(siblings.begin(), siblings.end(), this),
                       siblings.end());
    }

    std::queue<Container *> toDelete;
    toDelete.push(this);
    while (!toDelete.empty())
    {
        Container *first = toDelete.front();
        toDelete.pop();
        std::vector<Container *> &successors = first->getInnerContainers();
        for (unsigned int i = 0; i < successors.size(); ++i)
        {
            std::vector<Container *> &childParents = successors[i]->getParents();
            childParents.erase(std::remove(childParents.begin(), childParents.end(), first),
                               childParents.end());
            if (childParents.size() == 0)
                toDelete.push(successors[i]);
        }
        if (first != this)
            delete first;
    }
}

bool Container::isValidInterval(std::pair<int, int> &interval)
{
    return interval.first != NO_INTERVAL;
}

void Container::invalidateInterval(std::pair<int, int> &interval)
{
    interval.first = NO_INTERVAL;
}

bool Container::addInnerContainer(Container *container)
{
    return addInnerContainer(container, innerContainers.size());
}

bool Container::addInnerContainer(Container *container, size_t position)
{
    if (std::find(innerContainers.begin(), innerContainers.end(), container) !=
        innerContainers.end())
        return false;
    innerContainers.insert(innerContainers.begin() + position, container);
    container->getParents().push_back(this);
    return true;
}

/**
 * Override this method to draw a special representation of the container in the right pane.
 *
 * @param keepAfterNodeDeselection: Set to true if you need to keep state across container selection
 *     changes; the hierarchicalViewer will only call the method once for this container and will
 *     use the received QWidget * at further selections. If you don't need to keep state, set to
 *     false to optimize memory usage.
 */
QWidget *Container::doSpecialRepresentation(QHexEdit *hexEditor, bool &keepAfterNodeDeselection)
{
    keepAfterNodeDeselection = true;
    return nullptr;
}
