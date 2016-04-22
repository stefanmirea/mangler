#ifndef ASMVIEWER_HPP
#define ASMVIEWER_HPP

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>

class ASMViewer : public QTableWidget
{
public:
    ASMViewer(int rows, int columns, QWidget *parent = 0);
};

#endif // ASMVIEWER_HPP
