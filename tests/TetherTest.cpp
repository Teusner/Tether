#include <gtest/gtest.h>
#include "tether/Tether.hpp"

#include <math.h>
#include <memory>


namespace tether {
    class TetherTestConstructor1 : public ::testing::Test {
        public:
            virtual void SetUp() {
                tether = std::make_shared<Tether>(length, n);
            }
            std::double_t length = 10;
            std::size_t n = 100;
            std::shared_ptr<Tether> tether;
    };

    class TetherTestConstructor2 : public ::testing::Test {
        public:
            virtual void SetUp() {
                tether = std::make_shared<Tether>(length, n, Xhead, Xtail);
            }
            std::double_t length = 10;
            std::size_t n = 100;
            ignition::math::Vector4d Xhead = ignition::math::Vector4d(-5, 3, 1, 0);
            ignition::math::Vector4d Xtail = ignition::math::Vector4d(5, 3, 1, 0);
            std::shared_ptr<Tether> tether;
    };

    TEST_F(TetherTestConstructor1, lengthTest) {
        EXPECT_EQ(tether->Length(), 10);
    }

    TEST_F(TetherTestConstructor1, nTest) {
        EXPECT_EQ(tether->N(), 100);
    }

    TEST_F(TetherTestConstructor2, lengthTest) {
        EXPECT_EQ(tether->Length(), 10);
    }

    TEST_F(TetherTestConstructor2, nTest) {
        EXPECT_EQ(tether->N(), 100);
    }

    TEST_F(TetherTestConstructor2, XHeadTest) {
        EXPECT_EQ(tether->Head()->X(), -5);
        EXPECT_EQ(tether->Head()->Y(), 3);
        EXPECT_EQ(tether->Head()->Z(), 1);
        EXPECT_EQ(tether->Head()->Theta(), 0);
    }

    TEST_F(TetherTestConstructor2, XTailTest) {
        EXPECT_EQ(tether->Tail()->X(), 5);
        EXPECT_EQ(tether->Tail()->Y(), 3);
        EXPECT_EQ(tether->Tail()->Z(), 1);
        EXPECT_EQ(tether->Tail()->Theta(), 0);
    }

}; // namespace tether