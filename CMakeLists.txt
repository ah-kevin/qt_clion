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

# FFmpeg的头文件搜索路径
include_directories(/opt/homebrew/Cellar/ffmpeg/5.0.1/include/)
# 动态链接库或静态链接库的搜索路径
link_directories(/opt/homebrew/Cellar/ffmpeg/5.0.1/lib/)

add_executable(qt_clion main.cpp mainWindow.h mainWindow.cpp mainWindow.ui)
target_link_libraries(qt_clion
        Qt::Core
        Qt::Widgets
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        postproc
        swscale
        swresample
        )