#include "search_bar.hpp"
#include <QHBoxLayout>

SearchBar::SearchBar(QWidget *parent) : QWidget(parent)
{
    search = new QLabel(QString("Search:"), this);
    text = new QTextEdit(this);
    radiobox = new QGroupBox(this);
    hex = new QRadioButton(QString("Hex"), this);
    dec = new QRadioButton(QString("Dec"), this);
    string = new QRadioButton(QString("String"), this);

    text->setMaximumHeight(40);

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

    setLayout(hbox);
    setMaximumHeight(80);
}

