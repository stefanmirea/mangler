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

#include "main_window.hpp"
#include "executable_viewer.hpp"
#include "elf_file.hpp"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(QString("Interactive Executable Mangler"));

    mdiArea = new QMdiArea();
    setCentralWidget(mdiArea);
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)), this, SLOT(updateActions()));

    createActions();

    QMenu *fileMenu = menuBar()->addMenu(QString("File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    QMenu *viewMenu = menuBar()->addMenu(QString("View"));
    viewMenu->addAction(refreshAction);

    QMenu *editMenu = menuBar()->addMenu(QString("Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    windowMenu = menuBar()->addMenu(QString("Window"));
    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateCheckableWindows()));
    windowMenu->addAction(closeAction);
    windowMenu->addAction(closeAllAction);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAction);
    windowMenu->addAction(cascadeAction);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAction);
    windowMenu->addAction(previousAction);

    windowActionGroup = new QActionGroup(this);
    signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(QWidget *)), this, SLOT(selectWindow(QWidget *)));

    updateCheckableWindows();

    QMenu *helpMenu = menuBar()->addMenu(QString("Help"));
    helpMenu->addAction(aboutAction);

    QToolBar *fileToolBar = new QToolBar();
    addToolBar(fileToolBar);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    QToolBar *viewToolBar = new QToolBar();
    addToolBar(viewToolBar);
    viewToolBar->addAction(refreshAction);

    QToolBar *editToolBar = new QToolBar();
    addToolBar(editToolBar);
    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
}

