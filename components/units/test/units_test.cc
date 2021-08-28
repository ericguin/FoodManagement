#include "CppUTest/TestHarness.h"

#include "units.hh"

#include <iostream>
#include <string>
#include <vector>

using U = Food::Units::Units;
using V = Food::Units::Value;

TEST_GROUP(units)
{
    void printVector(std::vector<std::string>& v)
    {
        for (const std::string& s : v)
        {
            std::cout << s << std::endl;
        }
    }

    void printVector(std::vector<V>& v)
    {
        for (auto& s : v)
        {
            std::cout << "Val: " << s.Val << " Units: " << (unsigned)s.Unit << std::endl;
        }
    }
    
    bool compareVecs(std::vector<std::string>& a, std::vector<std::string>& b)
    {
        CHECK_TEXT(a.size() == b.size(), "Vector sizes do not match");
        
        for (std::size_t i = 0; i < a.size(); i ++)
        {
            CHECK_TEXT(a[i] == b[i], "Contents do not match");
        }
        
        return true;
    }
};

TEST(units, SplitUnitString)
{
    // Vector all should split to
    std::vector<std::string> resultOfSplit{"yes", "no", "maybe"};
    
    // Test 1: Compare splitting on ;
    std::string testUnitStringWithSemicolons = "yes;no;maybe;";
    auto vec = Food::Units::SplitUnitString(testUnitStringWithSemicolons);
    compareVecs(vec, resultOfSplit);
    
    // Test 1: Compare splitting on space
    std::string testUnitStringWithSpaces = "yes no maybe ";
    vec = Food::Units::SplitUnitString(testUnitStringWithSpaces, ' ');
    compareVecs(vec, resultOfSplit);
}

TEST(units, CanUnitAGoToUnitB)
{
    CHECK(Food::Units::CanUnitAGoToUnitB(U::MASS_GRAMS, U::MASS_LBS));
    CHECK(Food::Units::CanUnitAGoToUnitB(U::MASS_GRAMS, U::VOLUME_CUPS) == false);
}

TEST(units, StringToUnit)
{
    std::string unitStringSuccess = "139 pounds";
    U res = Food::Units::StringToUnit(unitStringSuccess);
    CHECK(res == U::MASS_LBS);
    
    std::string unitSuccessTwo = "15 cups";
    res = Food::Units::StringToUnit(unitSuccessTwo);
    CHECK(res == U::VOLUME_CUPS);
    
    std::string badUnits = "yeet yote";
    res = Food::Units::StringToUnit(badUnits);
    CHECK(res == U::INVALID_UNITS);
}


TEST(units, NarrowDownConvertibleUnits)
{
    std::vector<std::string> split{"12 grams", "14 pounds", "3 cups"};

    auto ret = Food::Units::NarrowDownToConvertibleUnits(split, U::MASS_LBS);
}

TEST(units, ConvertUnitTo)
{
    V start{1, U::VOLUME_L};
    V convert = Food::Units::ConvertUnitTo(start, U::VOLUME_ML);
    CHECK(1000 == convert.Val);
}

TEST(units, WholeHog)
{
    std::string conglomerateUnits = "12 grams;14 pounds;";

    std::cout << Food::Units::ConvertAllTo(conglomerateUnits, U::MASS_LBS) << std::endl;
    std::cout << Food::Units::ConvertAllTo(conglomerateUnits, U::VOLUME_CUPS) << std::endl;
}