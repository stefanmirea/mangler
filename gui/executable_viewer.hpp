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
#include <QCloseEvent>

#include "hierarchical_viewer.hpp"
#include "qhexedit.hpp"
#include "search_bar.hpp"
#include "main_window.hpp"

#include "file_unit.hpp"

/**
 * The internal widget of the MDI subwindow associated with an open file.
 */
class ExecutableViewer : public QWidget
{
    Q_OBJECT
public:
    ExecutableViewer(MainWindow *mainWindow, FileUnit *fileUnit, QWidget *parent = 0);
    MainWindow *getMainWindow();
    FileUnit *getFileUnit();
    bool save();
    bool saveAs();
    bool saveFile(const std::string &fileName);
    bool isRefreshable();
    void setRefreshable(bool refreshable);
    bool refresh(const std::string &fileName, bool temporary);
    virtual ~ExecutableViewer();

signals:

public slots:
    void hexDataChanged();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private:
    MainWindow *mainWindow;
    QSplitter *split;
    HierarchicalViewer *hierarchicalViewer;
    QHexEdit *hexViewer;
    SearchBar *searchBar;
    FileUnit *fileUnit;
    QWidget *defaultSpecialRep;
    QWidget *createDefaultSpecialRep();
    bool refreshable;
};

#endif // EXECUTABLE_VIEWER_HPP_
