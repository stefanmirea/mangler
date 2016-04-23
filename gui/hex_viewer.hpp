#ifndef HEXVIEWER_HPP
#define HEXVIEWER_HPP

#include <QWidget>
#include <QAbstractScrollArea>
#include "hierarchical_viewer.hpp"

class HexViewer : public QAbstractScrollArea
{
    Q_OBJECT
public:
    explicit HexViewer(HierarchicalViewer *hierarchicalViewer, QWidget *parent = 0);

signals:

public slots:
private:
    HierarchicalViewer *hierarchicalViewer;
};

#endif // HEXVIEWER_HPP
