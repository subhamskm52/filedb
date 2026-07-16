#include "filedb/model/table.h"

#include <iostream>

namespace filedb::model {

    Table::Table(
        std::vector<std::string>& columns_,
        const std::vector<std::vector<std::string>>& rows_)
        : rows(rows_)
    {
        for (const auto& col : columns_) {
            columns.emplace_back(Column{col, DataType::String});
        }
    }

    std::size_t Table::row_count() const {
        return rows.size();
    }

    std::size_t Table::column_count() const {
        return columns.size();
    }

    void Table::rename_column(std::size_t index, const std::string& name) {
        if (index < columns.size()) {
            columns[index].name = name;
        }
    }

    void Table::set_column_type(std::size_t index, DataType type) {
        if (index < columns.size()) {
            columns[index].type = type;
        }
    }

    void Table::print() const {
        // Header
        for (std::size_t i = 0; i < columns.size(); ++i) {
            std::cout << columns[i].name;
            if (i + 1 < columns.size()) {
                std::cout << " | ";
            }
        }
        std::cout << '\n';

        // Separator
        for (std::size_t i = 0; i < columns.size(); ++i) {
            std::cout << "----------";
        }
        std::cout << '\n';

        // Rows
        for (const auto& row : rows) {
            for (std::size_t i = 0; i < row.size(); ++i) {
                std::cout << row[i];
                if (i + 1 < row.size()) {
                    std::cout << " | ";
                }
            }
            std::cout << '\n';
        }
    }

}