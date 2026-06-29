#pragma once
#include <string>

#include "sqlite3.h"

namespace filedb {
    class Statement {
    public:
        Statement(sqlite3_stmt* stmt);
        ~Statement();

        Statement(const Statement&) = delete;
        Statement& operator=(const Statement&) = delete;

        void bind(int ind, int val);
        void bind(int ind, double val);
        void bind(int ind, const std::string& val);
        void bindNull(int index);

        bool next();
        void reset();
        void execute();

        int getInt(int column) const;
        double getDouble(int column) const;
        std::string getString(int column) const;

    private:
        sqlite3_stmt* stmt_ = nullptr;
    };

}