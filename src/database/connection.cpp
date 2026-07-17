#include "../../include/filedb/database/connection.h"

#include <iostream>

namespace filedb {
    Connection::Connection() = default;

    Connection::~Connection() {
        sqlite3_close(db_);
    }

    void Connection::open(const std::string& db_name ) {
        int rc = sqlite3_open(db_name.c_str(), &db_);
        if ( rc != SQLITE_OK) {
            std::string error = sqlite3_errmsg(db_);
            sqlite3_close(db_);
            db_ = nullptr;
            throw std::runtime_error(error);
        }
        std::cout<<"[S] Connection successful to " <<db_name<<std::endl;
    }

    void Connection::close() {
        int rc = sqlite3_close_v2(db_);
        if (rc != SQLITE_OK){
            std::string err = sqlite3_errmsg(db_);
            throw std::runtime_error(err);
        }
        db_ = nullptr;
        std::cout<<"[S] Connection closed"<<std::endl;
    }

    bool Connection::is_open() const {
        return db_ != nullptr;
    }

    Statement Connection::prepare(const std::string &sql) {
        sqlite3_stmt* stmt = nullptr;
        auto rc = sqlite3_prepare(db_,sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db_);
            std::cerr<<"[E] while preparing statement: "<<err<<std::endl;
            throw std::runtime_error(err);
        }
        return Statement(stmt);
    }

    void Connection::execute(const std::string& sql, int (*callback)(void*, int, char**, char**), void* param_to_callback ) const {
        char* err = nullptr;
        int rc = sqlite3_exec(db_, sql.c_str(), callback, param_to_callback, &err);

        if (rc != SQLITE_OK) {
            sqlite3_free(err);
        }

    }
}
