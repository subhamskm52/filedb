#include "filedb/database/database.h"
#include "filedb/importer/CsvImporter.h"
#include "filedb/database/query_builder.h"


#include <string>
#include <exception>

#include "filedb/importer/json-importer.h"

static filedb::Database g_db;
static std::string g_last_error;

static void clear_last_error()
{
    g_last_error.clear();
}

static void set_last_error(const std::exception& e)
{
    g_last_error = e.what();
}

extern "C" {

    /**
     * Open database
     */
    int db_open(const char* path)
    {
        clear_last_error();
        try {
            g_db.open(path);
            return 0;
        } catch (const std::exception& e) {
            set_last_error(e);
            return -1;
        }
    }

    /**
     * Import CSV into a table
     */
    int db_import_csv(const char* csv_path,
                      const char* table_name)
    {
        clear_last_error();
        try {
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
        } catch (const std::exception& e) {
            set_last_error(e);
            return -1;
        }
    }

    /**
     * Import JSON into a table
     */
    int db_import_json(const char* json_path, const char* table_name) {
        clear_last_error();
        try {
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
        } catch (const std::exception& e) {
            set_last_error(e);
            return -1;
        }
    }

    /**
     * Execute arbitrary SQL
     */
    int db_execute(const char* sql)
    {
        clear_last_error();
        try {
            g_db.execute(
                sql,
                nullptr,
                nullptr
            );
            return 0;
        } catch (const std::exception& e) {
            set_last_error(e);
            return -1;
        }
    }

    /**
     * Query and return results as text
     */
    const char* db_query(const char* sql)
    {
        static std::string result;
        result.clear();
        clear_last_error();

        try {
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
        } catch (const std::exception& e) {
            set_last_error(e);
            result = std::string("__ERROR__:") + e.what();
        }

        return result.c_str();
    }

    const char* db_last_error()
    {
        return g_last_error.c_str();
    }

}