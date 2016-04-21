#include "hierarchical_viewer.hpp"

HierarchicalViewer::HierarchicalViewer(QWidget *parent) : QTreeWidget(parent)
{
    /* Placeholders for testing purposes */
    setColumnCount(1);
    setHeaderLabel("Executable file");
    QTreeWidgetItem *filename = addRoot("hacker.out");
    QTreeWidgetItem *elf_header = addChild(filename, "ELF Header");
    QTreeWidgetItem *pht = addChild(filename, "Program Header Table");
    QTreeWidgetItem *sht = addChild(filename, "Section Header Table");
    addChild(pht, "--------NoThIng here");
    addChild(sht, "--------NoThIng here");

    addChild(elf_header, "e_ident");
    addChild(elf_header, "e_type");
    addChild(elf_header, "e_machine");
    addChild(elf_header, "e_e_version");
    addChild(elf_header, "e_entry");
}

QTreeWidgetItem *HierarchicalViewer::addRoot(const char *name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(this);
    item->setText(0, QString(name));
    addTopLevelItem(item);
    return item;
}

QTreeWidgetItem *HierarchicalViewer::addChild(QTreeWidgetItem *parent, const char *name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, QString(name));
    parent->addChild(item);
    return item;
}
