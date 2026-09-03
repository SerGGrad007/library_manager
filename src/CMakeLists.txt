add_library(LibraryManager
        core/interface.cpp
)

target_include_directories(LibraryManager PUBLIC ${CMAKE_SOURCE_DIR}/include/core)