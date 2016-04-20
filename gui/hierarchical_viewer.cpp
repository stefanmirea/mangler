#include "hierarchical_viewer.hpp"

HierarchicalViewer::HierarchicalViewer(QWidget *parent) : QTreeWidget(parent)
{
    /* Placeholders for testing purposes */
    setColumnCount(1);
    setHeaderLabel("Executable file");
    QTreeWidgetItem *filename = addRoot(QString("hacker.out"));
    QTreeWidgetItem *elf_header = addChild(filename, QString("ELF Header"));
    QTreeWidgetItem *pht = addChild(filename, QString("Program Header Table"));
    QTreeWidgetItem *sht = addChild(filename, QString("Section Header Table"));
    addChild(pht, QString("--------NoThIng here"));
    addChild(sht, QString("--------NoThIng here"));

    addChild(elf_header, QString("e_ident"));
    addChild(elf_header, QString("e_type"));
    addChild(elf_header, QString("e_machine"));
    addChild(elf_header, QString("e_e_version"));
    addChild(elf_header, QString("e_entry"));
}

QTreeWidgetItem *HierarchicalViewer::addRoot(QString name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(this);
    item->setText(0, name);
    addTopLevelItem(item);
    return item;
}

QTreeWidgetItem *HierarchicalViewer::addChild(QTreeWidgetItem *parent, QString name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    parent->addChild(item);
    return item;
}
