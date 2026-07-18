#pragma once
#include <__filesystem/filesystem_error.h>
#include "filedb/database/database.h"
#include "filedb/model/table.h"

namespace filedb::importer {
    class Importer {
    public:
        virtual  filedb::model::Table import(const std::filesystem::path& file_path, std::string table_name) = 0;
        virtual ~Importer() = default;
    };
}
