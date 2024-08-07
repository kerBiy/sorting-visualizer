cmake_minimum_required(VERSION 3.28)
project(sorting_visualiser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(sorting_visualiser src/main.cpp
        src/MenuWindow.cpp
        headers/MenuWindow.hpp
        src/OptionManager.cpp
        headers/OptionManager.hpp
        src/Distributor.cpp
        headers/Distributor.hpp
        headers/Item.hpp
        src/Linker.cpp
        headers/Linker.hpp
        src/Sorter.cpp
        headers/Sorter.hpp
        src/MainWindow.cpp
        headers/MainWindow.hpp)

target_link_libraries(sorting_visualiser
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

