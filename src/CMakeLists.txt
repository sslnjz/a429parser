# CMakeList.txt : CMake project for A429Parser, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10...3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PrintSupport )
qt_standard_project_setup()

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
    "view/a429bitsparseview.h"
    "view/a429bitsparseview.cpp"
    "view/a429bitssetview.h"
    "view/a429bitssetview.cpp"
    "model/a429bitsmodel.h"
    "model/a429bitsmodel.cpp" 
    "model/a429bitsparsemodel.h"
    "model/a429bitsparsemodel.cpp"
    "model/a429bitssetmodel.h" 
    "model/a429bitssetmodel.cpp"
    "delegate/aligndelegate.h"
    "delegate/aligndelegate.cpp"
    "delegate/a429bitsdelegate.cpp" 
    "delegate/a429bitsdelegate.h"
    "delegate/a429bitssetdelegate.h"
    "delegate/a429bitssetdelegate.cpp"
    "a429parser.rc"
    "a429parser.qrc"
    "a429bits.h"
    "utils.h"
    "utils.cpp"
    "main.cpp" )

# Set some syetem Specific Settings
if(WIN32)
    qt_add_executable(${PROJECT_NAME} WIN32 ${A429PARSER_SRCS})
elseif (APPLE)
    set(MACOSX_BUNDLE_ICON_FILE "a429parser.icns")
    set(APP_ICON_MACOSX ${CMAKE_CURRENT_SOURCE_DIR}/images/a429parser.icns)
    set_source_files_properties(${APP_ICON_MACOSX}
            PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable (${PROJECT_NAME} MACOSX_BUNDLE ${APP_ICON_MACOSX} ${A429PARSER_SRCS})
endif ()

# Add source to this project's executable.
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets
    Qt6::PrintSupport
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})


# TODO: Add tests and install targets if needed.

