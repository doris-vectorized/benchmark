#include "vec/common/exception.h"

#include "gtest/gtest.h"

namespace doris::vectorized {
TEST(ExceptionTest, ExceptionTest) {
    try {
        throw ErrnoException("haha", 1, 2);
    } catch (Exception& e) {
        auto st = e.getStackTrace().value();
        std::cerr << st << '\n';
        std::cout << e.what() << std::endl;
    }
}
} // namespace DB

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
