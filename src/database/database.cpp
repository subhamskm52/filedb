#include "filedb/database/database.h"
#include "filedb/exception.h"
#include "filedb/logger/Logger.h"

namespace filedb {

Database::~Database()
{
    try
    {
        close();
    }
    catch (...)
    {
        Logger::instance()->error(
            "Exception while closing database in destructor");
    }
}

void Database::open(const std::string& path)
{
    Logger::instance()->debug(
        "Opening database '{}'", path);

    try
    {
        connection_.open(path);

        Logger::instance()->info(
            "Database '{}' opened successfully", path);
    }
    catch (const std::exception& e)
    {
        Logger::instance()->error(
            "Failed to open database '{}': {}", path, e.what());

        throw DatabaseException(
            std::string("Failed to open database: ") + e.what());
    }
}

void Database::close()
{
    if (!connection_.is_open())
        return;

    Logger::instance()->debug("Closing database");

    connection_.close();

    Logger::instance()->info("Database closed");
}

bool Database::isOpen() const
{
    return connection_.is_open();
}

Statement Database::prepare(const std::string& sql)
{
    if (!connection_.is_open())
    {
        Logger::instance()->error(
            "Attempted to prepare statement on closed database");

        throw DatabaseException(
            "Database connection is closed");
    }

    Logger::instance()->debug(
        "Preparing statement: {}", sql);

    return connection_.prepare(sql);
}

void Database::execute(
    const std::string& sql,
    int(*callback)(void*, int, char**, char**),
    void* first_arg_to_callback)
{
    if (!connection_.is_open())
    {
        Logger::instance()->error(
            "Attempted to execute query on closed database");

        throw DatabaseException(
            "Database connection is closed");
    }

    Logger::instance()->debug(
        "Executing SQL: {}", sql);

    try
    {
        connection_.execute(
            sql,
            callback,
            first_arg_to_callback);

        Logger::instance()->trace(
            "SQL execution completed");
    }
    catch (const std::exception& e)
    {
        Logger::instance()->error(
            "SQL execution failed: {}", e.what());

        throw DatabaseException(
            std::string("SQL execution failed: ") + e.what());
    }
}

}