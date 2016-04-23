#-------------------------------------------------
#
# Project created by QtCreator 2016-04-24T00:13:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mangler
TEMPLATE = app

INCLUDEPATH += \
    $$PWD/core \
    $$PWD/dependencies \
    $$PWD/elf \
    $$PWD/gui \

SOURCES +=\
    core/code_container.cpp \
    core/container.cpp \
    core/file_assembly.cpp \
    core/file_handler.cpp \
    core/file_unit.cpp \
    core/mangler.cpp \
    core/search_engine.cpp \
    elf/elf_file.cpp \
    gui/asm_viewer.cpp \
    gui/executable_viewer.cpp \
    gui/hex_viewer.cpp \
    gui/hierarchical_viewer.cpp \
    gui/main_window.cpp \
    gui/modify_asmbar.cpp \
    gui/search_bar.cpp

HEADERS  += \
    core/code_container.hpp \
    core/container.hpp \
    core/file_assembly.hpp \
    core/file_handler.hpp \
    core/file_unit.hpp \
    core/search_engine.hpp \
    elf/elf_file.hpp \
    dependencies/elfio/elf_types.hpp \
    dependencies/elfio/elfio_utils.hpp \
    dependencies/elfio/elfio_symbols.hpp \
    dependencies/elfio/elfio_strings.hpp \
    dependencies/elfio/elfio_segment.hpp \
    dependencies/elfio/elfio_section.hpp \
    dependencies/elfio/elfio_relocation.hpp \
    dependencies/elfio/elfio_note.hpp \
    dependencies/elfio/elfio_header.hpp \
    dependencies/elfio/elfio_dynamic.hpp \
    dependencies/elfio/elfio_dump.hpp \
    dependencies/elfio/elfio.hpp \
    gui/asm_viewer.hpp \
    gui/executable_viewer.hpp \
    gui/hex_viewer.hpp \
    gui/hierarchical_viewer.hpp \
    gui/main_window.hpp \
    gui/modify_asmbar.hpp \
    gui/search_bar.hpp

RESOURCES += \
    gui/mangler.qrc
