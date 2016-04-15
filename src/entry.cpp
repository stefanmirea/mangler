#include "entry.h"

Entry::Entry(FileUnit *file, bool expandable)
    : file(file), expandable(expandable)
{
    invalidateInterval(interval);
}

Entry::Entry(FileUnit *file, bool expandable, std::pair<int, int> &interval)
    : file(file), expandable(expandable), interval(interval) {}

FileUnit *Entry::getFile()
{
    return file;
}

std::vector<Entry *> &Entry::getParents()
{
    return parents;
}

bool Entry::isExpandable()
{
    return expandable;
}

std::string &Entry::getName()
{
    return name;
}

void Entry::setName(std::string &name)
{
    this->name = name;
}

std::pair<int, int> &Entry::getInterval()
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

/* For expandable entries, this method will generate the child entries when
 * called for the first time */
std::vector<Entry *> &Entry::getInnerEntries()
{
    return innerEntries;
}

bool Entry::doSpecialRepresentation()
{
    return false;
}

Entry::~Entry()
{
    for (unsigned int i = 0; i < parents.size(); ++i)
    {
        std::vector<Entry *> &siblings = parents[i]->getInnerEntries();
        siblings.erase(std::remove(siblings.begin(), siblings.end(), this),
                       siblings.end());
    }

    std::queue<Entry *> toDelete;
    toDelete.push(this);
    while (!toDelete.empty())
    {
        Entry *first = toDelete.front();
        toDelete.pop();
        std::vector<Entry *> &successors = first->getInnerEntries();
        for (unsigned int i = 0; i < successors.size(); ++i)
        {
            std::vector<Entry *> &childParents = successors[i]->getParents();
            childParents.erase(std::remove(childParents.begin(), childParents.end(), first),
                               childParents.end());
            if (childParents.size() == 0)
                toDelete.push(successors[i]);
        }
        delete first;
    }
}

bool Entry::isValidInterval(std::pair<int, int> &interval)
{
    return interval.first != NO_INTERVAL;
}

void Entry::invalidateInterval(std::pair<int, int> &interval)
{
    interval.first = NO_INTERVAL;
}

bool Entry::addInnerEntry(Entry *entry)
{
    return addInnerEntry(entry, innerEntries.size());
}

bool Entry::addInnerEntry(Entry *entry, size_t position)
{
    if (std::find(innerEntries.begin(), innerEntries.end(), entry) !=
        innerEntries.end())
        return false;
    innerEntries.insert(innerEntries.begin() + position, entry);
    entry->getParents().push_back(this);
    return true;
}
