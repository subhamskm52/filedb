#pragma once

#include <vector>
#include "column.h"
namespace filedb::model {

    class Table {
    public:
        std::vector<Column> columns;
        std::vector<std::vector<std::string>> rows;

        std::size_t row_count() const;
        std::size_t column_count() const;

        void rename_column(std::size_t index, const std::string& name);
        void set_column_type(std::size_t index, DataType type);
    };

}