cmake_minimum_required(VERSION 3.27)
project(demo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/ToolKit/QT/5.12.12/mingw73_64")

set(QRC_SOURCE_FILE res/res.qrc)
set(PUBLISH_BIN_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PUBLISH_BIN_RELEASE})

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED
        )

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/Sources/Headers
        ${PROJECT_SOURCE_DIR}/lib
)
if(CMAKE_BUILD_TYPE MATCHES "Release")
    add_executable(demo WIN32 ${QRC_SOURCE_FILE}
            Sources/main.cpp
            Sources/mainwindow.cpp Sources/Headers/mainwindow.h
            Sources/dialogwindow.cpp Sources/Headers/dialogwindow.h
            Sources/QNChatMessage.cpp Sources/Headers/QNChatMessage.h)
else()
    add_executable(demo ${QRC_SOURCE_FILE}
            Sources/main.cpp
            Sources/mainwindow.cpp Sources/Headers/mainwindow.h
            Sources/dialogwindow.cpp Sources/Headers/dialogwindow.h
            Sources/QNChatMessage.cpp Sources/Headers/QNChatMessage.h)
endif()

target_link_libraries(demo
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network)

if (WIN32)
    set(DEBUG_SUFFIX)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
