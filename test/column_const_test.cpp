#include "gtest/gtest.h"
#include "vec/Columns/ColumnConst.h"
#include "vec/Columns/ColumnsNumber.h"

namespace DB {
TEST(ColumnConstTest, BasicTest) {
    auto c32 = ColumnInt32::create();
    c32->insertDefault();
    auto const_v32 = ColumnConst::create(c32->getPtr(), 4096);
    auto cc = const_v32->convertToFullColumnIfConst();
    ASSERT_EQ(cc->size(), (size_t)4096);
}
} // namespace DB

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
