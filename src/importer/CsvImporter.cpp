#include "filedb/importer/CsvImporter.h"

#include <csv.hpp>
#include <filedb/model/table.h>
#include <filedb/logger/logger.h>
#include <filedb/exception.h>

namespace filedb::importer {

filedb::model::Table CsvImporter::import(
    const std::filesystem::path& file_path,
    std::string table_name)
{
    Logger::instance()->info(
        "Importing CSV '{}' into table '{}'",
        file_path.string(),
        table_name);

    try
    {
        if (!std::filesystem::exists(file_path))
        {
            Logger::instance()->error(
                "CSV file does not exist: {}",
                file_path.string());

            throw FileException(
                "File does not exist: " + file_path.string());
        }

        if (!std::filesystem::is_regular_file(file_path))
        {
            Logger::instance()->error(
                "Not a regular file: {}",
                file_path.string());

            throw FileException(
                "Not a regular file: " + file_path.string());
        }

        if (std::filesystem::is_empty(file_path))
        {
            Logger::instance()->error(
                "CSV file is empty: {}",
                file_path.string());

            throw FileException(
                "CSV file is empty: " + file_path.string());
        }

        csv::CSVReader csv_file(file_path.string());

        std::vector<std::string> columns =
            csv_file.get_col_names();

        for (auto& column : columns) {
            column.erase(
                std::remove_if(column.begin(), column.end(),
                    [](unsigned char c) {
                        return !(std::isalnum(c) || c=='_');
                    }
                    )
                );
        }


        Logger::instance()->debug(
            "Detected {} columns in CSV",
            columns.size());

        std::vector<std::vector<std::string>> rows;

        for (csv::CSVRow& row : csv_file)
        {
            rows.emplace_back(row);
        }

        Logger::instance()->info(
            "Imported CSV successfully ({} rows, {} columns)",
            rows.size(),
            columns.size());

        return filedb::model::Table{
            table_name,
            columns,
            rows
        };
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        Logger::instance()->error(
            "Filesystem error while importing '{}': {}",
            file_path.string(),
            e.what());

        throw FileException(
            "Filesystem error while importing '" +
            file_path.string() +
            "': " +
            e.what());
    }
    catch (const std::exception& e)
    {
        Logger::instance()->error(
            "Failed to import CSV '{}': {}",
            file_path.string(),
            e.what());

        throw Exception(
            "Failed to import CSV '" +
            file_path.string() +
            "': " +
            e.what());
    }
}

}