#include "main_window.hpp"
#include <QMessageBox>
#include "executable_viewer.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(QString("Interactive Executable Mangler"));

    mdiArea = new QMdiArea();
    setCentralWidget(mdiArea);

    createActions();

    QMenu *fileMenu = menuBar()->addMenu(QString("File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    QMenu *editMenu = menuBar()->addMenu(QString("Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    QMenu *helpMenu = menuBar()->addMenu(QString("Help"));
    helpMenu->addAction(aboutAction);

    QToolBar *fileToolBar = new QToolBar();
    addToolBar(fileToolBar);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

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
    openAction->setIcon(QIcon::fromTheme("document-open", QIcon(":/images/open.png")));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(QString("Save"), this);
    saveAction->setIcon(QIcon::fromTheme("document-save", QIcon(":/images/save.png")));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(QString("Save As..."), this);
    saveAsAction->setIcon(QIcon::fromTheme("document-save-as", QIcon(":/images/save.png")));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAction = new QAction(QString("Exit"), this);
    exitAction->setIcon(QIcon::fromTheme("application-exit", QIcon(":/images/exit.png")));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));

    /* Edit menu */
    undoAction = new QAction(QString("Undo"), this);
    undoAction->setIcon(QIcon::fromTheme("edit-undo", QIcon(":/images/undo.png")));
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));

    redoAction = new QAction(QString("Redo"), this);
    redoAction->setIcon(QIcon::fromTheme("edit-redo", QIcon(":/images/redo.png")));
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));

    copyAction = new QAction(QString("Copy Hex"), this);
    copyAction->setIcon(QIcon::fromTheme("edit-copy", QIcon(":/images/copy.png")));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAction = new QAction(QString("Paste Hex"), this);
    pasteAction->setIcon(QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png")));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

    /* Help menu */
    aboutAction = new QAction(QString("About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::open()
{
    QString filename("hacker.out");
    ExecutableViewer *viewer = new ExecutableViewer(filename, mdiArea);
    mdiArea->addSubWindow(viewer);
    viewer->show();
    mdiArea->tileSubWindows();
}

void MainWindow::save() {}

void MainWindow::saveAs() {}

void MainWindow::exit() {}

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
