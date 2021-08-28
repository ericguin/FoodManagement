#pragma once

#include <string>
#include <vector>

namespace Food
{
    namespace Units
    {
        enum class Units : unsigned
        {
            MASS_GRAMS,
            MASS_LBS,
            VOLUME_CUPS,
            VOLUME_GALLONS,
            VOLUME_ML,
            VOLUME_L,
        };
        
        double ConvertAllTo(std::string str, Units to);
        std::vector<std::string> SplitUnitString(std::string &str, char split = ';');
        bool CanUnitAGoToUnitB(Units A, Units B);
        Units StringToUnit(std::string &part);
        std::vector<std::string> NarrowDownToConvertibleUnits(std::vector<std::string> &split, Units to);
        std::vector<double> AcquireConvertibleUnitsAndConvertToTarget(std::string &str, Units to);
    }
}