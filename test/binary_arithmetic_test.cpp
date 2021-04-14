#include <iostream>
#include <memory>
#include <string>

#include "vec/columns/column_vector.h"
#include "vec/functions/simple_function_factory.h"
#include "vec/data_types/data_types_number.h"
#include "gtest/gtest.h"


namespace doris::vectorized {

TEST(BinaryArithmeticTest, basic_test) {
    auto [column_vector_int32_1,column_vector_int32_2] = std::pair{ColumnVector<Int32>::create(), ColumnVector<Int32>::create()};
    for (int i = 0; i < 10; i++) {
        column_vector_int32_1->insert(castToNearestFieldType(i));
        column_vector_int32_2->insert(castToNearestFieldType(100 - i * 2));
    }

    DataTypePtr data_type1(std::make_shared<DataTypeInt32>());
    ColumnWithTypeAndName type_and_name1(column_vector_int32_1->getPtr(), data_type1, "a");
    ColumnWithTypeAndName type_and_name2(column_vector_int32_2->getPtr(), data_type1, "b");

    DataTypePtr data_type2(std::make_shared<DataTypeInt64>());
    ColumnWithTypeAndName type_and_name3(nullptr, data_type2, "a + b");

    auto plus_function = SimpleFunctionFactory::instance().get_function("add", {type_and_name1, type_and_name2});
    ColumnNumbers arguments{0, 1};
    Block block{type_and_name1, type_and_name2, type_and_name3};
    plus_function->execute(block, arguments, 2, 10, -1);

    int size = block.getByPosition(2).column->size();
    ASSERT_EQ(size, 10);
    auto data = ((ColumnVector<Int64>*)block.getByPosition(2).column.get());

    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(data->getInt(i), 100 - i);
    }

    auto minus_function = SimpleFunctionFactory::instance().get_function("subtract", {type_and_name1, type_and_name2});
    minus_function->execute(block, arguments, 2, 10, -1);

    size = block.getByPosition(2).column->size();
    ASSERT_EQ(size, 10);
    data = ((ColumnVector<Int64>*)block.getByPosition(2).column.get());
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(data->getInt(i), i * 3 - 100);
    }

    auto multiply_function = SimpleFunctionFactory::instance().get_function("multiply", {type_and_name1, type_and_name2});
    multiply_function->execute(block, arguments, 2, 10, -1);

    size = block.getByPosition(2).column->size();
    ASSERT_EQ(size, 10);
    data = ((ColumnVector<Int64>*)block.getByPosition(2).column.get());
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(data->getInt(i), i * (100 - i * 2));
    }

    auto divide_function = SimpleFunctionFactory::instance().get_function("divide", {type_and_name1, type_and_name2});
    DataTypePtr data_type3(std::make_shared<DataTypeFloat64>());
    block.insert({nullptr, data_type3, "a / b"});
    divide_function->execute(block, arguments, 3, 10, -1);

    size = block.getByPosition(3).column->size();
    ASSERT_EQ(size, 10);
    auto float_data = ((ColumnVector<Float64>*)block.getByPosition(3).column.get());
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(float_data->getFloat64(i), (double)i / (100 - i * 2));
    }

    auto int_divide_function = SimpleFunctionFactory::instance().get_function("int_divide", {type_and_name1, type_and_name2});
    block.insert({nullptr, data_type1, "a div b"});
    int_divide_function->execute(block, arguments, 4, 10, -1);

    size = block.getByPosition(4).column->size();
    ASSERT_EQ(size, 10);
    auto int32_data = ((ColumnVector<Int32>*)block.getByPosition(4).column.get());
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(int32_data->getInt(i), i / (100 - i * 2));
    }

    auto mod_function = SimpleFunctionFactory::instance().get_function("mod", {type_and_name1, type_and_name2});
    mod_function->execute(block, arguments, 4, 10, -1);

    size = block.getByPosition(4).column->size();
    ASSERT_EQ(size, 10);
    int32_data = ((ColumnVector<Int32>*)block.getByPosition(4).column.get());
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(int32_data->getInt(i), i % (100 - i * 2));
    }
}

} // namespace DB

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
