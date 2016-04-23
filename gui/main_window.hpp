#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
signals:

public slots:
    void newFile();
    void about();
private:
    void createActions();

    QMdiArea *mdiArea;
    QToolBar *toolBar;
    QAction *aboutAction, *newAction;
};

#endif // MAINWINDOW_H
