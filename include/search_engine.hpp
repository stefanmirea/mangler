#ifndef SEARCH_ENGINE_HPP_
#define SEARCH_ENGINE_HPP_

#include "file_unit.hpp"
#include <string>

enum Direction
{
    DIR_BACK = 0,
    DIR_FORWARD
};

class SearchEngine
{
public:
    SearchEngine();

    int getHexOffset(FileUnit &file, unsigned int start, Direction dir, std::string &searchInput);
    int getDecOffset(FileUnit &file, unsigned int start, Direction dir, int searchInput);
    int getStrOffset(FileUnit &file, unsigned int start, Direction dir, std::string &searchInput);

    virtual ~SearchEngine();
};

#endif

