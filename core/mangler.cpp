#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "executable_viewer.hpp"
#include "main_window.hpp"

#include "file_assembly.hpp"
#include "search_engine.hpp"
#include "container.hpp"
#include "code_container.hpp"
#include "file_unit.hpp"
#include "elf_file.hpp"
#include "elfio/elfio.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow *wn = new MainWindow();
    wn->show();

    return app.exec();
}
