#include "vec/Functions/abs.cpp"

#include "gtest/gtest.h"

namespace DB {

TEST(FunctionTest, AbsFunctionTest) {
    FunctionAbs function_abs;
    std::shared_ptr<IFunction> abs_function_ptr = function_abs.create();
    assert(abs_function_ptr->getName() == "abs");
}

} // namespace DB

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

