cmake_minimum_required(VERSION 4.0)
project(library_manager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(library_core
        include/Book.h
        include/Record.h
        include/User.h
        include/LibraryOperations.h
        include/Library.h
        src/Library.cpp
        src/LibraryConsole.cpp
        app/main.cpp

)

target_include_directories(library_core PUBLIC include)
