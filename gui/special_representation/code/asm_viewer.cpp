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

CodeContainer::ASMViewer::ASMViewer(QWidget *parent) : QTreeView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setItemsExpandable(false);
    setRootIsDecorated(false);
    setUniformRowHeights(true);

    model = new QStandardItemModel();
    model->setColumnCount(4);

    QStringList headers;
    headers << "Address" << "Machine code" << "Opcode" << "Arguments";
    model->setHorizontalHeaderLabels(headers);

    setModel(model);
    for (unsigned int column = 0; column < 4; ++column)
        resizeColumnToContents(column);

    QList<QStandardItem *> items;
    items.append(new QStandardItem(QString("406637")));
    items.append(new QStandardItem(QString("89 85 24 ff ff ff")));
    items.append(new QStandardItem(QString("mov")));
    items.append(new QStandardItem(QString("DWORD PTR [rbp-0xdc],eax")));
    model->appendRow(items);

    items.clear();
    items.append(new QStandardItem(QString("40663d")));
    items.append(new QStandardItem(QString("8b 85 24 ff ff ff")));
    items.append(new QStandardItem(QString("mov")));
    items.append(new QStandardItem(QString("eax,DWORD PTR [rbp-0xdc]")));
    model->appendRow(items);
}

