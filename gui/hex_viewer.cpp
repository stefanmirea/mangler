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

HexViewer::HexViewer(QByteArray &hexdump, HierarchicalViewer *hierarchicalViewer, QWidget *parent) :
    QAbstractScrollArea(parent), hexdump(hexdump), hierarchicalViewer(hierarchicalViewer)
{
    viewport()->setContentsMargins(QMargins());
}

void HexViewer::paintEvent(QPaintEvent *)
{
    QPainter painter(viewport());
    painter.setPen(Qt::black);

    /* Set the font to monospace */
    QFont current_monospace("Monospace");
    QFontMetrics font_metrics(current_monospace);
    font_width = font_metrics.width('W');
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

    painter.drawText(viewport()->rect(), Qt::AlignLeft, text);
}
