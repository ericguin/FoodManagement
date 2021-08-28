#include "units.hh"

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
        {Units::VOLUME_CUPS, {"c","cups"}},
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
            if (A == B)
            {
                return true;
            }

            if (ConversionRates.count(A))
            {
                auto rates = ConversionRates.at(A);
                return rates.count(B);
            }

            return false;
        }
        
        double UnitAToUnitBConversionRate(Units A, Units B)
        {
            if (A == B)
            {
                return 1;
            }

            if (CanUnitAGoToUnitB(A, B))
            {
                return ConversionRates.at(A).at(B);
            }

            return 0;
        }

        Units StringToUnit(std::string &part)
        {
            std::string unit_str = *(SplitUnitString(part, ' ').end() - 1);
            
            for (auto& pair : UnitNames)
            {
                for (auto& str : pair.second)
                {
                    if (str == unit_str)
                    {
                        return pair.first;
                    }
                }
            }

            return Units::INVALID_UNITS;
        }
        
        double StringToValue(std::string& part)
        {
            std::string value_str = SplitUnitString(part, ' ')[0];
            return std::stod(value_str);
        }

        std::vector<Value> NarrowDownToConvertibleUnits(std::vector<std::string> &split, Units to)
        {
            std::vector<Value> ret{};
            
            for (auto& part : split)
            {
                Units u = StringToUnit(part);
                if (CanUnitAGoToUnitB(to, u))
                {
                    double val = StringToValue(part);
                    ret.push_back({val, u});
                }
            }
            
            return ret;
        }
        
        Value ConvertUnitTo(Value& v, Units to)
        {
            if (CanUnitAGoToUnitB(v.Unit, to))
            {
                return {v.Val * UnitAToUnitBConversionRate(v.Unit, to), to};
            }
            
            return {0, Units::INVALID_UNITS};
        }

        double ConvertAllTo(std::string str, Units to)
        {
            std::vector<std::string> split = SplitUnitString(str);
            auto convertible = NarrowDownToConvertibleUnits(split, to);

            double ret = 0;
            
            for (auto& v : convertible)
            {
                ret += ConvertUnitTo(v, to).Val;
            }
            
            return ret;
        }
    }
}