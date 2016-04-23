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
    void open();
    void save();
    void saveAs();
    void exit();
    void undo();
    void redo();
    void copy();
    void paste();
    void about();
private:
    void createActions();

    QMdiArea *mdiArea;
    QAction *openAction, *saveAction, *saveAsAction, *exitAction;
    QAction *undoAction, *redoAction, *copyAction, *pasteAction;
    QAction *aboutAction;
};

#endif // MAINWINDOW_H
