cmake_minimum_required(VERSION 3.5)

project(JumpOffTheBridge VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package (Qt5 COMPONENTS Multimedia REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        player.h
        player.cpp
        gameobject.h
        gameobject.cpp
        level1.h
        level1.cpp
        moveobject.h
        moveobject.cpp
        game.cpp
        game.h
        staticObject.cpp
        staticObject.h
        floor.cpp
        floor.h
        parameter.cpp
        signboard.h
        signboard.cpp
        oldLady.h
        oldLady.cpp
        level2.cpp
        level2.h
        bulls.h
        bulls.cpp
        level3.h
        level3.cpp
        key.h
        key.cpp
        wall.h
        wall.cpp
        activeBoard.h
        activeBoard.cpp
        level5.h
        level5.cpp
        bullet.h
        bullet.cpp
        dog.h
        dog.cpp
        floor1.h
        floor1.cpp
        level6.h
        level6.cpp
        trap.h
        trap.cpp
        level4.h
        level4.cpp
        floor2.h
        floor2.cpp
        level7.h
        level7.cpp
        ghost.h
        ghost.cpp
	level8.h
        level8.cpp
        arrow.h
        arrow.cpp
        arrowshelf.h
        arrowshelf.cpp
        dragon.h
        dragon.cpp
        bomb.h
        bomb.cpp
        blood.h
        blood.cpp
)

set(QRC_SOURCE_FILES res.qrc)
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(testt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET testt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(testt SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(testt
            ${PROJECT_SOURCES}
            ${QRC_FILES}
        )
    endif()
endif()

target_link_libraries(testt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  Qt5::Multimedia )

set_target_properties(testt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS testt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(testt)
endif()
