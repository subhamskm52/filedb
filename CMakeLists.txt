cmake_minimum_required(VERSION 4.1)
project(FileDB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------
# SQLite library
# ----------------------------
add_library(sqlite3
        external/sqlite/sqlite3.c
)

target_include_directories(sqlite3
        PUBLIC
        external/sqlite
)

# ----------------------------
# FileDB core library
# ----------------------------
add_library(filedb
        src/database/connection.cpp
        src/database/statement.cpp
        src/database/database.cpp
        src/importer/CsvImporter.cpp
)

target_include_directories(filedb
        PUBLIC
        include
        external/csv
)

target_link_libraries(filedb
        PUBLIC
        sqlite3
)

# ----------------------------
# FileDB CLI (demo/testing)
# ----------------------------
add_executable(filedb-cli
        src/main.cpp
)

target_link_libraries(filedb-cli
        PRIVATE
        filedb
)