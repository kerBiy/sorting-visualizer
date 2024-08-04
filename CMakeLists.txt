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

add_executable(sorting_visualiser main.cpp
        MenuWindow.cpp
        MenuWindow.hpp
        OptionManager.cpp
        OptionManager.hpp
        Distributor.cpp
        Distributor.hpp
        Item.hpp
        Linker.cpp
        Linker.hpp
        Sorter.cpp
        Sorter.hpp
        MainWindow.cpp
        MainWindow.hpp)
target_link_libraries(sorting_visualiser
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

