#include "vec/Columns/ColumnDecimal.h"

#include "gtest/gtest.h"

namespace DB {
TEST(ColumnDecimalTest, ColumnDecimalTest) {
   auto column_decimal_vector = ColumnDecimal<Decimal128>::create(4, 9);
   column_decimal_vector->insertDefault();

   __int128 f1 = 1;
   __int128 f2 = 2;
   __int128 f3 = 3;

   column_decimal_vector->insertData((const char*)&f1, sizeof(__int128));
   column_decimal_vector->insertData((const char*)&f2, sizeof(__int128));
   column_decimal_vector->insertData((const char*)&f3, sizeof(__int128));
}
} // namespace DB

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

