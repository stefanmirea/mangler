#include "main_window.hpp"
#include <QMessageBox>
#include "executable_viewer.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(QString("Interactive Executable Mangler"));

    mdiArea = new QMdiArea();

    QMenu *file = menuBar()->addMenu(QString("File"));
    setCentralWidget(mdiArea);

    createActions();

    file->addAction(newAction);
    file->addAction(aboutAction);
}

void MainWindow::createActions()
{
    newAction = new QAction(QString("New"), this);
    aboutAction = new QAction(QString("About"), this);
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::newFile()
{
    QString filename("hacker.out");
    ExecutableViewer *viewer = new ExecutableViewer(filename, mdiArea);
    mdiArea->addSubWindow(viewer);
    viewer->show();
    mdiArea->tileSubWindows();
}

void MainWindow::about()
{
    QMessageBox::about(this, QString("About"),
        QString("<p>Ștefan Mirea & Adrian Dobrică 2016.</p><p><a "
                "href=\"https://github.com/stefanmirea/mangler\""
                ">Click!</a></p>"));
}
