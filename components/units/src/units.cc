#include "units.hh"

#include "boolinq.h"

#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <sstream>

namespace
{
    using Units = Food::Units::Units;

    std::map<Units, std::vector<std::string>> UnitNames = {
        {Units::MASS_GRAMS, {"g","grams"}},
        {Units::MASS_LBS, {"pounds","lbs","lb"}},
        {Units::VOLUME_CUPS, {"cup","c"}},
        {Units::VOLUME_ML, {"ml","milliliters"}},
        {Units::VOLUME_L, {"liters","l"}}
    };
    
    const std::map<Units, const std::map<Units, double const>> ConversionRates = {
        {Units::MASS_GRAMS, {
            {Units::MASS_LBS, 0.002204623}
        }},
        {Units::MASS_LBS, {
            {Units::MASS_GRAMS, 453.5924}
        }},
        {Units::VOLUME_CUPS, {
            {Units::VOLUME_ML, 236.5875},
            {Units::VOLUME_L, 0.2365875}
        }},
        {Units::VOLUME_ML, {
            {Units::VOLUME_CUPS, 0.004226766},
            {Units::VOLUME_L, 0.001}
        }},
        {Units::VOLUME_L, {
            {Units::VOLUME_CUPS, 4.226766},
            {Units::VOLUME_ML, 1000}
        }}
    };
    
}

namespace Food
{
    namespace Units
    {
        std::vector<std::string> SplitUnitString(std::string &str, char split)
        {
            std::vector<std::string> ret;
            std::string part;
            std::istringstream stream(str);

            while (std::getline(stream, part, split))
            {
                ret.push_back(part);
            }

            return ret;
        }

        bool CanUnitAGoToUnitB(Units A, Units B)
        {
            if (ConversionRates.count(A))
            {
                auto rates = ConversionRates.at(A);
                return rates.count(B);
            }

            return false;
        }

        Units StringToUnit(std::string &part)
        {
            std::string unit_str = *SplitUnitString(part, ' ').end();
            auto ret = boolinq::from(UnitNames)
                           .first([unit_str](std::pair<Units, std::vector<std::string>> l)
                                  { return boolinq::from(l.second).contains(unit_str); });
            return ret.first;
        }

        std::vector<std::string> NarrowDownToConvertibleUnits(std::vector<std::string> &split, Units to)
        {
            return std::vector<std::string>{};
        }

        std::vector<double> AcquireConvertibleUnitsAndConvertToTarget(std::string &str, Units to)
        {
            return std::vector<double>{};
        }

        double ConvertAllTo(std::string str, Units to)
        {
        }
    }
}