#include "search_bar.hpp"
#include <QHBoxLayout>

SearchBar::SearchBar(QWidget *parent) : QWidget(parent)
{
    search = new QLabel(QString("Search:"), this);
    text = new QLineEdit(this);
    radiobox = new QGroupBox(this);
    hex = new QRadioButton(QString("Hex"), this);
    dec = new QRadioButton(QString("Dec"), this);
    string = new QRadioButton(QString("String"), this);
    next = new QPushButton();
    previous = new QPushButton();

    next->setIcon(QIcon::fromTheme("go-next", QIcon(":/icons/next.png")));
    previous->setIcon(QIcon::fromTheme("go-previous", QIcon(":/icons/previous.png")));

    radiobox->setStyleSheet("border:0;");

    QHBoxLayout *radio = new QHBoxLayout;
    radio->setContentsMargins(QMargins());
    radio->addWidget(hex);
    radio->addWidget(dec);
    radio->addWidget(string);

    radiobox->setLayout(radio);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setContentsMargins(QMargins());
    hbox->addWidget(search);
    hbox->addWidget(text);
    hbox->addWidget(radiobox);
    hbox->addWidget(previous);
    hbox->addWidget(next);

    setLayout(hbox);
    setMaximumHeight(80);
}

