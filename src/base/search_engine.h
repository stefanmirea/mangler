#ifndef SEARCH_ENGINE_H_
#define SEARCH_ENGINE_H_
#include <string>

class SearchEngine
{
public:
    SearchEngine();

    int getOffset(std::string& searchInput);

    virtual ~SearchEngine();
};

#endif
