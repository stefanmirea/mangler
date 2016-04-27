/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Ștefan-Gabriel Mirea, Adrian Dobrică
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "search_bar.hpp"
#include <QHBoxLayout>
#include <iostream>

SearchBar::SearchBar(QHexEdit *hexedit, QWidget *parent) :
    QWidget(parent), hexedit(hexedit)
{
    search = new QLabel(QString("Search:"), this);
    text = new QLineEdit(this);
    radiobox = new QGroupBox(this);
    hex = new QRadioButton(QString("Hex"), this);
    dec = new QRadioButton(QString("Dec"), this);
    string = new QRadioButton(QString("String"), this);

    next = new QPushButton();
    connect(next, SIGNAL (clicked()), this, SLOT (findNext()));

    previous = new QPushButton();
    connect(previous, SIGNAL (clicked()), this, SLOT (findPrev()));

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

QByteArray SearchBar::getInput()
{
    QByteArray input;
    if(text->text().isEmpty() == false)
    {
        if(hex->isChecked() == true)
        {
            input =  QByteArray::fromHex(text->text().toLatin1());
            std::cerr << "HEX\n";
        }

        else
        if(dec->isChecked() == true)
        {
            int value = text->text().toInt();
            input =  QByteArray::number(value);
            std::cerr << "DEC\n";
        }

        else
        if(string->isChecked() == true)
        {
            input = QByteArray(text->text().toUtf8());
            std::cerr << "STR\n";
        }
    }

    qDebug(text->text().toLatin1());
    return input;
}

int SearchBar::findNext()
{
    QByteArray searchInput = getInput();
    if(searchInput.length() == 0)
    {
        return -1;
    }

    qint64 start = hexedit->cursorPosition() / 2;
    qint64 newPosition = -1;

    newPosition = hexedit->indexOf(searchInput, start);
    std::cerr <<"New pos: " << newPosition;

    return newPosition;
}

int SearchBar::findPrev()
{
    return newPosition;
}
