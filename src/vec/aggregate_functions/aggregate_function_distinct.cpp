#include "vec/aggregate_functions/aggregate_function_distinct.h"

#include "vec/aggregate_functions/aggregate_function_combinator.h"
#include "vec/aggregate_functions/aggregate_function_simple_factory.h"
#include "vec/aggregate_functions/helpers.h"
#include "vec/common/typeid_cast.h"
// #include "registerAggregateFunctions.h"

namespace doris::vectorized {
namespace ErrorCodes {
extern const int NUMBER_OF_ARGUMENTS_DOESNT_MATCH;
}

class AggregateFunctionCombinatorDistinct final : public IAggregateFunctionCombinator {
public:
    DataTypes transformArguments(const DataTypes& arguments) const override {
        if (arguments.empty())
            throw Exception(
                    "Incorrect number of arguments for aggregate function with Distinct suffix",
                    ErrorCodes::NUMBER_OF_ARGUMENTS_DOESNT_MATCH);

        return arguments;
    }

    AggregateFunctionPtr transformAggregateFunction(const AggregateFunctionPtr& nested_function,
                                                    const DataTypes& arguments,
                                                    const Array& params) const override {
        AggregateFunctionPtr res;
        if (arguments.size() == 1) {
            res.reset(createWithNumericType<AggregateFunctionDistinct,
                                            AggregateFunctionDistinctSingleNumericData>(
                    *arguments[0], nested_function, arguments));

            if (res) return res;

            if (arguments[0]->isValueUnambiguouslyRepresentedInContiguousMemoryRegion())
                return std::make_shared<AggregateFunctionDistinct<
                        AggregateFunctionDistinctSingleGenericData<true>>>(nested_function,
                                                                           arguments);
            else
                return std::make_shared<AggregateFunctionDistinct<
                        AggregateFunctionDistinctSingleGenericData<false>>>(nested_function,
                                                                            arguments);
        }

        return std::make_shared<
                AggregateFunctionDistinct<AggregateFunctionDistinctMultipleGenericData>>(
                nested_function, arguments);
    }
};

// void registerAggregateFunctionCombinatorDistinct(AggregateFunctionCombinatorFactory & factory)
// {
//     factory.registerCombinator(std::make_shared<AggregateFunctionCombinatorDistinct>());
// }
} // namespace doris::vectorized
