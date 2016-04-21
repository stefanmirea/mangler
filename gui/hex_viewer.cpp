#include "hex_viewer.hpp"
#include <QHeaderView>

HexViewer::HexViewer(int rows, int columns, QWidget *parent) :
    QTableWidget(rows, columns, parent)
{
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setShowGrid(false);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
