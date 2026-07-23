#pragma once
#include "filedb/model/table.h"


namespace filedb::exporter {
    class Exporter {
    private:
        filedb::model::Table tbl;
    public:
        explicit Exporter(const filedb::model::Table& tbl_):tbl(tbl_){};
        ~Exporter() = default;
        void as_csv(const std::string& path);
        void as_json(const std::string& path);
    };
}
