cmake_minimum_required(VERSION 3.15)
project(Tools)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(QT_DIR C:/Qt/Qt5.12.7/5.12.7/mingw73_32)
set(CMAKE_PREFIX_PATH ${QT_DIR} C:/Qt/Qt5.12.7)

find_package(Qt5Widgets)
find_package(Qt5Core)
get_target_property(QtCore_location Qt5::Core LOCATION)
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")
link_directories(${QT_DIR}/lib C:/Qt/Qt5.12.7/5.12.7/mingw73_32/lib)
foreach (plugin ${Qt5Network_PLUGINS})
    get_target_property(_loc ${plugin} LOCATION)
    message("Plugin ${plugin} is at location ${_loc}")
endforeach ()

add_executable(Tools WIN32 main.cpp mainwindow.cpp mainwindow.h FrameInfoDialog.cpp FrameInfoDialog.h)
qt5_use_modules(Tools Widgets Core SerialPort Network)