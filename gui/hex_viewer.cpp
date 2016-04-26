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

#include "hex_viewer.hpp"
#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>

HexViewer::HexViewer(QByteArray &hexdump, int address_size,
                     HierarchicalViewer *hierarchicalViewer,
                     QWidget *parent) :
    QAbstractScrollArea(parent), hexdump(hexdump), address_size(address_size), hierarchicalViewer(hierarchicalViewer)
{
    setFont(QFont("Monospace"));
    word_size = 2;
    row_width = 16;
    viewport()->setContentsMargins(QMargins());
}

void HexViewer::repaint()
{
    viewport()->repaint();
}

void HexViewer::paintEvent(QPaintEvent *)
{
    QPainter painter(viewport());
    painter.setPen(Qt::black);

    /* Set the font to monospace */
    QFont current_monospace = font();//("Monospace");
    //current_monospace.setStyleHint(QFont::Monospace);
    QFontMetrics font_metrics(current_monospace);
    font_width = font_metrics.width('i');
    font_height = font_metrics.height();

    std::cerr << "W: " << font_width << " H: " << font_height << std::endl;

    painter.setFont(current_monospace);

    QString text("00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ...D..:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ...X..:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ...C..:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ...V..:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ... ..:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ... ..:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ... ..:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ... ..:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ... ..:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ... ..:...B.....\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ... ..:....CA...\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ... ..:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ... ..:.....B...\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ......:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ......:..CXD....\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ......:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ... ..:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ... ..:.........\n"
                 "00000000  fa 08 ff 32 f1 a0 3a 84  b2 18 ac aa 01 a0 3a 84  ... ..:.........\n");

    font_width = 7; /* W = 10 */
    font_height = 14; /* H = 19 */

    total_space = text.size() - 18 + 18 * 20;

    std::cerr << "X: " << selected_x << " Y: " << selected_y << " xn:"<<selected_x/font_width<<" " << " yn: " << selected_y/font_height << std::endl;

    /* Highlighter */
    painter.fillRect(
                        QRectF(
                            (selected_x / font_width) * font_width,
                            (selected_y / font_height) * font_height,
                            1 * font_width,
                            1 * font_height),
                        palette().highlight()
                        );
    painter.drawText(viewport()->rect(), Qt::AlignLeft, text);
}

void HexViewer::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
    {
        selected_x = event->x();
        selected_y = event->y();
        viewport()->update();
    }
}
