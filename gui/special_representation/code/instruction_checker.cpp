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

#include "instruction_checker.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>

InstructionChecker::InstructionChecker(QHexEdit *hexEditor, ASMViewer *asmViewer,
    std::string &defaultMachineCode, QWidget *parent) : QDialog(parent), hexEditor(hexEditor),
    asmViewer(asmViewer)
{
    setWindowTitle("Confirmation required");

    QString labelContent;
    if (defaultMachineCode != "")
        labelContent = "The support for entering instructions in assembly language is currently "
            "experimental. Problems are usually caused by the instruction containing labels or "
            "symbol names.\nPlease ensure that the generated machine code below is correct before "
            "proceeding.";
    else
        labelContent = "The instruction you entered could not be assembled. Please enter the "
            "machine code manually in hexadecimal.";
    QLabel *label = new QLabel(labelContent, this);
    label->setWordWrap(true);

    input = new QLineEdit(QString(defaultMachineCode.c_str()), this);

    int mLeft, mTop, mRight, mBottom;
    QWidget *middle = new QWidget(this);
    QHBoxLayout *middleLayout = new QHBoxLayout;
    middleLayout->addWidget(new QLabel("Machine code: ", this));
    middleLayout->addWidget(input);
    middleLayout->getContentsMargins(&mLeft, &mTop, &mRight, &mBottom);
    middleLayout->setContentsMargins(mLeft, 0, mRight, 0);
    middleLayout->setAlignment(Qt::AlignHCenter);
    middle->setLayout(middleLayout);

    QPushButton *buttonOK = new QPushButton("OK", this);
    buttonOK->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPushButton *buttonCancel = new QPushButton("Cancel", this);
    buttonCancel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QWidget *bottom = new QWidget(this);
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(buttonOK);
    bottomLayout->addWidget(buttonCancel);
    bottomLayout->getContentsMargins(&mLeft, &mTop, &mRight, &mBottom);
    bottomLayout->setContentsMargins(mLeft, 0, mRight, 0);
    bottomLayout->setAlignment(Qt::AlignHCenter);
    bottom->setLayout(bottomLayout);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(middle);
    layout->addWidget(bottom);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

    connect(buttonOK, SIGNAL(clicked()), this, SLOT(ok()));
    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void InstructionChecker::getOverlayInfo(int &fullyCovered, int &rest)
{
    fullyCovered = this->fullyCovered;
    rest = this->rest;
}

void InstructionChecker::getMachineCode(std::string &machineCode)
{
    machineCode = this->machineCode;
}

void InstructionChecker::ok()
{
    QString inputText = input->text();

    QModelIndexList list = asmViewer->selectionModel()->selectedIndexes();
    unsigned int instrSize = (list[1].data().toString().size() + 1) / 3;

    QRegularExpression blank("^\\s*$", QRegularExpression::CaseInsensitiveOption);
    if (blank.match(inputText).hasMatch())
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation required",
            "You left the \"Machine code\" field blank. Do you want to delete the currently "
            "selected instruction? Its content will be replaced with NOP instructions.",
            QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No)
            return;
        fullyCovered = 0;
        rest = instrSize;
        machineCode = "";
        accept();
        return;
    }

    QRegularExpression hexValue("^[0-9A-F ]*$",
                                QRegularExpression::CaseInsensitiveOption);
    if (!hexValue.match(inputText).hasMatch())
    {
        QMessageBox::critical(this, QString("Error"), QString("\"%1\" is not a valid hexadecimal "
            "value.").arg(inputText));
        return;
    }

    QByteArray ba = QByteArray::fromHex(inputText.toLatin1());
    machineCode = std::string(ba.data(), ba.size());
    int selectedRow = list[0].row();

    if (machineCode.size() < instrSize)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation required",
            QString("The instruction provided is shorter than the instruction to be replaced. "
                    "The last %1 byte(s) of the currently selected instruction will be "
                    "overwritten with NOP instructions.\nDo you want to proceed?")
                    .arg(instrSize - machineCode.size()),
            QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No)
            return;
        fullyCovered = 0;
        rest = instrSize - machineCode.size();
    }
    else if (machineCode.size() > instrSize)
    {
        int row = selectedRow;
        int bytesLeft = machineCode.size();
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
                "overwritten: its last %3 byte(s) will be replaced with NOP instructions. ")
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
    accept();
}
