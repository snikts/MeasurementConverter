#include "measure.hpp"

#include <iomanip>
#include <iostream>
#include <string>

template <typename Left, typename Right>
void testRelationship(std::string title, Left lhs, Right rhs)
{
    std::cout << title << std::endl;
    // Test for equality
    if (lhs == rhs)
    {
        std::cout << "lhs == rhs" << std::endl;
    }
    if (lhs != rhs)
    {
        std::cout << "lhs != rhs" << std::endl;
    }
    if (lhs < rhs)
    {
        std::cout << "lhs < rhs" << std::endl;
    }
    if (lhs > rhs)
    {
        std::cout << "lhs > rhs" << std::endl;
    }
    std::cout << std::endl;
}

// ------------------------------------------------------------------
//
// Operator overloading, various constructors, more templates, etc
//
// ------------------------------------------------------------------
int main()
{
    // Basic declarations and measure_cast
    {
        usu::millimeter mm(10000);
        usu::centimeter cm = usu::measure_cast<usu::centimeter>(mm);
        usu::meter m = usu::measure_cast<usu::meter>(mm);
        usu::kilometer km = usu::measure_cast<usu::kilometer>(mm);
        usu::inch in = usu::measure_cast<usu::inch>(mm);
        usu::feet ft = usu::measure_cast<usu::feet>(mm);
        usu::yard yd = usu::measure_cast<usu::yard>(mm);
        usu::mile mi = usu::measure_cast<usu::mile>(mm);
        usu::league lg = usu::measure_cast<usu::league>(mm);

        std::cout << std::fixed << std::setprecision(8);
        std::cout << "-- Using measure_cast to convert From 10,000 millimeters --" << std::endl;
        std::cout << "millimeters : " << mm.count() << std::endl;
        std::cout << "centimeters : " << cm.count() << std::endl;
        std::cout << "meters      : " << m.count() << std::endl;
        std::cout << "kilometers  : " << km.count() << std::endl;
        std::cout << "inches      : " << in.count() << std::endl;
        std::cout << "feet        : " << ft.count() << std::endl;
        std::cout << "yard        : " << yd.count() << std::endl;
        std::cout << "mile        : " << mi.count() << std::endl;
        std::cout << "leagues     : " << lg.count() << std::endl;
        std::cout << std::endl;
    }

    // Various relational operators
    {
        testRelationship("--- Comparing 1 meter to 1,000 millimeters ---", usu::meter(1), usu::millimeter(1000));
        testRelationship("--- Comparing 2 meters to 1,000 millimeters ---", usu::meter(2), usu::millimeter(1000));
        testRelationship("--- Comparing 2 meters to 4,000 millimeters ---", usu::meter(2), usu::millimeter(4000));

        testRelationship("--- Comparing 1 inch to 10 millimeters ---", usu::inch(1), usu::millimeter(10));
        testRelationship("--- Comparing 2 inches to 10 millimeters ---", usu::inch(2), usu::millimeter(10));
        testRelationship("--- Comparing 2 inches to 100 millimeters ---", usu::inch(2), usu::millimeter(100));
    }

    // Adding of measures
    {
        std::cout << std::fixed << std::setprecision(2);

        usu::inch in(1);
        auto resultInches = in + usu::inch(2);
        std::cout << "1 inch + 2 inches = " << resultInches.count() << " inches" << std::endl;

        usu::yard yd(2);
        auto resultYards = usu::yard(6) - yd;
        std::cout << "6 yards - 2 yards = " << resultYards.count() << " yards" << std::endl;
    }

    // Scalar multiplications
    {
        std::cout << std::fixed << std::setprecision(2);

        usu::meter m(2.4);
        auto resultMeters = m * 2.2;
        std::cout << "2.4 meters * 2.2 = " << resultMeters.count() << " meters" << std::endl;

        usu::mile mi(6.2);
        auto resultMiles = 4.0 * mi;
        std::cout << "4.0 * 6.2 miles = " << resultMiles.count() << " miles" << std::endl;
    }

    return 0;
}
