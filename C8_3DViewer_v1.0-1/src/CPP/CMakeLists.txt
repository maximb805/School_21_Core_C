cmake_minimum_required(VERSION 3.5)

project(CPP VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS OpenGLWidgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        glwidget.h
        glwidget.cpp
        ../C/s21_3Dviewer.h
        ../C/s21_obj_parser.c
        ../C/s21_list.c
        ../C/s21_affine_transformations.c
        ./QtGifimage/src/gifimage/qgifimage.cpp
        ./QtGifimage/src/gifimage/qgifimage.h
        ./QtGifimage/src/gifimage/qgifimage_p.h
        ./QtGifimage/src/gifimage/qgifglobal.h
        ./QtGifimage/src/3rdparty/giflib/dgif_lib.c
        ./QtGifimage/src/3rdparty/giflib/egif_lib.c
        ./QtGifimage/src/3rdparty/giflib/gif_err.c
        ./QtGifimage/src/3rdparty/giflib/gif_font.c
        ./QtGifimage/src/3rdparty/giflib/gif_hash.c
        ./QtGifimage/src/3rdparty/giflib/gif_hash.h
        ./QtGifimage/src/3rdparty/giflib/gif_lib.h
        ./QtGifimage/src/3rdparty/giflib/gif_lib_private.h
        ./QtGifimage/src/3rdparty/giflib/gifalloc.c
        ./QtGifimage/src/3rdparty/giflib/quantize.c
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3dViewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CPP APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3dViewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3dViewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(3dViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGLWidgets)

set_target_properties(3dViewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3dViewer)
endif()
