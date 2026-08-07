#include <iostream>

#include "filedb/database/database.h"
#include "filedb/database/query_builder.h"
#include "filedb/importer/json-importer.h"
#include "filedb/importer/CsvImporter.h"

int main() {
    filedb::Database db;
    db.open(":memory:");

    filedb::importer::JsonImporter jsonImporter;
    filedb::importer::CsvImporter csvImporter;

    auto products =
        jsonImporter.import(
            "../data/products.json",
            "products"
        );

    auto orders =
        csvImporter.import(
            "../data/orders.csv",
            "orders"
        );

    auto products_sql =
        filedb::QueryBuilder::create_table(products);

    auto orders_sql =
        filedb::QueryBuilder::create_table(orders);

    db.execute(products_sql, nullptr, nullptr);
    db.execute(orders_sql, nullptr, nullptr);

    for (const auto& row : products.rows) {
        auto sql =
            filedb::QueryBuilder::insert_row(
                "products",
                products,
                row
            );

        db.execute(sql, nullptr, nullptr);
    }

    for (const auto& row : orders.rows) {
        auto sql =
            filedb::QueryBuilder::insert_row(
                "orders",
                orders,
                row
            );

        db.execute(sql, nullptr, nullptr);
    }

    db.execute(
        R"(
    SELECT
        o.order_id,
        p.product_name,
        p.price,
        o.quantity
    FROM orders o
    LEFT JOIN products p
        ON o.product_id = p.id
    )",
        [](void*, int argc, char** argv, char** colNames) -> int {

            for (int i = 0; i < argc; ++i) {
                std::cout
                    << colNames[i]
                    << " = "
                    << (argv[i] ? argv[i] : "NULL")
                    << '\n';
            }

            std::cout << '\n';
            return 0;
        },
        nullptr
    );

    return 0;
}
