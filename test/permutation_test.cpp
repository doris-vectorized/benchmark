#include "vec/columns/column_vector.h"

#include "gtest/gtest.h"

namespace doris::vectorized {
TEST(ColumnVectorTest, ColumnVectorTest) {
   auto column_vector_int32 = ColumnVector<Int32>::create()->getPtr();
   auto f1 = castToNearestFieldType(3);
   auto f2 = castToNearestFieldType(2);
   auto f3 = castToNearestFieldType(1);

   column_vector_int32->insert(f1);
   column_vector_int32->insertDefault();
   column_vector_int32->insert(f2);
   column_vector_int32->insert(f3);

   IColumn::Permutation perm;
   column_vector_int32->getPermutation(false, 4, 0, perm);
   auto column_vector_int32_sort = column_vector_int32->permute(perm, 4);

   assert(column_vector_int32_sort->size() == 4);
   assert(column_vector_int32_sort->getUInt(0) == 0);
   assert(column_vector_int32_sort->getUInt(1) == 1);
   assert(column_vector_int32_sort->getUInt(2) == 2);
   assert(column_vector_int32_sort->getUInt(3) == 3);

   column_vector_int32->getPermutation(true, 4, 0, perm);
   column_vector_int32_sort = column_vector_int32->permute(perm, 4);
   assert(column_vector_int32_sort->getUInt(0) == 3);
   assert(column_vector_int32_sort->getUInt(1) == 2);
   assert(column_vector_int32_sort->getUInt(2) == 1);
   assert(column_vector_int32_sort->getUInt(3) == 0);

   column_vector_int32->getPermutation(false, 2, 0, perm);
   column_vector_int32_sort = column_vector_int32->permute(perm, 2);
   assert(column_vector_int32_sort->size() == 2);
   assert(column_vector_int32_sort->getUInt(0) == 0);
   assert(column_vector_int32_sort->getUInt(1) == 1);

}
} // namespace DB

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}