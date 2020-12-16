#include "measure.hpp"

#include "gtest/gtest.h"
#include <cstdint>
#include <ratio>

constexpr auto KEPSILON = 1E-6;

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Measure_Constructor, DefaultInitialization)
{
    usu::measure<std::ratio<1, 1>> empty1;
    usu::measure<std::ratio<2, 1>, double> empty2;
    usu::measure<std::ratio<1, 2>, std::uint32_t> empty3;

    EXPECT_EQ(empty1.count(), 0);
    EXPECT_EQ(empty2.count(), 0);
    EXPECT_EQ(empty3.count(), 0u);
}

TEST(Measure_Constructor, OverloadInitialization)
{
    usu::measure<std::ratio<1, 1>> one(1);
    usu::measure<std::ratio<2, 1>, double> two(2.2);
    usu::measure<std::ratio<1, 2>, std::uint32_t> three(3);

    EXPECT_EQ(one.count(), 1);
    EXPECT_EQ(two.count(), 2.2);
    EXPECT_EQ(three.count(), 3u);
}

TEST(Measure_Operators, Relational)
{
    usu::millimeter mm1000(1000);
    usu::millimeter mm500(500);

    usu::meter m1(1);
    usu::meter m1_2(0.5);

    EXPECT_TRUE(mm1000 == m1);
    EXPECT_TRUE(mm500 == m1_2);
    EXPECT_FALSE(mm1000 == m1_2);
    EXPECT_FALSE(mm500 == m1);

    EXPECT_TRUE(mm1000 != mm500);
    EXPECT_TRUE(mm1000 != m1_2);
    EXPECT_TRUE(m1 != m1_2);
    EXPECT_TRUE(m1 != mm500);

    EXPECT_TRUE(mm1000 > mm500);
    EXPECT_TRUE(m1 > mm500);
    EXPECT_TRUE(mm1000 > m1_2);
    EXPECT_TRUE(m1 > mm500);

    EXPECT_FALSE(mm1000 < mm500);
    EXPECT_FALSE(m1 < mm500);
    EXPECT_FALSE(mm1000 < m1_2);
    EXPECT_FALSE(m1 < mm500);

    EXPECT_TRUE(mm500 < mm1000);
    EXPECT_TRUE(mm500 < m1);
    EXPECT_TRUE(m1_2 < mm1000);
    EXPECT_TRUE(mm500 < m1);
}

TEST(Masure_Operators, Mathematical_Addition)
{
    usu::inch inches2(2);
    usu::inch inches4(4);

    usu::feet feet1(1.1);
    usu::feet feet3(3.3);

    usu::inch inches6 = inches2 + inches4;
    EXPECT_EQ(inches6.count(), 6);

    usu::feet feet4 = feet1 + feet3;
    EXPECT_NEAR(feet4.count(), 4.4, KEPSILON);
}

TEST(Masure_Operators, Mathematical_Subtraction)
{
    usu::inch inches2(2);
    usu::inch inches4(4);

    usu::feet feet1(1.1);
    usu::feet feet3(3.3);

    usu::inch inchesResult = inches4 - inches2;
    EXPECT_EQ(inchesResult.count(), 2);

    usu::feet feetResult = feet3 - feet1;
    EXPECT_NEAR(feetResult.count(), 2.2, KEPSILON);
}

TEST(Measure_Operators, Mathematical_Multiplication)
{
    usu::inch inches1(1);

    usu::inch inches4 = inches1 * 4;
    EXPECT_EQ(inches4.count(), 4);

    usu::inch inches6 = 6 * inches1;
    EXPECT_EQ(inches6.count(), 6);

    usu::feet feet1(1.1);

    usu::feet feet4 = feet1 * 4.4;
    EXPECT_NEAR(feet4.count(), 4.84, KEPSILON);

    usu::feet feet6 = 6.6 * feet1;
    EXPECT_NEAR(feet6.count(), 7.26, KEPSILON);
}

TEST(Measure_Cast, Measure_Cast)
{
    usu::millimeter mm(10'000);
    usu::centimeter cm = usu::measure_cast<usu::centimeter>(mm);
    usu::meter m = usu::measure_cast<usu::meter>(mm);
    usu::kilometer km = usu::measure_cast<usu::kilometer>(mm);
    usu::inch in = usu::measure_cast<usu::inch>(mm);
    usu::feet ft = usu::measure_cast<usu::feet>(mm);
    usu::yard yd = usu::measure_cast<usu::yard>(mm);
    usu::mile mi = usu::measure_cast<usu::mile>(mm);
    usu::league lg = usu::measure_cast<usu::league>(mm);

    EXPECT_EQ(mm.count(), 10'000);
    EXPECT_EQ(cm.count(), 1'000);
    EXPECT_EQ(m.count(), 10);
    EXPECT_NEAR(km.count(), 0.01, KEPSILON);
    EXPECT_NEAR(in.count(), 393.70078740, KEPSILON);
    EXPECT_NEAR(ft.count(), 32.80839895, KEPSILON);
    EXPECT_NEAR(yd.count(), 10.93613298, KEPSILON);
    EXPECT_NEAR(mi.count(), 0.00621371, KEPSILON);
    EXPECT_NEAR(lg.count(), 0.00207123, KEPSILON);
}
