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

#ifndef HEX_VIEWER_HPP_
#define HEX_VIEWER_HPP_

#include <QWidget>
#include <QAbstractScrollArea>
#include "hierarchical_viewer.hpp"

class HexViewer : public QAbstractScrollArea
{
    Q_OBJECT
public:
    explicit HexViewer(QByteArray &hexdump, int address_size,
                       HierarchicalViewer *hierarchicalViewer,
                       QWidget *parent = 0);

signals:

public slots:
private:
    HierarchicalViewer *hierarchicalViewer;
    void repaint();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);

    bool selection_exists;

    int font_width;
    int font_height;
    int total_space;
    QPair<int, int> selectedBounds;
    QByteArray hexdump;
    int selected_x;
    int selected_y;

    int address_size;
    int word_size;
    int row_width;
};

#endif // HEX_VIEWER_HPP_
