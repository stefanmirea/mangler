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
