cmake_minimum_required(VERSION 3.31)
project(TetrisCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(TetrisCPP
        src/main.cpp
        src/BoardView.cpp
        src/BoardView.h
        src/Observable.cpp
        src/Observable.h
        src/Observer.cpp
        src/Observer.h
        src/TileGrid.cpp
        src/TileGrid.h
        src/Tetromino.cpp
        src/Tetromino.h
        src/BoardModel.cpp
        src/BoardModel.h
)

target_include_directories(TetrisCPP PRIVATE src/)
target_compile_features(TetrisCPP    PRIVATE cxx_std_17)
target_link_libraries(TetrisCPP PRIVATE SFML::Graphics)
