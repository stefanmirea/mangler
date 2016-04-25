/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Adrian Dobrică, Ștefan-Gabriel Mirea
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

#include "code_container.hpp"

CodeContainer::CodeContainer(FileUnit *file)
    : Container(file, false), injectionPossible(false) {}

CodeContainer::CodeContainer(FileUnit *file, const std::pair<int, int> &interval)
    : Container(file, false, interval), injectionPossible(false) {}

bool CodeContainer::canInject()
{
    return injectionPossible;
}

std::vector<Container *> &CodeContainer::getInnerContainers()
{
    return innerContainers;
}

/**
 * In order to keep this class generic among different executable file formats,
 * do not fill up this method. If you want to implement code injection for your
 * file format, create a new class derived from CodeContainer.
 */
void CodeContainer::injectCode(size_t offset, std::string &newContent) {}

CodeContainer::~CodeContainer() {}
