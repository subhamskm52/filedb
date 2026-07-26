#include "../../include/filedb/database/connection.h"

#include "filedb/exception.h"
#include "filedb/logger/Logger.h"

namespace filedb {

Connection::Connection() = default;

Connection::~Connection()
{
    if (db_)
    {
        sqlite3_close(db_);
        db_ = nullptr;
    }
}

void Connection::open(const std::string& db_name)
{
    Logger::instance()->info("Opening database '{}'", db_name);

    int rc = sqlite3_open(db_name.c_str(), &db_);

    if (rc != SQLITE_OK)
    {
        std::string error = sqlite3_errmsg(db_);

        Logger::instance()->error(
            "Failed to open database '{}': {}",
            db_name,
            error);

        sqlite3_close(db_);
        db_ = nullptr;

        throw DatabaseException(error);
    }

    Logger::instance()->info(
        "Connection successful to '{}'",
        db_name);
}

void Connection::close()
{
    if (!db_)
        return;

    Logger::instance()->debug("Closing database connection");

    int rc = sqlite3_close_v2(db_);

    if (rc != SQLITE_OK)
    {
        std::string err = sqlite3_errmsg(db_);

        Logger::instance()->error(
            "Failed to close database: {}",
            err);

        throw DatabaseException(err);
    }

    db_ = nullptr;

    Logger::instance()->info("Connection closed");
}

bool Connection::is_open() const
{
    return db_ != nullptr;
}

Statement Connection::prepare(const std::string& sql)
{
    if (!db_)
    {
        Logger::instance()->error(
            "Attempted to prepare statement on closed database");

        throw DatabaseException(
            "Database connection is not open");
    }

    sqlite3_stmt* stmt = nullptr;

    int rc = sqlite3_prepare(
        db_,
        sql.c_str(),
        -1,
        &stmt,
        nullptr);

    if (rc != SQLITE_OK)
    {
        std::string err = sqlite3_errmsg(db_);

        Logger::instance()->error(
            "Failed to prepare statement: {}",
            err);

        throw DatabaseException(err);
    }

    Logger::instance()->debug(
        "Statement prepared successfully");

    return Statement(stmt);
}

void Connection::execute(
    const std::string& sql,
    int (*callback)(void*, int, char**, char**),
    void* param_to_callback) const
{
    if (!db_)
    {
        Logger::instance()->error(
            "Attempted to execute query on closed database");

        throw DatabaseException(
            "Database connection is not open");
    }

    Logger::instance()->debug(
        "Executing SQL: {}",
        sql);

    char* err = nullptr;

    int rc = sqlite3_exec(
        db_,
        sql.c_str(),
        callback,
        param_to_callback,
        &err);

    if (rc != SQLITE_OK)
    {
        std::string error =
            err ? err : "Unknown SQLite error";

        Logger::instance()->error(
            "SQL execution failed: {}",
            error);

        sqlite3_free(err);

        throw DatabaseException(error);
    }

    Logger::instance()->trace(
        "SQL executed successfully");
}

}
