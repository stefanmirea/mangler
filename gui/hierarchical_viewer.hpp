#ifndef HIERACHICALVIEWER_HPP
#define HIERACHICALVIEWER_HPP

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QSplitter>

#include "hierarchy_node.hpp"

class HierarchicalViewer : public QTreeWidget
{
    Q_OBJECT
public:
    explicit HierarchicalViewer(QSplitter *split, QWidget *defaultSpecialRep, QWidget *parent = 0);
    HierarchyNode *addRoot(Container *container);
    HierarchyNode *addChild(HierarchyNode *parent, Container *container);
signals:

public slots:
    void expand(QTreeWidgetItem *item);
    void change(QTreeWidgetItem *current, QTreeWidgetItem *previous);
private:
    QWidget *defaultSpecialRep;
    QSplitter *split;
};

#endif // HIERACHICALVIEWER_HPP
