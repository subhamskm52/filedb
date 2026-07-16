#include "filedb/database/database.h"
#include "filedb/importer/CsvImporter.h"
#include <filesystem>

int main() {
    filedb::Database db;

    filedb::importer::CsvImporter importer;
    auto tbl = importer.import("abc.csv");
    tbl.print();
    return 0;
}
