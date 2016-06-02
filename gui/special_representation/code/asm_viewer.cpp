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

#include "asm_viewer.hpp"

ASMViewer::ASMViewer(CodeContainer *container, QWidget *parent) :
    QTreeView(parent), container(container)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setItemsExpandable(false);
    setRootIsDecorated(false);
    setUniformRowHeights(true);
    setFont(QFont("Monospace", 10));

    model = new QStandardItemModel();
    model->setColumnCount(4);

    QStringList headers;
    headers << "Address" << "Machine code" << "Opcode" << "Arguments";
    model->setHorizontalHeaderLabels(headers);

    setModel(model);
    for (unsigned int column = 0; column < 4; ++column)
        resizeColumnToContents(column);

    std::vector<std::pair<unsigned long long, std::string>> content;
    container->getContent(content);

    QList<QStandardItem *> items;
    for (unsigned int i = 0; i < content.size(); ++i)
    {
        items.clear();
        items.append(new QStandardItem(QString::number(content[i].first, 16)));
        items.append(new QStandardItem(bufferToHex(content[i].second)));
        std::string opcode, arguments;
        splitInstruction(content[i].second, opcode, arguments);
        items.append(new QStandardItem(QString(opcode.c_str())));
        items.append(new QStandardItem(QString(arguments.c_str())));
        model->appendRow(items);
    }
}

QStandardItemModel *ASMViewer::getModel()
{
    return model;
}

QString ASMViewer::bufferToHex(const std::string &buffer)
{
    QString ret;
    for (unsigned int byte = 0; byte < buffer.size(); ++byte)
    {
        char c = buffer[byte];
        ret += QString::number((c & 0xF0) >> 4, 16);
        ret += QString::number(c & 0xF, 16);
        if (byte != buffer.size() - 1)
            ret += ' ';
    }
    return ret;
}

void ASMViewer::splitInstruction(const std::string &binary, std::string &opcode, std::string &arguments)
{
    std::string instruction = FileAssembly::disassembleCode(binary);
    size_t spacePos = instruction.find(' ');
    if (spacePos == std::string::npos)
    {
        /* For example "nop" */
        opcode = instruction;
        arguments = "";
    }
    else
    {
        opcode = instruction.substr(0, spacePos);
        arguments = instruction.substr(spacePos + 1);
    }
}
