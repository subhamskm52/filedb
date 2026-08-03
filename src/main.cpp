#include "filedb/database/database.h"
#include "filedb/importer/CsvImporter.h"
#include "filedb/database/query_builder.h"
#include "filedb/importer/json-importer.h"

int main() {
    filedb::Database db;
    db.open(":memory:");
    filedb::importer::JsonImporter importer;
    auto tbl = importer.import("./data/example.json", "example");
    tbl.print();

}
