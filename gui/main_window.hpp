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

#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QMdiArea>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QSignalMapper>

class ExecutableViewer;

/**
 * The main window of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void open(const QString &filename);
signals:

public slots:
    void open();
    void save();
    void saveAs();
    void exit();
    void refresh();
    void undo();
    void redo();
    void copy();
    void paste();
    void about();
    void updateActions();
    void updateCheckableWindows();
    void selectWindow(QWidget *subWindow);
protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
private:
    void createActions();
    ExecutableViewer *activeExecutableViewer();

    QMdiArea *mdiArea;
    QAction *openAction, *saveAction, *saveAsAction, *exitAction;
    QAction *refreshAction;
    QAction *undoAction, *redoAction, *copyAction, *pasteAction;
    QAction *closeAction, *closeAllAction, *tileAction, *cascadeAction, *nextAction,
            *previousAction;
    QAction *aboutAction;
    QMenu *windowMenu;
    QActionGroup *windowActionGroup;
    QSignalMapper *signalMapper;
};

#endif // MAIN_WINDOW_HPP_
