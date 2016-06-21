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

#ifndef INSTRUCTION_CHECKER_HPP_
#define INSTRUCTION_CHECKER_HPP_

#include "qhexedit.hpp"
#include "asm_viewer.hpp"
#include <QDialog>
#include <QLineEdit>

class InstructionChecker : public QDialog
{
    Q_OBJECT
public:
    InstructionChecker(QHexEdit *hexEditor, ASMViewer *asmViewer, std::string &defaultMachineCode,
        QWidget *parent = 0);
    void getOverlayInfo(int &fullyCovered, int &rest);
    void getMachineCode(std::string &machineCode);

public slots:
    void ok();

private:
    QHexEdit *hexEditor;
    ASMViewer *asmViewer;
    QLineEdit *input;

    int fullyCovered, rest;
    std::string machineCode;
};

#endif // INSTRUCTION_CHECKER_HPP_
