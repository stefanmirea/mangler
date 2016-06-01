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
    QString inputInstruction = text->text();

    if(list.size() && inputInstruction.isEmpty() == false)
    {
        QString address = list[0].data().toString();
        QString machineCode = list[1].data().toString();
        QString opCode = list[2].data().toString();
        QString args = list[3].data().toString();

        int selectedRow = list[0].row();
        int instrSize = (machineCode.size() + 1) / 3;

        /* TODO: The input instruction will also be updated in the elfio backend
         * and hexedit */

        /* TODO: The instruction will be disassembled and the opCode and args
         * will be updated */

        /* TODO: deallocate memory for old QStandardItem */

        if(inputInstruction.contains("90")) /* Testing purposes, not a rigorous check */
        {
            QString nops;
            for(unsigned int i = 0; i < instrSize; i++)
                nops.append("90 ");
            asmViewer->editModel(selectedRow, 1, new QStandardItem(nops));

            asmViewer->editModel(selectedRow, 2,
                            new QStandardItem(QString::fromStdString(FileAssembly::Disassembler::
                            disassembleCode(nullptr, 1))));

            asmViewer->editModel(selectedRow, 3,
                            new QStandardItem(QString("")));
        }

        else
        {
            asmViewer->editModel(selectedRow, 1, new QStandardItem(inputInstruction));
            asmViewer->editModel(selectedRow, 2,
                            new QStandardItem(QString("xor")));

            asmViewer->editModel(selectedRow, 3,
                                    new QStandardItem(QString("eax, eax")));
        }

        std::cerr << list[0].row() << "\n";
        std::cerr << address.toStdString();
    }
}

