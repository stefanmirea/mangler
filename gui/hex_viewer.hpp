#ifndef HEXVIEWER_HPP
#define HEXVIEWER_HPP

#include <QWidget>
#include <QTableWidget>

class HexViewer : public QTableWidget
{
    Q_OBJECT
public:
    explicit HexViewer(int rows, int columns, QWidget * parent = 0);

signals:

public slots:
};

#endif // HEXVIEWER_HPP
