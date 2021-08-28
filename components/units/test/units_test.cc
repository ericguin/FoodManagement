#include "CppUTest/TestHarness.h"

#include "units.hh"

#include <iostream>
#include <string>
#include <vector>

using U = Food::Units::Units;

TEST_GROUP(units)
{
    void printVector(std::vector<std::string>& v)
    {
        for (const std::string& s : v)
        {
            std::cout << s << std::endl;
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