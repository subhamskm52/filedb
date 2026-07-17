#include "../../include/filedb/database/database.h"

namespace filedb {
    Database::~Database() {
        close();
    }

    void Database::open(const std::string& path) {
        connection_.open(path);
    }

    void Database::close() {
        connection_.close();
    }

    bool Database::isOpen() const {
        return connection_.is_open();
    }

    Statement Database::prepare(const std::string& sql) {
        return connection_.prepare(sql);
    }

    void Database::execute(const std::string& sql, int(*callback)(void*, int, char**, char**), void* first_arg_to_callback) {
        if (!connection_.is_open())
            throw std::runtime_error("Database Connection Closed");

        connection_.execute(sql, callback, first_arg_to_callback);
    }
}