cmake_minimum_required(VERSION 3.5)

project(CureSuch VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        resources.qrc
)

add_library(datastructures STATIC Tree.h Node.h List.h Element.h HashTable.h)
add_library(mainwindow STATIC mainwindow.cpp mainwindow.h mainwindow.ui)
add_library(report STATIC report.h report.cpp report.ui)
add_library(addseller STATIC addseller.cpp addseller.h addseller.ui)
add_library(addnote STATIC addnote.cpp addnote.h addnote.ui)
add_library(debugwindow STATIC debugwindow.cpp debugwindow.h debugwindow.ui)
add_library(search STATIC search.h search.cpp search.ui)
add_library(person STATIC Person.cpp Person.h)
add_library(note STATIC Note.cpp Note.h)
add_library(god STATIC god.h)

target_link_libraries(datastructures PRIVATE god)
target_link_libraries(mainwindow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets god)
target_link_libraries(report PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(addseller PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(addnote PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(debugwindow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets god)
target_link_libraries(search PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CureSuch
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(CureSuch
            ${PROJECT_SOURCES}
            )
endif()

target_link_libraries(CureSuch PRIVATE Qt${QT_VERSION_MAJOR}::Widgets mainwindow report addseller addnote debugwindow search person note datastructures)

set_target_properties(CureSuch PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CureSuch)
endif()
