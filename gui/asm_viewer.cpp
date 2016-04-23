#include "asm_viewer.hpp"

ASMViewer::ASMViewer(QWidget *parent) : QTreeView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setItemsExpandable(false);
    setRootIsDecorated(false);
    setUniformRowHeights(true);

    model = new QStandardItemModel();
    model->setColumnCount(4);

    QStringList headers;
    headers << "Address" << "Machine code" << "Opcode" << "Arguments";
    model->setHorizontalHeaderLabels(headers);

    setModel(model);
    for (unsigned int column = 0; column < 4; ++column)
        resizeColumnToContents(column);

    QList<QStandardItem *> items;
    items.append(new QStandardItem(QString("406637")));
    items.append(new QStandardItem(QString("89 85 24 ff ff ff")));
    items.append(new QStandardItem(QString("mov")));
    items.append(new QStandardItem(QString("DWORD PTR [rbp-0xdc],eax")));
    model->appendRow(items);

    items.clear();
    items.append(new QStandardItem(QString("40663d")));
    items.append(new QStandardItem(QString("8b 85 24 ff ff ff")));
    items.append(new QStandardItem(QString("mov")));
    items.append(new QStandardItem(QString("eax,DWORD PTR [rbp-0xdc]")));
    model->appendRow(items);
}

