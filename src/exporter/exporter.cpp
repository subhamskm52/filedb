#include "filedb/exporter/exporter.h"
#include <fstream>

void filedb::exporter::Exporter::as_csv(const std::string& path) {

    std::string name = tbl.name;
    std::vector<filedb::model::Column> cols = tbl.columns;
    auto rows = tbl.rows;

    std::ofstream file(path +"/" + tbl.name);

    // Header
    for (size_t i = 0; i < cols.size(); ++i) {
        if (i) file << ",";
        file << cols[i].name;
    }
    file << "\n";

    // Rows
    for (const auto& row : rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (i) file << ",";
            file << row[i];
        }
        file << "\n";
    }
}

void filedb::exporter::Exporter::as_json(const std::string& path) {
    std::string name = tbl.name;
    std::vector<filedb::model::Column> cols = tbl.columns;
    auto rows = tbl.rows;
}

