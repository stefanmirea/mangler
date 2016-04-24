#ifndef EXECUTABLEVIEWER_H
#define EXECUTABLEVIEWER_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QSplitter>
#include <QWidget>
#include <QVBoxLayout>

#include "hierarchical_viewer.hpp"
#include "hex_viewer.hpp"
#include "search_bar.hpp"
#include "modify_asmbar.hpp"
#include "asm_viewer.hpp"

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

signals:

public slots:
private:
    HierarchicalViewer *hierarchicalViewer;
    HexViewer *hexViewer;
    SearchBar *searchBar;
    ModifyASMBar *modifyBar;
    ASMViewer *asmView;
    FileUnit *fileUnit;
};

#endif // EXECUTABLEVIEWER_H
