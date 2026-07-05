#pragma once

#include <string>

#include "datatype.h"

namespace filedb::model {

    struct Column {
        std::string name;
        DataType type = DataType::String;
    };

}