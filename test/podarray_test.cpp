#include "vec/common/pod_array.h"
#include "vec/common/pod_array_fwd.h"
#include "gtest/gtest.h"

namespace doris::vectorized {
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
