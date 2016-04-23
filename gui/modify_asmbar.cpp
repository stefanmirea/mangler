#include "modify_asmbar.hpp"
#include <QHBoxLayout>

ModifyASMBar::ModifyASMBar(QWidget *parent) : QWidget(parent)
{
    modify = new QLabel(QString("Modify:"), this);
    text = new QLineEdit(this);
    ok = new QPushButton(QString("OK"), this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(QMargins());
    layout->addWidget(modify);
    layout->addWidget(text);
    layout->addWidget(ok);
    setLayout(layout);
    setMaximumHeight(80);
}

