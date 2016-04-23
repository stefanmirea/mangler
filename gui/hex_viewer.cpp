#include "hex_viewer.hpp"
#include <QHeaderView>

HexViewer::HexViewer(HierarchicalViewer *hierarchicalViewer, QWidget *parent) :
    QAbstractScrollArea(parent), hierarchicalViewer(hierarchicalViewer) {}
