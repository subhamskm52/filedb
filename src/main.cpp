#include "filedb/database/database.h"
#include "filedb/importer/CsvImporter.h"
#include <filesystem>

#include "filedb/database/query_builder.h"

int main() {
    filedb::Database db;
    db.open(":memory:");
    filedb::importer::CsvImporter importer;
    auto tbl = importer.import("abc.csv", "users");
    // tbl.print();
    auto create_sql =
        filedb::QueryBuilder::create_table(tbl);
    db.execute(create_sql, nullptr, nullptr);

    for (auto row : tbl.rows) {
        auto row_sql = filedb::QueryBuilder::insert_row("users",tbl,row);
        db.execute(row_sql, nullptr, nullptr);
    }
    db.execute(
        "SELECT * FROM users",
        [](void* data, int argc, char** argv, char** colNames) -> int {

            for (int i = 0; i < argc; ++i) {
                std::cout
                    << colNames[i]
                    << " = "
                    << (argv[i] ? argv[i] : "NULL")
                    << '\n';
            }
            std::cout << '\n';
            return 0;
        },
        nullptr
    );
    std::cout<<"end of program";
    return 0;
}
