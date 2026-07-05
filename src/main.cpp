#include "filedb/database/database.h"
#include "filedb/importer/CsvImporter.h"
#include <filesystem>

int main() {
    filedb::Database db;

    std::cout << std::filesystem::current_path() << '\n';
    filedb::importer::CsvImporter importer;

    importer.import("abc.csv");

    return 0;
}
