﻿# CMakeList.txt : CMake project for A429Parser, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10...3.18)

#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY)
set(QT_DIR "/Users/songbinbin/Documents/Library/Qt/6.1.0/clang_64")
set(CMAKE_PREFIX_PATH "${QT_DIR}\\lib\\cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets PrintSupport REQUIRED)

include_directories(
    .
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/3rdparty
)

set(QCustomplot_DIR 
    "${PROJECT_SOURCE_DIR}/3rdparty/qcustomplot"
)

set(A429PARSER_SRCS
    "${QCustomplot_DIR}/qcustomplot.cpp"
    "${QCustomplot_DIR}/qcustomplot.h"
    "gui/a4292value.ui"
    "gui/a429parser.ui"
    "gui/value2a429.ui"
    "gui/a4292valuebatch.ui" 
    "gui/a429parser.h" 
    "gui/a429parser.cpp"
    "gui/a4292value.h" 
    "gui/a4292value.cpp"
    "gui/value2a429.cpp" 
    "gui/value2a429.h"
    "gui/a4292valuebatch.h"
    "gui/a4292valuebatch.cpp"
    "view/a429bitsview.h" 
    "view/a429bitsview.cpp"
    "model/a429bitsmodel.h"
    "model/a429bitsmodel.cpp" 
    "delegate/aligndelegate.h"
    "delegate/aligndelegate.cpp"
    "delegate/a429bitsdelegate.cpp" 
    "delegate/a429bitsdelegate.h"
    "a429parser.rc"
    "a429parser.qrc"
    "a429bits.h"
    "utils.h"
    "main.cpp"
)

# Set some Win32 Specific Settings
if(WIN32)
    add_executable (A429Parser WIN32 ${A429PARSER_SRCS})
endif(WIN32)
# Set some Apple MacOS Specific settings
if (APPLE)
    set(MACOSX_BUNDLE_ICON_FILE "a429parser.icns")
    set(APP_ICON_MACOSX ${CMAKE_CURRENT_SOURCE_DIR}/images/a429parser.icns)
    set_source_files_properties(${APP_ICON_MACOSX}
            PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable (A429Parser MACOSX_BUNDLE ${APP_ICON_MACOSX} ${A429PARSER_SRCS})
endif (APPLE)

# Add source to this project's executable.
target_link_libraries(A429Parser PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets 
    Qt6::PrintSupport
)

# Copy after build finished 
if(WIN32)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        add_custom_command(TARGET A429Parser POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_DIR}\\bin\\Qt6Cored.dll"
                "${QT_DIR}\\bin\\Qt6Guid.dll"
                "${QT_DIR}\\bin\\Qt6Widgetsd.dll"
                "${QT_DIR}\\bin\\Qt6PrintSupportd.dll"
                $<TARGET_FILE_DIR:A429Parser>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_DIR}\\plugins\\platforms\\qwindowsd.dll"
                $<TARGET_FILE_DIR:A429Parser>\\platforms\\qwindowsd.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_DIR}\\plugins\\styles\\qwindowsvistastyled.dll"
                $<TARGET_FILE_DIR:A429Parser>\\styles\\qwindowsvistastyled.dll)
    else ()
            add_custom_command(TARGET A429Parser POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_DIR}\\bin\\Qt6Core.dll"
                "${QT_DIR}\\bin\\Qt6Gui.dll"
                "${QT_DIR}\\bin\\Qt6Widgets.dll"
                "${QT_DIR}\\bin\\Qt6PrintSupport.dll"
                "$<TARGET_FILE_DIR:A429Parser>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_DIR}\\plugins\\platforms\\qwindows.dll"
                $<TARGET_FILE_DIR:A429Parser>\\platforms\\qwindows.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_DIR}\\plugins\\styles\\qwindowsvistastyle.dll"
                $<TARGET_FILE_DIR:A429Parser>\\styles\\qwindowsvistastyle.dll)  
    endif()
endif()


# TODO: Add tests and install targets if needed.
