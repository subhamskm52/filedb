#include "filedb/importer/json-importer.h"

#include <set>
#include <filedb/logger/logger.h>
#include <filedb/exception.h>
#include <filedb/model/table.h>

#include "fstream"


namespace filedb::importer {
    model::DataType JsonImporter::get_data_type(const nlohmann::json &value) {
        using filedb::model::DataType;

        if (value.is_null())
            return DataType::Null;

        if (value.is_boolean())
            return DataType::Boolean;

        if (value.is_number_integer() || value.is_number_unsigned())
            return DataType::Integer;

        if (value.is_number_float())
            return DataType::Double;

        if (value.is_string())
            return DataType::String;

        // Arrays and objects don't map cleanly to any enum.
        if (value.is_array() || value.is_object())
            return DataType::String;

        return DataType::String;

    }

    std::string JsonImporter::read_json(const std::filesystem::path& file_path) {
        std::fstream json_stream(file_path);
        if (!json_stream.is_open()) {
            throw FileException("Unable to read json file: " + file_path.string());
        }

        std::stringstream json_buffer;
        json_buffer << json_stream.rdbuf();
        return json_buffer.str();

    }
    filedb::model::Table JsonImporter::import(const std::filesystem::path& file_path, std::string table_name) {
        Logger::instance()->info("Importing json file {} into table {}", file_path.string(), table_name);

        std::string json_string = read_json(file_path);

    // idea is if json is not homogeneous, take union of all key present and fill missing data as null in SQLITE table.

        nlohmann::json data = nlohmann::json::parse(json_string);

        std::set<std::pair<std::string, model::DataType>> columns{};
        for (const auto& row : data) {
            for (auto& [key, value] : row.items()) {
                columns.emplace(key, get_data_type(value));
            }
        }

        model::Table tbl{table_name, {}, {}};

        std::unordered_map<std::string, std::size_t> col_index;
        for (const auto&[name, type] : columns) {
            col_index[name] = tbl.columns.size();
                std::string filtered_col = name;
                filtered_col.erase(
                    std::remove_if(filtered_col.begin(), filtered_col.end(),
                    [](unsigned char c) {
                        return !(std::isalnum(c) || c == '_');
                    }
                )
            );
            tbl.columns.emplace_back(model::Column(filtered_col, type));
        }

        std::vector<std::vector<std::string>> rows;
        for (const auto& row: data) {
            std::vector<std::string> tbl_row{tbl.columns.size(), ""};
            for (auto& [key, value]: row.items()) {
                tbl_row[col_index[key]]=value.is_string()? value.get<std::string>(): value.dump();
            }
            rows.emplace_back(tbl_row);
        }

        tbl.rows = rows;

        return tbl;
    }

}
