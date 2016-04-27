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

#ifndef EXECUTABLE_VIEWER_HPP_
#define EXECUTABLE_VIEWER_HPP_

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QSplitter>
#include <QWidget>
#include <QVBoxLayout>
#include <QFile>
#include <QIODevice>

#include "hierarchical_viewer.hpp"
#include "qhexedit.hpp"
#include "search_bar.hpp"

#include "file_unit.hpp"

class ExecutableViewer : public QWidget
{
    Q_OBJECT
public:
    ExecutableViewer(FileUnit *fileUnit, QWidget *parent = 0);
    FileUnit *getFileUnit();
    bool loadFile(const QString &fileName) {return true;}
    bool save() {return true;}
    bool saveAs() {return true;}
    bool saveFile(const QString &fileName) {return true;}
    QString userFriendlyCurrentFile() {return QString("a");}
    QString currentFile() { return QString("current"); }
    virtual ~ExecutableViewer();

signals:

public slots:
private:
    QSplitter *split;
    HierarchicalViewer *hierarchicalViewer;
    QHexEdit *hexViewer;
    SearchBar *searchBar;
    FileUnit *fileUnit;
    QFile *file_q;
    QWidget *defaultSpecialRep;
    QWidget *createDefaultSpecialRep();
};

#endif // EXECUTABLE_VIEWER_HPP
