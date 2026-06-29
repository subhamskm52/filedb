#include <iostream>

#include "../include/filedb/database/database.h"

int main() {
    filedb::Database db;

    db.open(":memory:");

    db.execute(R"(
        CREATE TABLE users(
            id INTEGER,
            name TEXT
        );
    )");

    {
        auto stmt = db.prepare(
            "INSERT INTO users(id, name) VALUES(?, ?);"
        );

        stmt.bind(1, 1);
        stmt.bind(2, "Alice");
        stmt.execute();
    }

    {
        auto stmt = db.prepare(
            "INSERT INTO users(id, name) VALUES(?, ?);"
        );

        stmt.bind(1, 2);
        stmt.bind(2, "Bob");
        stmt.execute();
    }

    auto stmt = db.prepare(
        "SELECT id, name FROM users;"
    );

    while (stmt.next()) {
        std::cout
            << stmt.getInt(1)
            << " "
            << stmt.getString(1)
            << '\n';
    }

    db.close();

    return 0;
}