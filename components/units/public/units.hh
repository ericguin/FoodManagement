#pragma once

#include <string>
#include <vector>

namespace Food
{
    namespace Units
    {
        enum class Units : unsigned
        {
            INVALID_UNITS,
            MASS_GRAMS,
            MASS_LBS,
            VOLUME_CUPS,
            VOLUME_GALLONS,
            VOLUME_ML,
            VOLUME_L,
        };
        
        struct Value
        {
            double Val;
            Units Unit;
        };
        
        double ConvertAllTo(std::string str, Units to);
        std::vector<std::string> SplitUnitString(std::string &str, char split = ';');
        bool CanUnitAGoToUnitB(Units A, Units B);
        double UnitAToBConversionRate(Units A, Units B);
        Units StringToUnit(std::string &part);
        double StringToValue(std::string &part);
        Value ConvertUnitTo(Value& v, Units to);
        std::vector<Value> NarrowDownToConvertibleUnits(std::vector<std::string> &split, Units to);
    }
}