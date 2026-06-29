#include "../../include/filedb/database/statement.h"

namespace filedb {
    Statement::Statement(sqlite3_stmt* stmt):stmt_(stmt){}

    void Statement::bind(int ind, const std::string &val) {
        int rc = sqlite3_bind_text(stmt_, ind, val.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(sqlite3_db_handle(stmt_)));
        }
    }

    void Statement::bind(int ind, double val) {
        int rc = sqlite3_bind_double(stmt_, ind, val);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(sqlite3_db_handle(stmt_)));
        }
    }

    void Statement::bind(int ind, int val) {
        int rc = sqlite3_bind_int(stmt_, ind, val);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(sqlite3_db_handle(stmt_)));
        }
    }

    void Statement::bindNull(int index) {
        int rc = sqlite3_bind_null(stmt_, index);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(sqlite3_db_handle(stmt_)));
        }
    }

    bool Statement::next() {
        int rc = sqlite3_step(stmt_);
        if (rc == SQLITE_DONE) return false;
        if (rc == SQLITE_ROW) return true;

        throw std::runtime_error(
            sqlite3_errmsg(sqlite3_db_handle(stmt_))
        );
    }

    void Statement::reset() {
        int rc = sqlite3_reset(stmt_);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(
                sqlite3_errmsg(sqlite3_db_handle(stmt_))
            );
        }
    }

    void Statement::execute() {
        int rc = sqlite3_step(stmt_);

        if (rc != SQLITE_DONE) {
            throw std::runtime_error(
                sqlite3_errmsg(sqlite3_db_handle(stmt_))
            );
        }
    }

    int Statement::getInt(int column) const {
        return sqlite3_column_int(stmt_, column);
    }

    double Statement::getDouble(int column) const {
        return sqlite3_column_double(stmt_, column);
    }

    std::string Statement::getString(int column) const {
        const unsigned char* text = sqlite3_column_text(stmt_, column);

        if (text == nullptr) {
            return "";
        }

        return reinterpret_cast<const char*>(text);
    }

    Statement::~Statement() {
        sqlite3_finalize(stmt_);
    }

}
