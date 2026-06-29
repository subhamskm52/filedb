#pragma once

#pragma once

#include <string>

#include "connection.h"
#include "statement.h"

namespace filedb {

    class Database {
    public:
        Database() = default;
        ~Database() = default;

        void open(const std::string& path);
        void close();

        bool isOpen() const;

        void execute(const std::string& sql);

        Statement prepare(const std::string& sql);

    private:
        Connection connection_;
    };

} // namespace filedb