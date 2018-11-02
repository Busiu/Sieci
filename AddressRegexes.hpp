//
// Created by Busiu on 01.11.2018.
//

#ifndef SIECI_ADDRESSREGEXES_HPP
#define SIECI_ADDRESSREGEXES_HPP

#include <iostream>
#include <regex>

class AddressRegexes {
private:
    std::regex regexIPv4;

public:
    explicit AddressRegexes();
    ~AddressRegexes() = default;

    std::regex getRegexIPv4();

};


#endif //SIECI_ADDRESSREGEXES_HPP
