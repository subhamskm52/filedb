#pragma once
#include "importer.h"
#include "csv.hpp"

namespace filedb::importer {
    class CsvImporter : public Importer {
    public:
        CsvImporter() = default;
        ~CsvImporter() override = default;
        void import(const std::filesystem::path& file_path, Database& db) override;

    };
}