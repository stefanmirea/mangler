#-------------------------------------------------
#
# Project created by QtCreator 2016-04-24T00:13:09
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=gnu++0x
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
    core/file_unit.cpp \
    core/mangler.cpp \
    core/search_engine.cpp \
    elf/elf_file.cpp \
    elf/elf_header_container.cpp \
    elf/program_header_table_container.cpp \
    elf/section_header_table_container.cpp \
    elf/segment_contents_container.cpp \
    elf/section_contents_container.cpp \
    gui/executable_viewer.cpp \
    gui/hierarchical_viewer.cpp \
    gui/main_window.cpp \
    gui/search_bar.cpp \
    gui/hierarchy_node.cpp \
    gui/special_representation/code/asm_viewer.cpp \
    gui/special_representation/code/modify_asmbar.cpp \
    gui/special_representation/code/do.cpp \
    gui/special_representation/default.cpp \
    gui/qhexedit.cpp \
    gui/chunks.cpp \
    gui/commands.cpp

HEADERS  += \
    core/code_container.hpp \
    core/container.hpp \
    core/file_assembly.hpp \
    core/file_unit.hpp \
    core/search_engine.hpp \
    elf/elf_file.hpp \
    elf/elf_header_container.hpp \
    elf/program_header_table_container.hpp \
    elf/section_header_table_container.hpp \
    elf/segment_contents_container.hpp \
    elf/section_contents_container.hpp \
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
    gui/executable_viewer.hpp \
    gui/hierarchical_viewer.hpp \
    gui/main_window.hpp \
    gui/search_bar.hpp \
    gui/hierarchy_node.hpp \
    gui/special_representation/code/asm_viewer.hpp \
    gui/special_representation/code/modify_asmbar.hpp \
    gui/qhexedit.hpp \
    gui/commands.hpp \
    gui/chunks.hpp

RESOURCES += \
    gui/mangler.qrc
