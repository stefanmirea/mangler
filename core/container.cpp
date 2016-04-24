#include "container.hpp"

Container::Container(FileUnit *file, bool expandable)
    : file(file), expandable(expandable)
{
    invalidateInterval(interval);
}

Container::Container(FileUnit *file, bool expandable, const std::pair<int, int> &interval)
    : file(file), expandable(expandable), interval(interval) {}

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
            assert(parentInterval.first <= interval.first &&
                   interval.second <= parentInterval.second);
        }
#endif
    return interval;
}

/* For expandable containers, this method will generate the child containers
 * when called for the first time */
std::vector<Container *> &Container::getInnerContainers()
{
    return innerContainers;
}

bool Container::doSpecialRepresentation()
{
    return false;
}

Container::~Container()
{
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
