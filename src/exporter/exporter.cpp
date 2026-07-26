#include "filedb/exporter/exporter.h"
#include "filedb/logger/logger.h"
#include "filedb/exception.h"

#include <fstream>

void filedb::exporter::Exporter::as_csv(
    const std::string& path)
{
    Logger::instance()->info(
        "Exporting table '{}' to CSV",
        tbl.name);

    std::ofstream file(
        path + "/" + tbl.name + ".csv");

    if (!file.is_open())
    {
        Logger::instance()->error(
            "Failed to create CSV file at '{}'",
            path);

        throw FileException(
            "Unable to create CSV file");
    }

    // Header
    for (size_t i = 0; i < tbl.columns.size(); ++i)
    {
        if (i)
            file << ",";

        file << tbl.columns[i].name;
    }

    file << '\n';

    // Rows
    for (const auto& row : tbl.rows)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            if (i)
                file << ",";

            file << row[i];
        }

        file << '\n';
    }

    if (!file.good())
    {
        Logger::instance()->error(
            "Failed while writing CSV file");

        throw FileException(
            "Failed while writing CSV file");
    }

    Logger::instance()->info(
        "Successfully exported {} rows to '{}'",
        tbl.rows.size(),
        path);
}

void filedb::exporter::Exporter::as_json(
    const std::string& path)
{
    Logger::instance()->warn(
        "JSON export not implemented");

    throw Exception(
        "JSON export not implemented");
}