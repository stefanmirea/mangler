#-------------------------------------------------
#
# Project created by QtCreator 2016-04-24T00:13:09
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=gnu++0x
DEFINES += DEBUG
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mangler
TEMPLATE = app

INCLUDEPATH += \
    $$PWD/core \
    $$PWD/dependencies \
    $$PWD/dependencies/QHexEdit \
    $$PWD/elf \
    $$PWD/gui \
    $$PWD/util

SOURCES +=\
    core/code_container.cpp \
    core/container.cpp \
    core/file_assembly.cpp \
    core/file_unit.cpp \
    core/mangler.cpp \
    core/search_engine.cpp \
    elf/elf_file.cpp \
    elf/elf_header_container.cpp \
    elf/e_ident_container.cpp \
    elf/program_header_table_container.cpp \
    elf/section_header_table_container.cpp \
    elf/segment_contents_container.cpp \
    elf/section_contents_container.cpp \
    elf/elf_code_container.cpp \
    dependencies/QHexEdit/qhexedit.cpp \
    dependencies/QHexEdit/chunks.cpp \
    dependencies/QHexEdit/commands.cpp \
    gui/executable_viewer.cpp \
    gui/hierarchical_viewer.cpp \
    gui/main_window.cpp \
    gui/search_bar.cpp \
    gui/hierarchy_node.cpp \
    gui/special_representation/code/asm_viewer.cpp \
    gui/special_representation/code/modify_asmbar.cpp \
    gui/special_representation/code/do.cpp \
    gui/special_representation/default.cpp \
    elf/sht_entry_container.cpp \
    util/util.cpp \
    elf/symbol_table_container.cpp \
    elf/symbol_table_entry_container.cpp

HEADERS  += \
    core/code_container.hpp \
    core/container.hpp \
    core/file_assembly.hpp \
    core/file_unit.hpp \
    core/search_engine.hpp \
    elf/elf_file.hpp \
    elf/elf_header_container.hpp \
    elf/e_ident_container.hpp \
    elf/program_header_table_container.hpp \
    elf/section_header_table_container.hpp \
    elf/segment_contents_container.hpp \
    elf/section_contents_container.hpp \
    elf/elf_code_container.hpp \
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
    dependencies/QHexEdit/qhexedit.hpp \
    dependencies/QHexEdit/chunks.hpp \
    dependencies/QHexEdit/commands.hpp \
    gui/executable_viewer.hpp \
    gui/hierarchical_viewer.hpp \
    gui/main_window.hpp \
    gui/search_bar.hpp \
    gui/hierarchy_node.hpp \
    gui/special_representation/code/asm_viewer.hpp \
    gui/special_representation/code/modify_asmbar.hpp \
    elf/sht_entry_container.hpp \
    util/util.hpp \
    elf/symbol_table_container.hpp \
    elf/symbol_table_entry_container.hpp

RESOURCES += \
    gui/mangler.qrc
