#include "../../include/filedb/database/database.h"

namespace filedb {
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
        connection_.execute(sql, callback, first_arg_to_callback);
    }
}