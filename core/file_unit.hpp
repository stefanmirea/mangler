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

#ifndef FILE_UNIT_HPP_
#define FILE_UNIT_HPP_

#include "container.hpp"
#include <string>
#include <vector>

class Container;

/**
 * Manages information associated with an open file. Extend this class in order to implement support
 * for new executable file formats.
 */
class FileUnit
{
public:
    FileUnit(const std::string &filename);
    std::string &getName();
    virtual const std::string &getFormatName() = 0;
    std::vector<Container *> &getTopLevelContainers();

    virtual bool getOpenStatus() = 0;
    virtual bool save(std::string &filename) = 0;
    virtual void modifyHex(size_t offset, std::string &newContent) = 0;
    virtual ~FileUnit();
    virtual bool loadFile(const std::string &filename) = 0; /* Creates the top-level containers. */

private:
    std::string filename;
    std::vector<Container *> topLevelContainers;
};

#endif // FILE_UNIT_HPP_
