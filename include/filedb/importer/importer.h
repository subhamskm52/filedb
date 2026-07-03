#pragma once
#include <__filesystem/filesystem_error.h>
#include "filedb/database/database.h"

namespace filedb::importer {
    class Importer {
    public:
        virtual void import(const std::filesystem::path& file_path, Database& db ) = 0;
        virtual ~Importer() = default;
    };
}
