#include "filedb/importer/CsvImporter.h"
#include <csv.hpp>
#include <filedb/model/table.h>

namespace filedb::importer {
     filedb::model::Table CsvImporter::import(const std::filesystem::path &file_path, std::string table_name) {
        try {
            if (!std::filesystem::exists(file_path)) {
                throw std::runtime_error(
                    "File does not exist: " + file_path.string()
                );
            }
            if (!std::filesystem::is_regular_file(file_path)) {
                throw std::runtime_error(
                    "Not a regular file: " + file_path.string()
                );
            }
            if (std::filesystem::is_empty(file_path)) {
                throw std::runtime_error(
                    "CSV file is empty: " + file_path.string()
                );
            }
            csv::CSVReader csv_file(file_path.string());


            std::vector<std::string> columns = csv_file.get_col_names();
            std::vector<std::vector<std::string>> rows {};
            for (csv::CSVRow& row: csv_file) {
                rows.emplace_back(row);
            }
            return filedb::model::Table{table_name,columns, rows};
        }
        catch (const std::filesystem::filesystem_error& e) {
            throw std::runtime_error(
                "Filesystem error while importing '" +
                file_path.string() + "': " + e.what()
            );
        }
        catch (const std::exception& e) {
            throw std::runtime_error(
                "Failed to import CSV '" +
                file_path.string() + "': " + e.what()
            );
        }
    }

}
