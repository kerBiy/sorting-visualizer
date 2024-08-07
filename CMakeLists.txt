cmake_minimum_required(VERSION 3.28)

project(sorting_visualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
        src/MenuWindow.cpp
        src/OptionManager.cpp
        src/Distributor.cpp
        src/Linker.cpp
        src/Sorter.cpp
        src/MainWindow.cpp
        src/main.cpp
)

set(HEADERS
        headers/MenuWindow.hpp
        headers/OptionManager.hpp
        headers/Distributor.hpp
        headers/Linker.hpp
        headers/Sorter.hpp
        headers/MainWindow.hpp
        headers/Item.hpp
)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)

add_executable(sorting_visualizer
        ${SOURCES}
        ${HEADERS}
)

target_link_libraries(sorting_visualizer
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

target_include_directories(sorting_visualizer
        PUBLIC headers
)
