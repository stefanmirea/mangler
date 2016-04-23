#ifndef ASMVIEWER_HPP
#define ASMVIEWER_HPP

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>

class ASMViewer : public QTreeView
{
public:
    ASMViewer(QWidget *parent = 0);
private:
    QStandardItemModel *model;
};

#endif // ASMVIEWER_HPP
