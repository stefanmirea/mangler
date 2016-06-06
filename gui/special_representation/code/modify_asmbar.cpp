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
#include "qhexedit.hpp"
#include <QMessageBox>
#include <QHBoxLayout>
#include <iostream>
#include <QDebug>

ModifyASMBar::ModifyASMBar(CodeContainer *container, ASMViewer *asmViewer, QHexEdit *hexEditor,
    QWidget *parent) : QWidget(parent), container(container), asmViewer(asmViewer),
                       hexEditor(hexEditor)
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

void ModifyASMBar::editInstruction()
{
    std::cerr << "OK!\n";
    QModelIndexList list = asmViewer->selectionModel()->selectedIndexes();
    QString inputInstruction = text->text();

    if (!list.size())
    {
        QMessageBox::critical(this, QString("Error"),
                              QString("You must select the instruction to be replaced."));
        return;
    }

    std::string binaryCode;
    int fullyCovered;
    int rest;
    QString machineCode = list[1].data().toString();
    unsigned int instrSize = (machineCode.size() + 1) / 3;
    int selectedRow = list[0].row();

    if (inputInstruction.isEmpty())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation required",
            "You left the \"Modify\" field blank. Do you want to delete the currently selected "
            "instruction? Its content will be replaced with NOP instructions.",
            QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No)
            return;
        fullyCovered = 0;
        rest = instrSize;
    }
    else
    {
        bool assembled;
        binaryCode = FileAssembly::assembleCode(inputInstruction.toStdString(), assembled);
        if (!assembled)
        {
            QMessageBox::critical(this, QString("Error"),
                QString("The instruction provided could not be assembled. "
                        "Please check your input and try again."));
            return;
        }

        if (binaryCode.size() < instrSize)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirmation required",
                QString("The instruction provided is shorter than the instruction to be replaced. "
                        "The last %1 byte(s) of the currently selected instruction will be "
                        "overwritten with NOP instructions.\nDo you want to proceed?")
                        .arg(instrSize - binaryCode.size()),
                QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::No)
                return;
            fullyCovered = 0;
            rest = instrSize - binaryCode.size();
        }
        else if (binaryCode.size() > instrSize)
        {
            int row = selectedRow;
            int bytesLeft = binaryCode.size();
            rest = 0;

            while (bytesLeft > 0 && row < asmViewer->getModel()->rowCount())
            {
                int currentSize = (asmViewer->getModel()->item(row, 1)->text().size() + 1) / 3;
                if (currentSize >= bytesLeft)
                    rest = currentSize - bytesLeft;
                bytesLeft -= currentSize;
                ++row;
            }

            if (bytesLeft > 0 && row == asmViewer->getModel()->rowCount())
            {
                QMessageBox::critical(this, QString("Error"),
                    QString("The new instruction cannot exceed the section limit."));
                return;
            }

            fullyCovered = row - selectedRow;
            if (rest)
                --fullyCovered;

            QString message = QString("The instruction provided is longer than the instruction to "
                "be replaced. %1 instruction(s) starting with the one you selected will be fully "
                "overwritten.").arg(fullyCovered);
            QString ord;
            if (fullyCovered + 1 == 2)
                ord = QString("nd");
            else if (fullyCovered + 1 == 3)
                ord = QString("rd");
            else
                ord = QString("th");
            if (rest)
                message += QString(" Additionally, the %1%2 instruction will be partially "
                    "overwritten: its last %3 bytes will be replaced with NOP instructions. ")
                    .arg(fullyCovered + 1).arg(ord).arg(rest);
            message += QString("\nDo you want to proceed?");

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirmation required", message,
                QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::No)
                return;
        }
        else
        {
            fullyCovered = 1;
            rest = 0;
        }
    }

    bool ok;
    unsigned long long initialAddress = list[0].data().toString().toULongLong(&ok, 16);
    unsigned long long address = initialAddress;
    int row = selectedRow;

    if (binaryCode != "")
    {
        std::string opcode;
        std::string arguments;
        std::string assembled;
        ASMViewer::splitInstruction(binaryCode, assembled, opcode, arguments);

        QList<QStandardItem *> newInstructionEntry {
            new QStandardItem(QString::number(address, 16)),
            new QStandardItem(QString(assembled.c_str())),
            new QStandardItem(QString(opcode.c_str())),
            new QStandardItem(QString(arguments.c_str()))
        };

        asmViewer->getModel()->insertRow(row, newInstructionEntry);
        address += binaryCode.size();
        ++row;
    }

    std::string codeContainerUpdate = binaryCode;
    for (int i = 0; i < rest; ++i)
    {
        QList<QStandardItem *> newInstructionEntry {
            new QStandardItem(QString::number(address, 16)),
            new QStandardItem(QString("90")),
            new QStandardItem(QString("nop")),
            new QStandardItem(QString(""))
        };
        codeContainerUpdate += (char)0x90;
        asmViewer->getModel()->insertRow(row, newInstructionEntry);
        ++address;
        ++row;
    }

    asmViewer->getModel()->removeRows(row, fullyCovered + (rest ? 1 : 0));

    /* TODO: The input instruction will also be updated in the elfio backend
     * and hexedit */
    container->overwrite(initialAddress, codeContainerUpdate);
}

void ModifyASMBar::changeViewerSelection(const QItemSelection &selected,
                                         const QItemSelection &deselected)
{
    QModelIndexList list = selected.indexes();
    text->setText(list[2].data().toString() + ' ' + list[3].data().toString());

    bool ok;
    unsigned long long address = list[0].data().toString().toULongLong(&ok, 16);
    hexEditor->selectData(container->addressToOffset(address), (list[1].data().toString().size() + 1) / 3);
}
