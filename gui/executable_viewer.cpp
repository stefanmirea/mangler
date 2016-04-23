#include "executable_viewer.hpp"
#include "QDesktopWidget"
#include "QApplication"

ExecutableViewer::ExecutableViewer(QString &filename, QWidget *parent) : QWidget(parent)
{
    setWindowTitle(filename);

    QWidget *left = new QWidget(this);
    QWidget *center = new QWidget(this);
    QWidget *right = new QWidget(this);

    QSplitter *split = new QSplitter(this);

    /* Left panel - hierarchy */
    QHBoxLayout *hv = new QHBoxLayout;
    hv->setContentsMargins(QMargins());
    hierarchicalViewer = new HierarchicalViewer(this);
    hv->addWidget(hierarchicalViewer);
    left->setLayout(hv);

    /* Center hex viewer and search bar */
    hexViewer = new HexViewer(hierarchicalViewer, this);
    searchBar = new SearchBar();
    QVBoxLayout *hexaLayout = new QVBoxLayout;
    hexaLayout->setContentsMargins(QMargins());
    hexaLayout->addWidget(hexViewer);
    hexaLayout->addWidget(searchBar);
    center->setLayout(hexaLayout);

    /* Right extra component */
    modifyBar = new ModifyASMBar();
    asmView = new ASMViewer(this);
    QVBoxLayout *extraLayout = new QVBoxLayout;
    extraLayout->setContentsMargins(QMargins());
    extraLayout->addWidget(asmView);
    extraLayout->addWidget(modifyBar);
    right->setLayout(extraLayout);

    /* Split the three components */
    split->addWidget(left);
    split->addWidget(center);
    split->addWidget(right);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(QMargins());
    layout->addWidget(split);

    setLayout(layout);
}

