cmake_minimum_required(VERSION 4.1)
project(FileDB)

set(CMAKE_CXX_STANDARD 20)

add_executable(FileDB src/main.cpp
        src/database/connection.cpp
        include/filedb/database/statement.h
        src/database/statement.cpp
        src/database/database.cpp)

target_include_directories(FileDB PRIVATE include)

add_library(sqlite3 external/sqlite/sqlite3.c)

target_include_directories(sqlite3 PUBLIC external/sqlite)

target_link_libraries(FileDB PRIVATE sqlite3)