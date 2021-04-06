#pragma once

#include <vec/AggregateFunctions/IAggregateFunction.h>
#include <vec/Core/Field.h>
#include <vec/DataTypes/IDataType.h>

#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <unordered_map>

namespace DB {

class AggregateFunctionSimpleFactory;
void registerAggregateFunctionSum(AggregateFunctionSimpleFactory& factory);
void registerAggregateFunctionCombinatorNull(AggregateFunctionSimpleFactory & factory);

using DataTypePtr = std::shared_ptr<const IDataType>;
using DataTypes = std::vector<DataTypePtr>;
using AggregateFunctionCreator =
        std::function<AggregateFunctionPtr(const std::string&, const DataTypes&, const Array&)>;

class AggregateFunctionSimpleFactory {
public:
    using Creator = AggregateFunctionCreator;

private:
    using AggregateFunctions = std::unordered_map<std::string, Creator>;

    AggregateFunctions aggregate_functions;
    AggregateFunctions nullable_aggregate_functions;

public:
    void registerFunction(const std::string& name, Creator creator, bool nullable = false) {
        if (nullable) {
            nullable_aggregate_functions[name] = creator;
        } else {
            aggregate_functions[name] = creator;
        }
    }

    AggregateFunctionPtr get(const std::string& name, const DataTypes& argument_types,
                             const Array& parameters) {
        bool nullable = false;
        for (const auto& type : argument_types) {
            if (type->isNullable()) {
                nullable = true;
            }
        }
        if (nullable) {
            return nullable_aggregate_functions[name](name, argument_types, parameters);
        } else {
            return aggregate_functions[name](name, argument_types, parameters);
        }
    }

public:
    static AggregateFunctionSimpleFactory& instance() {
        static std::once_flag oc;
        static AggregateFunctionSimpleFactory instance;
        std::call_once(oc, [&]() { 
            registerAggregateFunctionSum(instance); 
            registerAggregateFunctionCombinatorNull(instance);
        });
        return instance;
    }
};

}; // namespace DB
