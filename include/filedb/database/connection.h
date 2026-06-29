#pragma once
#include <string>

#include "sqlite3.h"
#include "statement.h"

namespace filedb {

class Connection {
public:
    Connection();
    ~Connection();

    Connection(const Connection& ) = delete;
    Connection& operator=(const Connection&) = delete;

    void open(const std::string&);
    void close();
    bool is_open() const;
    Statement prepare(const std::string&);

    void execute(const std::string&, int (*callback)(void*, int, char**, char**), void*) const;

private:
    sqlite3* db_ = nullptr;
};

}
