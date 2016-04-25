#include "executable_viewer.hpp"

#include <QVBoxLayout>
#include <QLabel>

QWidget *ExecutableViewer::createDefaultSpecialRep()
{
    QWidget *area = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout();
    QLabel *label = new QLabel(QString("No special representation available."));
    layout->addWidget(label);
    layout->setAlignment(label, Qt::AlignHCenter);
    area->setLayout(layout);

    return area;
}
