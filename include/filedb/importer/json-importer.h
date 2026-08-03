#pragma once
#include "filedb/importer/importer.h"
#include "json.hpp"

namespace filedb::importer{
    class JsonImporter: public Importer{
    public:
        JsonImporter()=default;
        ~JsonImporter() override =default;

        filedb::model::Table import(const std::filesystem::path &file_path, std::string table_name) override;

    private:
        std::string read_json(const std::filesystem::path &path);
        model::DataType get_data_type(const nlohmann::json& value);
    };
}