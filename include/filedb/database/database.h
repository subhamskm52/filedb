#pragma once

#pragma once

#include <string>

#include "connection.h"
#include "statement.h"

namespace filedb {

    class Database {
    public:
        Database() = default;
        ~Database();

        void open(const std::string& path);
        void close();

        bool isOpen() const;

        void execute(const std::string &sql, int (*callback)(void*, int, char**, char**), void *first_arg_to_callback);

        Statement prepare(const std::string& sql);

    private:
        Connection connection_;
    };

} // namespace filedb