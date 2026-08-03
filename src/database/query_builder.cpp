#include "filedb/database/query_builder.h"
#include "filedb/exception.h"
#include "filedb/logger/Logger.h"

namespace filedb {

std::string QueryBuilder::to_sqlite_type(model::DataType type)
{
    switch (type) {
        case model::DataType::Integer:
            return "INTEGER";

        case model::DataType::Double:
            return "REAL";

        case model::DataType::Boolean:
            return "INTEGER";

        case model::DataType::String:
            return "TEXT";

        case model::DataType::Date:
            return "TEXT";

        case model::DataType::DateTime:
            return "TEXT";

        case model::DataType::Binary:
            return "BLOB";

        case model::DataType::Null:
            return "NULL";
    }

    Logger::instance()->error(
        "Unsupported data type encountered while generating SQLite type");

    throw Exception("Unsupported data type");
}

std::string QueryBuilder::escape_sql_string(
    const std::string& value)
{
    std::string escaped = value;

    size_t pos = 0;
    while ((pos = escaped.find('\'', pos)) != std::string::npos) {
        escaped.insert(pos, "'");
        pos += 2;
    }

    return escaped;
}

std::string QueryBuilder::create_table(
    const model::Table& table)
{
    Logger::instance()->debug(
        "Building CREATE TABLE query for '{}'",
        table.name);

    std::string query =
        "CREATE TABLE IF NOT EXISTS " +
        table.name +
        " (";

    for (size_t i = 0; i < table.columns.size(); ++i) {

        const auto& col = table.columns[i];

        query += col.name;
        query += " ";
        query += to_sqlite_type(col.type);

        if (i + 1 < table.columns.size()) {
            query += ", ";
        }
    }

    query += ");";

    Logger::instance()->trace(
        "Generated CREATE TABLE query: {}",
        query);

    return query;
}

std::string QueryBuilder::insert_row(
    const std::string& table_name,
    const model::Table& table,
    const std::vector<std::string>& row)
{
    if (table.columns.size() != row.size()) {

        Logger::instance()->error(
            "INSERT query generation failed for table '{}': "
            "column count ({}) does not match row size ({})",
            table_name,
            table.columns.size(),
            row.size());

        throw ValidationException(
            "column count and row size must match");
    }

    Logger::instance()->debug(
        "Building INSERT query for table '{}'",
        table_name);

    std::string query =
        "INSERT INTO " +
        table_name +
        " (";

    for (size_t i = 0; i < table.columns.size(); ++i) {

        query += table.columns[i].name;

        if (i + 1 < table.columns.size()) {
            query += ", ";
        }
    }

    query += ") VALUES (";

    for (size_t i = 0; i < row.size(); ++i) {

        if (!row[i].empty()) {
            query += "'";
            query += escape_sql_string(row[i]);
            query += "'";
        }
        else
            query+="NULL";

        if (i + 1 < row.size()) {
            query += ", ";
        }
    }

    query += ");";

    Logger::instance()->trace(
        "Generated INSERT query: {}",
        query);

    return query;
}

}
