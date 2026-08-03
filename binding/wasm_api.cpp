#include "filedb/database/database.h"
#include "filedb/importer/CsvImporter.h"
#include "filedb/database/query_builder.h"


#include <string>

#include "filedb/importer/json-importer.h"

static filedb::Database g_db;

extern "C" {

    /**
     * Open database
     */
    int db_open(const char* path)
    {
        g_db.open(path);
        return 0;
    }

    /**
     * Import CSV into a table
     */
    int db_import_csv(const char* csv_path,
                      const char* table_name)
    {
        filedb::importer::CsvImporter importer;

        auto tbl = importer.import(
            csv_path,
            table_name
        );

        auto create_sql =
            filedb::QueryBuilder::create_table(tbl);

        g_db.execute(
            create_sql,
            nullptr,
            nullptr
        );

        for (auto& row : tbl.rows) {

            auto row_sql =
                filedb::QueryBuilder::insert_row(
                    table_name,
                    tbl,
                    row
                );

            g_db.execute(
                row_sql,
                nullptr,
                nullptr
            );
        }

        return 0;
    }

    /**
     * Import JSON into a table
     */
    int db_import_json(const char* json_path, const char* table_name) {
        filedb::importer::JsonImporter imptr;
        filedb::model::Table tbl = imptr.import(json_path, table_name);

        auto create_sql =
            filedb::QueryBuilder::create_table(tbl);

        g_db.execute(
            create_sql,
            nullptr,
            nullptr
        );

        for (auto& row : tbl.rows) {

            auto row_sql =
                filedb::QueryBuilder::insert_row(
                    table_name,
                    tbl,
                    row
                );

            g_db.execute(
                row_sql,
                nullptr,
                nullptr
            );
        }
        return 0;
    }

    /**
     * Execute arbitrary SQL
     */
    int db_execute(const char* sql)
    {
        g_db.execute(
            sql,
            nullptr,
            nullptr
        );
        return 0;
    }

    /**
     * Query and return results as text
     */
    const char* db_query(const char* sql)
    {
        static std::string result;
        result.clear();

        g_db.execute(
            sql,
            [](void* data,
               int argc,
               char** argv,
               char** colNames) -> int
            {
                auto* output =
                    static_cast<std::string*>(data);

                for (int i = 0; i < argc; ++i) {

                    *output += colNames[i];
                    *output += "=";
                    *output +=
                        argv[i]
                            ? argv[i]
                            : "NULL";

                    *output += "\n";
                }

                *output += "\n";

                return 0;
            },
            &result
        );

        return result.c_str();
    }

}