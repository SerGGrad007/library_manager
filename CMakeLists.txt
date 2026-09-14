cmake_minimum_required(VERSION 3.16)
project(library_manager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(library_core
        src/Library.cpp
        src/LibraryConsole.cpp
        src/User.cpp
        src/Book.cpp

)

add_executable(library_app app/main.cpp)

target_include_directories(library_core PUBLIC include)

target_link_libraries(library_app PRIVATE library_core)
