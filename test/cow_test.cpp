#include <iostream>
#include <string>

#include "Common/COW.h"
#include "gtest/gtest.h"

class Ref : public COW<Ref> {
public:
    friend class COW<Ref>;
    Ref() { std::cout << "contruction call" << std::endl; }
    Ref(const Ref&& other) { std::cout << "move contruction" << std::endl; }
    Ref(const Ref& other) { std::cout << "copy contruction" << std::endl; }
    virtual ~Ref() = default;
    virtual Ref::MutablePtr clone() const = 0;
};

class ConcreteObject : public COWHelper<Ref, ConcreteObject> {
public:
    friend class COWHelper<Ref, ConcreteObject>;

public:
};

TEST(COWTest, basic_test) {
    // test implement interface
    auto ptr = ConcreteObject::create();
    auto ptr2 = ptr->getPtr();
    auto newx = std::move(*ptr).mutate();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
