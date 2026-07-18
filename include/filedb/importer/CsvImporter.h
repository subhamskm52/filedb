#pragma once
#include "importer.h"
#include "csv.hpp"
#include "filedb/model/table.h"

namespace filedb::importer {
    class CsvImporter : public Importer {
    public:
        CsvImporter() = default;
        ~CsvImporter() override = default;
         filedb::model::Table import(const std::filesystem::path& file_path, std::string table_name) override;
    };
}
