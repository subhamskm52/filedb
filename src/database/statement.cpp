#include "../../include/filedb/database/statement.h"

#include "filedb/logger/logger.h"
#include "filedb/exception.h"

namespace filedb {

Statement::Statement(sqlite3_stmt* stmt)
    : stmt_(stmt)
{
    Logger::instance()->trace("Statement created");
}

void Statement::bind(int ind, const std::string& val)
{
    int rc = sqlite3_bind_text(
        stmt_,
        ind,
        val.c_str(),
        -1,
        SQLITE_TRANSIENT);

    if (rc != SQLITE_OK)
    {
        std::string err =
            sqlite3_errmsg(sqlite3_db_handle(stmt_));

        Logger::instance()->error(
            "Failed to bind string parameter at index {}: {}",
            ind,
            err);

        throw DatabaseException(err);
    }

    Logger::instance()->trace(
        "Bound string parameter at index {}",
        ind);
}

void Statement::bind(int ind, double val)
{
    int rc = sqlite3_bind_double(stmt_, ind, val);

    if (rc != SQLITE_OK)
    {
        std::string err =
            sqlite3_errmsg(sqlite3_db_handle(stmt_));

        Logger::instance()->error(
            "Failed to bind double parameter at index {}: {}",
            ind,
            err);

        throw DatabaseException(err);
    }

    Logger::instance()->trace(
        "Bound double parameter at index {}",
        ind);
}

void Statement::bind(int ind, int val)
{
    int rc = sqlite3_bind_int(stmt_, ind, val);

    if (rc != SQLITE_OK)
    {
        std::string err =
            sqlite3_errmsg(sqlite3_db_handle(stmt_));

        Logger::instance()->error(
            "Failed to bind integer parameter at index {}: {}",
            ind,
            err);

        throw DatabaseException(err);
    }

    Logger::instance()->trace(
        "Bound integer parameter at index {}",
        ind);
}

void Statement::bindNull(int index)
{
    int rc = sqlite3_bind_null(stmt_, index);

    if (rc != SQLITE_OK)
    {
        std::string err =
            sqlite3_errmsg(sqlite3_db_handle(stmt_));

        Logger::instance()->error(
            "Failed to bind NULL parameter at index {}: {}",
            index,
            err);

        throw DatabaseException(err);
    }

    Logger::instance()->trace(
        "Bound NULL parameter at index {}",
        index);
}

bool Statement::next()
{
    int rc = sqlite3_step(stmt_);

    if (rc == SQLITE_DONE)
        return false;

    if (rc == SQLITE_ROW)
        return true;

    std::string err =
        sqlite3_errmsg(sqlite3_db_handle(stmt_));

    Logger::instance()->error(
        "Failed while iterating statement: {}",
        err);

    throw DatabaseException(err);
}

void Statement::reset()
{
    int rc = sqlite3_reset(stmt_);

    if (rc != SQLITE_OK)
    {
        std::string err =
            sqlite3_errmsg(sqlite3_db_handle(stmt_));

        Logger::instance()->error(
            "Failed to reset statement: {}",
            err);

        throw DatabaseException(err);
    }

    Logger::instance()->trace("Statement reset");
}

void Statement::execute()
{
    Logger::instance()->debug(
        "Executing prepared statement");

    int rc = sqlite3_step(stmt_);

    if (rc != SQLITE_DONE)
    {
        std::string err =
            sqlite3_errmsg(sqlite3_db_handle(stmt_));

        Logger::instance()->error(
            "Statement execution failed: {}",
            err);

        throw DatabaseException(err);
    }

    Logger::instance()->trace(
        "Statement executed successfully");
}

int Statement::getInt(int column) const
{
    return sqlite3_column_int(stmt_, column);
}

double Statement::getDouble(int column) const
{
    return sqlite3_column_double(stmt_, column);
}

std::string Statement::getString(int column) const
{
    const unsigned char* text =
        sqlite3_column_text(stmt_, column);

    if (text == nullptr)
        return "";

    return reinterpret_cast<const char*>(text);
}

Statement::~Statement()
{
    if (stmt_)
    {
        sqlite3_finalize(stmt_);
        stmt_ = nullptr;
    }
}

}