#include "util.hpp"
#include <sstream>
#include <iomanip>

std::string printHex(int value)
{
        std::string ret;
        std::stringstream ss;
        ss << std::hex << std::showbase << value;
        ret = ss.str();
        return ret;
}
