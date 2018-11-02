//
// Created by Busiu on 01.11.2018.
//

#include "AddressRegexes.hpp"

AddressRegexes::AddressRegexes() :
        regexIPv4("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$")
        {}

std::regex AddressRegexes::getRegexIPv4()
{
    return regexIPv4;
}
