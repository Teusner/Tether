#include <gtest/gtest.h>
#include "Tether.hpp"

#include <math.h>
#include <memory>
#include <eigen3/Eigen/Dense>


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
            Eigen::Vector3d Xhead = Eigen::Vector3d(-5, 3, 1);
            Eigen::Vector3d Xtail = Eigen::Vector3d(5, 3, 1);
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
    }

    TEST_F(TetherTestConstructor2, XTailTest) {
        EXPECT_EQ(tether->Tail()->X(), 5);
        EXPECT_EQ(tether->Tail()->Y(), 3);
        EXPECT_EQ(tether->Tail()->Z(), 1);
    }

}; // namespace tether