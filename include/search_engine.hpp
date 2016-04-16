#ifndef SEARCH_ENGINE_HPP_
#define SEARCH_ENGINE_HPP_
#include <string>

class SearchEngine
{
public:
    SearchEngine();

    int getOffset(std::string &searchInput);

    virtual ~SearchEngine();
};

#endif

