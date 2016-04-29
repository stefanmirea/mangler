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

#include "modify_asmbar.hpp"
#include <QHBoxLayout>
#include <iostream>
#include <QDebug>

ModifyASMBar::ModifyASMBar(ASMViewer *asmViewer, QWidget *parent) :
    QWidget(parent), asmViewer(asmViewer)
{
    modify = new QLabel(QString("Modify:"), this);
    text = new QLineEdit(this);
    ok = new QPushButton(QString("OK"), this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(QMargins());
    layout->addWidget(modify);
    layout->addWidget(text);
    layout->addWidget(ok);
    setLayout(layout);
    setMaximumHeight(80);

    connect(ok, SIGNAL(clicked()), this, SLOT(editInstruction()));
}

bool ModifyASMBar::editInstruction()
{
    std::cerr << "OK!\n";
    QModelIndexList list = asmViewer->selectionModel()->selectedIndexes();

    QString address = list[0].data().toString();
    QString machineCode = list[0].data().toString();
    QString opCode = list[0].data().toString();
    QString args = list[0].data().toString();



    std::cerr << list.size() << "\n";
    std::cerr << address.toStdString();
}

