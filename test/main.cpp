#include <iostream>
#include <filesystem>
#include <stdexcept>

#include "filedb/database/database.h"
#include "filedb/database/query_builder.h"
#include "filedb/model/table.h"

#define ASSERT_TRUE(expr)                                      \
    do {                                                       \
        if (!(expr)) {                                         \
            std::cerr << "FAILED: " #expr << std::endl;        \
            return 1;                                          \
        }                                                      \
    } while (0)

#define ASSERT_EQ(a, b)                                        \
    do {                                                       \
        if ((a) != (b)) {                                      \
            std::cerr << "FAILED: " #a " == " #b              \
                      << std::endl;                            \
            return 1;                                          \
        }                                                      \
    } while (0)

int test_database_open_close()
{
    filedb::Database db;

    db.open("test.db");

    ASSERT_TRUE(db.isOpen());

    db.close();

    ASSERT_TRUE(!db.isOpen());

    return 0;
}

int test_query_builder()
{
    filedb::model::Table table(
        "users",
        {"id", "name"},
        {}
    );

    auto sql =
        filedb::QueryBuilder::create_table(table);

    ASSERT_TRUE(
        sql.find("CREATE TABLE") != std::string::npos
    );

    return 0;
}

int test_insert_query()
{
    filedb::model::Table table(
        "users",
        {"id", "name"},
        {}
    );

    auto sql =
        filedb::QueryBuilder::insert_row(
            "users",
            table,
            {"1", "John"}
        );

    ASSERT_TRUE(
        sql.find("INSERT INTO") != std::string::npos
    );

    return 0;
}

int test_table_counts()
{
    filedb::model::Table table(
        "users",
        {"id", "name"},
        {
            {"1", "John"},
            {"2", "Jane"}
        }
    );

    ASSERT_EQ(table.row_count(), 2);
    ASSERT_EQ(table.column_count(), 2);

    return 0;
}

int test_database_insert()
{
    filedb::Database db;

    db.open("test.db");

    filedb::model::Table table(
        "users",
        {"id", "name"},
        {}
    );

    db.execute(
        filedb::QueryBuilder::create_table(table),
        nullptr,
        nullptr
    );

    db.execute(
        filedb::QueryBuilder::insert_row(
            "users",
            table,
            {"1", "John"}
        ),
        nullptr,
        nullptr
    );

    db.close();

    return 0;
}

int main()
{
    try
    {
        if (test_database_open_close()) return 1;
        if (test_query_builder()) return 1;
        if (test_insert_query()) return 1;
        if (test_table_counts()) return 1;
        if (test_database_insert()) return 1;

        std::filesystem::remove("test.db");

        std::cout << "All tests passed!" << std::endl;

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "EXCEPTION: "
                  << e.what()
                  << std::endl;

        return 1;
    }
}
