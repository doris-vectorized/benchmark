#include "vec/Common/PODArray.h"
#include "vec/Common/PODArray_fwd.h"
#include "gtest/gtest.h"

namespace DB {
struct PODPoint {
  int x;
  int y;
};
TEST(PODArrayTest, PODArrayBasicTest) {
    using PODPointArray = PaddedPODArray<PODPoint>;
    PODPointArray point_array;
}
} // namespace DB

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
