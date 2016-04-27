/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Adrian Dobrică, Ștefan-Gabriel Mirea
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

#ifndef SEARCH_BAR_HPP_
#define SEARCH_BAR_HPP_

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QByteArray>
#include <qhexedit.hpp>

class SearchBar : public QWidget
{
    Q_OBJECT
public:
    explicit SearchBar(QHexEdit *hexedit, QWidget *parent = 0);

signals:

public slots:
    int findNext();
    int findPrev();
private:
    QByteArray getInput();

    enum search_type {HEX, DEC, STRING};
    QHexEdit *hexedit;
    QLabel *search;
    QLineEdit *text;
    QGroupBox *radiobox;
    QPushButton *next, *previous;
    QRadioButton *hex, *dec, *string;
};

#endif // SEARCH_BAR_HPP_
