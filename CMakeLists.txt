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
        src/model/table.cpp
        src/database/query_builder.cpp
        src/exporter/exporter.cpp
)

target_include_directories(filedb
        PUBLIC
        include
        external/csv
        external/spdlog-1.17.0/include
        external/json
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

add_executable(filedb-test test/main.cpp)
target_link_libraries(filedb-test
        PRIVATE
        filedb
)

add_executable(filedb-example
        example/hello-world.cpp
)

target_link_libraries(filedb-example
        PRIVATE
        filedb
)



add_executable(filedb-wasm
        binding/wasm_api.cpp
)
target_link_libraries(filedb-wasm
        PRIVATE
        filedb
)

target_link_options(filedb-wasm PRIVATE
        "-sMODULARIZE=1"
        "-sEXPORT_ES6=1"
        "-sEXPORTED_FUNCTIONS=[\"_db_open\",\"_db_import_csv\",\"_db_execute\",\"_db_query\"]"
        "-sEXPORTED_RUNTIME_METHODS=[\"ccall\",\"UTF8ToString\"]"
)