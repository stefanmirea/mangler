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

    /* Help menu */
    aboutAction = new QAction(QString("About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    updateActions();
}

void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(this, QString("Open"));
    if (filename.isEmpty())
        return;
    filename = QFileInfo(filename).canonicalFilePath();

    foreach (QMdiSubWindow *window, mdiArea->subWindowList())
    {
        ExecutableViewer *ev = qobject_cast<ExecutableViewer *>(window->widget());
        if (ev->getFileUnit()->getName() == filename.toStdString())
        {
            mdiArea->setActiveSubWindow(window);
            return;
        }
    }

    /* check read access */
    QFile qFile(filename);
    if (!qFile.open(QFile::ReadOnly))
        QMessageBox::critical(this, QString("Error"), QString("Cannot read file %1:\n%2.")
                              .arg(filename) .arg(qFile.errorString()));
    qFile.close();

    /* check file type */
    FileUnit *file;
    do { 
        file = new elf::ELFFile(filename.toStdString());
        if (file->getOpenStatus())
            break;
        delete file;

        /* check other file types */

        /* unknown file format */
        QMessageBox::critical(this, QString("Error"), QString("Unknown file format."));
        return;
    } while (false);

    ExecutableViewer *viewer = new ExecutableViewer(file, mdiArea);
    mdiArea->addSubWindow(viewer);
    viewer->showMaximized();
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

void MainWindow::updateActions()
{
    bool hasActiveSubWindow = mdiArea->activeSubWindow();

    saveAction->setEnabled(hasActiveSubWindow);
    saveAsAction->setEnabled(hasActiveSubWindow);

    undoAction->setEnabled(false);
    redoAction->setEnabled(false);
    copyAction->setEnabled(false);
    pasteAction->setEnabled(false);
}
