#pragma once
#include <string>
#include <mutex>
#include "vec/DataTypes/IDataType.h"
#include "vec/DataTypes/data_type_string.h"
#include "vec/DataTypes/DataTypeNothing.h"
#include "vec/DataTypes/DataTypesNumber.h"
#include "vec/DataTypes/DataTypesDecimal.h"

namespace DB
{
class DataTypeFactory {
    using DataTypeMap = std::unordered_map<std::string, DataTypePtr>;
public:
    static DataTypeFactory& instance() {
        static std::once_flag oc;
        static DataTypeFactory instance;
        std::call_once(oc, [&]() {
            instance.regist_data_type("UInt8", DataTypePtr(std::make_shared<DataTypeUInt8>()));
            instance.regist_data_type("UInt16", DataTypePtr(std::make_shared<DataTypeUInt16>()));
            instance.regist_data_type("UInt32", DataTypePtr(std::make_shared<DataTypeUInt32>()));
            instance.regist_data_type("UInt64", DataTypePtr(std::make_shared<DataTypeUInt64>()));
            instance.regist_data_type("Int8", DataTypePtr(std::make_shared<DataTypeInt8>()));
            instance.regist_data_type("Int16", DataTypePtr(std::make_shared<DataTypeInt16>()));
            instance.regist_data_type("Int32", DataTypePtr(std::make_shared<DataTypeInt32>()));
            instance.regist_data_type("Int64", DataTypePtr(std::make_shared<DataTypeInt64>()));
            instance.regist_data_type("Float32", DataTypePtr(std::make_shared<DataTypeFloat32>()));
            instance.regist_data_type("Float64", DataTypePtr(std::make_shared<DataTypeFloat64>()));

        });
        return instance;
    }
    DataTypePtr get(const std::string &name) {
        return _data_type_map[name];
    }
private:
    void regist_data_type(const std::string& name, DataTypePtr data_type) {
        _data_type_map.emplace(name, data_type);
    }
    DataTypeMap _data_type_map;
};
} // namespace DB