void MainWindow::createActions()
{
    /* File menu */
    openAction = new QAction(QString("Open"), this);
    openAction->setIcon(QIcon::fromTheme("document-open", QIcon(":/icons/open.png")));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(QString("Save"), this);
    saveAction->setIcon(QIcon::fromTheme("document-save", QIcon(":/icons/save.png")));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(QString("Save As..."), this);
    saveAsAction->setIcon(QIcon::fromTheme("document-save-as", QIcon(":/icons/save.png")));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAction = new QAction(QString("Exit"), this);
    exitAction->setIcon(QIcon::fromTheme("application-exit", QIcon(":/icons/exit.png")));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));

    /* View menu */
    refreshAction = new QAction(QString("Refresh"), this);
    refreshAction->setIcon(QIcon::fromTheme("view-refresh", QIcon(":/icons/refresh.png")));
    connect(refreshAction, SIGNAL(triggered()), this, SLOT(refresh()));

    /* Edit menu */
    undoAction = new QAction(QString("Undo"), this);
    undoAction->setIcon(QIcon::fromTheme("edit-undo", QIcon(":/icons/undo.png")));
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));

    redoAction = new QAction(QString("Redo"), this);
    redoAction->setIcon(QIcon::fromTheme("edit-redo", QIcon(":/icons/redo.png")));
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));

    copyAction = new QAction(QString("Copy Hex"), this);
    copyAction->setIcon(QIcon::fromTheme("edit-copy", QIcon(":/icons/copy.png")));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAction = new QAction(QString("Paste Hex"), this);
    pasteAction->setIcon(QIcon::fromTheme("edit-paste", QIcon(":/icons/paste.png")));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

    /* Window menu */
    closeAction = new QAction(QString("Close"), this);
    connect(closeAction, SIGNAL(triggered()), mdiArea, SLOT(closeActiveSubWindow()));

    closeAllAction = new QAction(QString("Close All"), this);
    connect(closeAllAction, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    tileAction = new QAction(QString("Tile"), this);
    connect(tileAction, SIGNAL(triggered()), mdiArea, SLOT(tileSubWindows()));

    cascadeAction = new QAction(QString("Cascade"), this);
    connect(cascadeAction, SIGNAL(triggered()), mdiArea, SLOT(cascadeSubWindows()));

    nextAction = new QAction(QString("Next"), this);
    connect(nextAction, SIGNAL(triggered()), mdiArea, SLOT(activateNextSubWindow()));

    previousAction = new QAction(QString("Previous"), this);
    connect(previousAction, SIGNAL(triggered()), mdiArea, SLOT(activatePreviousSubWindow()));

    /* Help menu */
    aboutAction = new QAction(QString("About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    updateActions();
}

void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(this, QString("Open"));
    if (!filename.isEmpty())
        open(filename);
}

void MainWindow::open(const QString &filename)
{
    QString canonicalName = QFileInfo(filename).canonicalFilePath();
    if (canonicalName == "")
    {
        QMessageBox::critical(this, QString("Error"), QString("The file %1 does not exist.")
                              .arg(filename));
        return;
    }

    foreach (QMdiSubWindow *window, mdiArea->subWindowList())
    {
        ExecutableViewer *ev = qobject_cast<ExecutableViewer *>(window->widget());
        if (ev->getFileUnit()->getName() == canonicalName.toStdString())
        {
            mdiArea->setActiveSubWindow(window);
            return;
        }
    }

    /* check read access */
    QFile qFile(canonicalName);
    if (!qFile.open(QFile::ReadOnly))
    {
        QMessageBox::critical(this, QString("Error"), QString("Cannot read file %1:\n%2.")
                              .arg(canonicalName) .arg(qFile.errorString()));
        return;
    }
    qFile.close();

    /* check file type */
    FileUnit *file;
    do {
        file = new elf::ELFFile(canonicalName.toStdString());
        if (file->getOpenStatus())
            break;
        delete file;

        /* check other file types */

        /* unknown file format */
        QMessageBox::critical(this, QString("Error"), QString("%1: Unknown file format.")
                              .arg(canonicalName));
        return;
    } while (false);

    ExecutableViewer *viewer = new ExecutableViewer(file, mdiArea);
    mdiArea->addSubWindow(viewer);
    viewer->showMaximized();
}

void MainWindow::save() {}

void MainWindow::saveAs() {}

void MainWindow::exit() {}

void MainWindow::refresh() {}

void MainWindow::undo() {}

void MainWindow::redo() {}

void MainWindow::copy() {}

void MainWindow::paste() {}

void MainWindow::about()
{
    QMessageBox::about(this, QString("About"),
        QString("<p>Ștefan Mirea & Adrian Dobrică 2016.</p><p><a "
                "href=\"https://github.com/stefanmirea/mangler\""
                ">Click!</a></p>"));
}

void MainWindow::updateActions()
{
    bool hasActiveSubWindow = mdiArea->activeSubWindow();

    saveAction->setEnabled(hasActiveSubWindow);
    saveAsAction->setEnabled(hasActiveSubWindow);

    refreshAction->setEnabled(true);

    undoAction->setEnabled(false);
    redoAction->setEnabled(false);
    copyAction->setEnabled(false);
    pasteAction->setEnabled(false);

    closeAction->setEnabled(hasActiveSubWindow);
    closeAllAction->setEnabled(hasActiveSubWindow);
    tileAction->setEnabled(hasActiveSubWindow);
    cascadeAction->setEnabled(hasActiveSubWindow);

    int subWindowsNum = mdiArea->subWindowList().size();
    nextAction->setEnabled(subWindowsNum >= 2);
    previousAction->setEnabled(subWindowsNum >= 2);
}

void MainWindow::updateCheckableWindows()
{
    /* Remove the previous checkable actions. */
#ifdef DEBUG
    assert(!windowMenu->actions().isEmpty());
#endif
    QAction *last;
    while ((last = windowMenu->actions().back()) != previousAction)
    {
        windowMenu->removeAction(last);
        if (!last->isSeparator())
        {
            windowActionGroup->removeAction(last);
            /* signalMapper will automatically remove all the mappings for last if any. */
        }
        delete last;
#ifdef DEBUG
        assert(!windowMenu->actions().isEmpty());
#endif
    }

    if (!mdiArea->subWindowList().empty())
    {
        QAction *separator = new QAction(this);
        separator->setSeparator(true);
        windowMenu->addAction(separator);
    }

    int index = 0;
    foreach (QMdiSubWindow *window, mdiArea->subWindowList())
    {
        ++index;
        ExecutableViewer *ev = qobject_cast<ExecutableViewer *>(window->widget());
        QAction *action = new QAction(QString::fromStdString(ev->getFileUnit()->getName()), this);
        action->setActionGroup(windowActionGroup);
        action->setCheckable(true);
        QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();

#ifdef DEBUG
        /* Reaching this point supposes there is at least one subwindow. Therefore, we also have an
         * active subwindow. */
        assert(activeSubWindow != nullptr);
#endif

        action->setChecked(ev == qobject_cast<ExecutableViewer *>(activeSubWindow->widget()));
        connect(action, SIGNAL(triggered()), signalMapper, SLOT(map()));
        signalMapper->setMapping(action, window);
        windowMenu->addAction(action);
    }
}

void MainWindow::selectWindow(QWidget *subWindow)
{
    QMdiSubWindow *mdiSubWindow = dynamic_cast<QMdiSubWindow *>(subWindow);

#ifdef DEBUG
    assert(mdiSubWindow != nullptr);
#endif

    mdiArea->setActiveSubWindow(mdiSubWindow);
}
