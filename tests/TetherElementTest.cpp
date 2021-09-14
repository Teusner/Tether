#include <gtest/gtest.h>
#include "tether/TetherElement.hpp"

#include <math.h>
#include <memory>


namespace tether {
    class TetherElementTest : public ::testing::Test {
        public:
            virtual void SetUp() {
                tether_element = std::make_shared<TetherElement>(mass, volume, length);
            }
            std::double_t mass = 0.5;
            std::double_t volume = 0.1;
            std::double_t length = 0.02;
            std::shared_ptr<TetherElement> tether_element;
    };

    TEST_F(TetherElementTest, xTest) {
        EXPECT_EQ(tether_element->X(), 0);
    }

    TEST_F(TetherElementTest, yTest) {
        EXPECT_EQ(tether_element->Y(), 0);
    }

    TEST_F(TetherElementTest, zTest) {
        EXPECT_EQ(tether_element->Z(), 0);
    }

    TEST_F(TetherElementTest, thetaTest) {
        EXPECT_EQ(tether_element->Theta(), 0);
    }

    TEST_F(TetherElementTest, massTest) {
        EXPECT_EQ(tether_element->Mass(), mass);
    }

    TEST_F(TetherElementTest, volumeTest) {
        EXPECT_EQ(tether_element->Volume(), volume);
    }
    
    TEST_F(TetherElementTest, lengthTest) {
        EXPECT_EQ(tether_element->Length(), length);
    }

}; // namespace tether