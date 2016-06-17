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
#include "instruction_checker.hpp"
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
    handleSelection = true;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(QMargins());
    layout->addWidget(modify);
    layout->addWidget(text);
    layout->addWidget(ok);
    setLayout(layout);
    setMaximumHeight(80);

    connect(ok, SIGNAL(clicked()), this, SLOT(editInstruction()));
}

QString ModifyASMBar::getText()
{
    return text->text();
}

void ModifyASMBar::setText(QString &text)
{
    this->text->setText(text);
}

void ModifyASMBar::setHandleSelection(bool handleSelection)
{
    this->handleSelection = handleSelection;
}

void ModifyASMBar::editInstruction()
{
    QModelIndexList list = asmViewer->selectionModel()->selectedIndexes();
    QString inputInstruction = text->text();

    if (!list.size())
    {
        QMessageBox::critical(this, QString("Error"),
                              QString("You must select the instruction to be replaced."));
        return;
    }

    std::string binaryCode;
    asmInstr instruction;
    int fullyCovered;
    int rest;
    QString machineCode = list[1].data().toString();
    unsigned int instrSize = (machineCode.size() + 1) / 3;
    int selectedRow = list[0].row();
    bool ok;
    unsigned long long initialAddress = list[0].data().toString().toULongLong(&ok, 16);

    QRegularExpression blank("^\\s*$", QRegularExpression::CaseInsensitiveOption);
    if (blank.match(inputInstruction).hasMatch())
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
        FileAssembly::assembleInstruction(inputInstruction.toStdString(), instruction);
        InstructionChecker *instructionChecker = new InstructionChecker(hexEditor, asmViewer,
            instruction.assembled, this);
        int result = instructionChecker->exec();
        if (result == QDialog::Rejected)
        {
            delete instructionChecker;
            return;
        }

        instructionChecker->getOverlayInfo(fullyCovered, rest);
        instructionChecker->getMachineCode(binaryCode);
        delete instructionChecker;

        /* binaryCode keeps the new instruction in binary format.
         * instruction must be filled accoringly. */
        if (binaryCode != "")
        {
            QByteArray beforeEdit = QByteArray::fromHex(instruction.assembled.c_str());

            /* if assembleInstruction did not work or the user has modified the machine code */
            if (instruction.assembled == ""
                || std::string(beforeEdit.data(), beforeEdit.size()) != binaryCode)
            {
                bool fileAccess = true;
                QString tempFileName((container->getFile()->getName() + "_asmtmp").c_str());
                if (!hexEditor->saveFile(tempFileName))
                    fileAccess = false;
                else
                {
                    QFile tempFile(tempFileName);
                    if (!tempFile.open(QFile::ReadWrite))
                    {
                        fileAccess = false;
                        QFile::remove(tempFileName);
                    }
                    else
                    {
                        tempFile.seek(container->addressToOffset(initialAddress));
                        tempFile.write(binaryCode.data(), binaryCode.size());
                        char fill = 0x90;
                        for (int i = 0; i < rest; ++i)
                            tempFile.write(&fill, 1);
                        tempFile.close();
                    }
                }
                if (!fileAccess)
                {
                    QMessageBox::critical(this, QString("Error"),
                        QString("Cannot access temporary file. Aborting operation."));
                    return;
                }

                std::map<std::string, unsigned long long> labels;
                std::vector<asmInstr> instructions;
                FileAssembly::disassembleSection(tempFileName.toStdString(),
                                                 container->getSectionName(), labels, instructions);
                QFile::remove(tempFileName);
                bool found = false;
                for (unsigned int i = 0; i < instructions.size(); ++i)
                    if (instructions[i].address == initialAddress)
                    {
                        found = true;
                        instruction = instructions[i];
                        if ((instruction.assembled.size() + 1) / 3 != binaryCode.size())
                        {
                            QMessageBox::critical(this, QString("Error"),
                                QString("You are only allowed to enter a single instruction at a "
                                    "time."));
                            return;
                        }
                        break;
                    }
                if (!found)
                {
                    QMessageBox::critical(this, QString("Error"),
                        QString("An error occurred. Refresh your view and try again."));
                    return;
                }
            }
            /* else, use the instruction received from FileAssembly::assembleInstruction */
        }
        else
            instruction.assembled = "";
    }

    unsigned long long address = initialAddress;
    int row = selectedRow;

    if (binaryCode != "")
    {
        QList<QStandardItem *> newInstructionEntry {
            new QStandardItem(QString::number(address, 16)),
            new QStandardItem(QString(instruction.assembled.c_str())),
            new QStandardItem(QString(instruction.opcode.c_str())),
            new QStandardItem(QString(instruction.args.c_str()))
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

    /* The input instruction will also be updated in the elfio backend
     * and hexedit */
    container->overwrite(initialAddress, codeContainerUpdate);

    QByteArray byteArray(codeContainerUpdate.data(), codeContainerUpdate.size());
    hexEditor->replace(container->addressToOffset(initialAddress), codeContainerUpdate.size(),
                       byteArray);
}

void ModifyASMBar::changeViewerSelection(const QItemSelection &selected,
                                         const QItemSelection &deselected)
{
    if (!handleSelection)
        return;

    QModelIndexList list = selected.indexes();
    if (list.empty())
        return;

    text->setText(list[2].data().toString() + ' ' + list[3].data().toString());

    bool ok;
    unsigned long long address = list[0].data().toString().toULongLong(&ok, 16);
    hexEditor->selectData(container->addressToOffset(address),
                          (list[1].data().toString().size() + 1) / 3);
}
