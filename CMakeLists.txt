cmake_minimum_required(VERSION 3.16)
project(LinNote VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

qt_add_executable(LinNote
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/PortablePaths.cpp
    src/PortablePaths.h
    src/CommandPage.cpp
    src/CommandPage.h
    src/ConfigPage.cpp
    src/ConfigPage.h
    src/NotebookPage.cpp
    src/NotebookPage.h
    resources/resources.qrc
)

target_link_libraries(LinNote PRIVATE Qt6::Widgets Qt6::Network)

install(TARGETS LinNote RUNTIME DESTINATION .)
install(DIRECTORY resources/commands resources/configs DESTINATION share/linnote)
