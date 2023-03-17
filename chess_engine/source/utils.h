#pragma once
#include <iomanip>
#include <locale>


std::string format_decimal(float value)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    std::string s = stream.str();
    return s;
}