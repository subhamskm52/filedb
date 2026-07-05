#include "filedb/importer/CsvImporter.h"
#include <csv.hpp>

namespace filedb::importer {
    void CsvImporter::import(const std::filesystem::path& file_path) {
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

            for (csv::CSVRow& row : csv_file) {
                for (csv::CSVField& field : row) {
                    std::cout << field.get() << '\n';
                }
            }
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
