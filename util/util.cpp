#include "util.hpp"
#include <sstream>
#include <iomanip>

std::string &printHex(int value)
{
        std::stringstream ss;
        ss << std::hex << std::showbase << value;
        return ss.str();
}
