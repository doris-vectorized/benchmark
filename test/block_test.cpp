#include "Core/Block.h"
#include "Columns/ColumnVector.h"
#include "DataTypes/DataTypesNumber.h"

#include "Core/BlockInfo.h"
#include "gtest/gtest.h"

namespace DB {
TEST(BlockTest, BlockInfoTest) {
    BlockInfo info;
}

TEST(BlockTest, BlockMissingValuesTest) {
    BlockMissingValues bmv;
    bmv.setBit(1, 1);
    bmv.setBit(1, 2);
    BlockMissingValues::RowsBitMask mask = bmv.getDefaultsBitmask(1);
    ASSERT_EQ(mask[1], true);
    ASSERT_EQ(mask[2], true);
    ASSERT_EQ(mask[0], false);
}
TEST(BlockTest, BlockBasicTest) {
    auto vec = ColumnVector<Int32>::create();

    // reference to DataTypesNumber.cpp
    DataTypePtr data_type(std::make_shared<DataTypeInt32>());
    ColumnWithTypeAndName type_and_name(vec->getPtr(), data_type, "echo");
    Block block({type_and_name});
}
} // namespace DB

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
