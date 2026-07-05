#pragma once

namespace filedb::model {
    enum class DataType {
        Integer,
        Double,
        Boolean,
        String,
        Date,
        DateTime,
        Binary,
        Null
    };
}