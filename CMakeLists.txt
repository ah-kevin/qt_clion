cmake_minimum_required(VERSION 3.21)
project(qt_clion)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt/6.2.3_1/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Widgets
        REQUIRED)

add_executable(qt_clion main.cpp mainWindow.h mainWindow.cpp mainWindow.ui)
target_link_libraries(qt_clion
        Qt::Core
        Qt::Widgets
        )

