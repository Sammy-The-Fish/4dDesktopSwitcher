cmake_minimum_required(VERSION 4.1)
project(4dDesktopSwitcher)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(4dDesktopSwitcher main.cpp
        DesktopPosition.cpp
        DesktopPosition.h)


target_link_libraries(4dDesktopSwitcher
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
