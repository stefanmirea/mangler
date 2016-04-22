#include "asm_viewer.hpp"

ASMViewer::ASMViewer(int rows, int columns, QWidget *parent) : QTableWidget(rows, columns, parent)
{
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setShowGrid(false);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

