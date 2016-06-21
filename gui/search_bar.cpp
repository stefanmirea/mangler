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
#include <QMessageBox>
#include <iostream>
#include <algorithm>

SearchBar::SearchBar(QHexEdit *hexedit, QWidget *parent) :
    QWidget(parent), hexedit(hexedit)
{
    search = new QLabel(QString("Search:"), this);
    text = new QLineEdit(this);
    radiobox = new QGroupBox(this);
    hex = new QRadioButton(QString("Hex"), this);
    hex->setChecked(true);
    dec = new QRadioButton(QString("Dec"), this);
    string = new QRadioButton(QString("String"), this);
    direction = new QCheckBox("Backwards", this);

    next = new QPushButton();
    connect(next, SIGNAL (clicked()), this, SLOT (searchValue()));
    next->setIcon(QIcon::fromTheme("go-next", QIcon(":/icons/next.png")));

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
    hbox->addWidget(direction);
    hbox->addWidget(next);

    setLayout(hbox);
    setMaximumHeight(80);
}

void SearchBar::searchValue()
{
    if (!direction->isChecked())
    {
        findNext();
    }

    else
    {
        findPrev();
    }
}

QByteArray SearchBar::getInput()
{
    QByteArray input;
    if (text->text().isEmpty() == false)
    {
        if (hex->isChecked() == true)
        {
            QRegularExpression hexValue("^[0-9A-F]+$", QRegularExpression::CaseInsensitiveOption);
            if (!hexValue.match(text->text()).hasMatch())
                QMessageBox::critical(this, QString("Error"),
                                      QString("\"%1\" is not a valid hexadecimal value.")
                                      .arg(text->text()));
            else
            {
                input = QByteArray::fromHex(text->text().toLatin1());
            }
        }
        else if (dec->isChecked() == true)
        {
            bool ok;
            qulonglong value = text->text().toULongLong(&ok);
            if (!ok)
                QMessageBox::critical(this, QString("Error"),
                                      QString("\"%1\" is not a valid decimal value.")
                                      .arg(text->text()));
            else if (value == 0)
                input.fill(0, 1);
            else
            {
                int shift = CHAR_BIT * (sizeof(unsigned long long) - 1);
                unsigned long long mask = 0xFF << shift;
                bool null = true;
                while (mask)
                {
                    char byte = (char)((value & mask) >> shift);
                    if (byte != 0)
                        null = false;
                    if (!null)
                        input.append(byte);
                    mask >>= CHAR_BIT;
                    shift -= CHAR_BIT;
                }
            }
        }
        else if (string->isChecked() == true)
        {
            input = QByteArray(text->text().toUtf8());
        }
    }
    else
        QMessageBox::critical(this, QString("Error"), QString("Please enter a search query."));

    qDebug(text->text().toLatin1());
    return input;
}

void SearchBar::findNext()
{
    QByteArray searchInput = getInput();
    if (searchInput.length() == 0)
    {
        return;
    }

    qint64 start = (hexedit->cursorPosition() + 1) / 2;
    qint64 newPosition = -1;

    newPosition = hexedit->indexOf(searchInput, start);

    if (newPosition == -1)
        QMessageBox::information(this, QString("Information"),
        QString("Your search has reached the end of the file."));
}

void SearchBar::findPrev()
{
    QByteArray searchInput = getInput();
    if (searchInput.length() == 0)
    {
        return;
    }

    qint64 start = (hexedit->cursorPosition() - 1) / 2;
    qint64 newPosition = -1;

    newPosition = hexedit->lastIndexOf(searchInput, start);

    if (newPosition == -1)
        QMessageBox::information(this, QString("Information"),
        QString("Your search has reached the beginning of the file."));
}
