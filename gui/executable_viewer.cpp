#include "executable_viewer.hpp"
#include "QDesktopWidget"
#include "QApplication"

ExecutableViewer::ExecutableViewer(FileUnit *fileUnit, QWidget *parent) :
    QWidget(parent), fileUnit(fileUnit)
{
    setWindowModified(false);
    setWindowTitle(QString(fileUnit->getName().c_str()) + "[*]");

    QWidget *left = new QWidget(this);
    QWidget *center = new QWidget(this);

    split = new QSplitter(this);

    /* Right extra component */
    defaultSpecialRep = createDefaultSpecialRep();

    /* Left panel - hierarchy */
    QHBoxLayout *hv = new QHBoxLayout;
    hv->setContentsMargins(QMargins());
    hierarchicalViewer = new HierarchicalViewer(split, defaultSpecialRep, this);

    std::vector<Container *> rootContainers = fileUnit->getTopLevelContainers();
    for (unsigned int i = 0; i < rootContainers.size(); ++i)
        hierarchicalViewer->addRoot(rootContainers[i]);

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

    /* Split the three components */
    split->addWidget(left);
    split->addWidget(center);
    split->addWidget(defaultSpecialRep);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(QMargins());
    layout->addWidget(split);

    setLayout(layout);
}

FileUnit *ExecutableViewer::getFileUnit()
{
    return fileUnit;
}

ExecutableViewer::~ExecutableViewer()
{
    if (split->widget(2) != defaultSpecialRep)
    {
        delete defaultSpecialRep;

        QTreeWidgetItem *currentItem = hierarchicalViewer->currentItem();

        /* If the currently selected HierarchyNode wanted to keep its special representation after
         * being deselected, the QWidget will be deallocated in that node's destructor. */
        if (dynamic_cast<HierarchyNode *>(currentItem)->keepSpecialRepresentation())

        /* The widget must be disconnected from the splitter, otherwise the splitter will
         * try to deallocate it too. Setting the parent to null is safe as the splitter will get
         * notified about its child being reparented. */
            split->widget(2)->setParent(Q_NULLPTR);
    }
    /* else defaultSpecialRep will be deallocated automatically by the splitter destructor */
}
