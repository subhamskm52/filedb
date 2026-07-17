#pragma once

#include <string>

#include "filedb/model/table.h"

namespace filedb {

    class QueryBuilder {
    public:
        static std::string create_table(
            const std::string& table_name,
            const model::Table& table);

        static std::string insert_row(
            const std::string& table_name,
            const model::Table& table,
            const std::vector<std::string>& row);

    private:
        static std::string to_sqlite_type(model::DataType type);
        static std::string escape_sql_string(const std::string& value);
    };

}