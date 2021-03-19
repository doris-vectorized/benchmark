#include "vec/Columns/ColumnVector.h"

#include "gtest/gtest.h"

namespace DB {
TEST(ColumnVectorTest, ColumnVectorTest) {
   auto column_vector_int32 = ColumnVector<Int32>::create();
   column_vector_int32->insertDefault();

   auto f1 = castToNearestFieldType(1);
   auto f2 = castToNearestFieldType(2);
   auto f3 = castToNearestFieldType(3);

   column_vector_int32->insert(f1);
   column_vector_int32->insert(f2);
   column_vector_int32->insert(f3);

   assert(column_vector_int32->size() == 4);
   assert(column_vector_int32->getUInt(0) == 0);
   assert(column_vector_int32->getUInt(1) == 1);
   assert(column_vector_int32->getUInt(2) == 2);
   assert(column_vector_int32->getUInt(3) == 3);
}
} // namespace DB

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
