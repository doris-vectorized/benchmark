#include "vec/Columns/ColumnString.h"

#include "gtest/gtest.h"

namespace DB {
TEST(ColumnStringTest, ColumnStringTest) {
   auto column_string = ColumnString::create();

   auto f1 = std::string("happen");
   auto f2 = std::string("lee");
   auto f3 = std::string("happen lee");

   column_string->insertData(f1.c_str(), f1.size());
   column_string->insertData(f2.c_str(), f2.size());
   column_string->insertData(f3.c_str(), f3.size());

   ASSERT_STREQ(f1.c_str(), column_string->getDataAt(0).toString().c_str());
   ASSERT_STREQ(f2.c_str(), column_string->getDataAt(1).toString().c_str());
   ASSERT_STREQ(f3.c_str(), column_string->getDataAt(2).toString().c_str());

}
} // namespace DB

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}