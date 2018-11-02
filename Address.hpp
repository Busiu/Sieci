//
// Created by Busiu on 01.11.2018.
//

#ifndef SIECI_ADDRESS_HPP
#define SIECI_ADDRESS_HPP

#include <iostream>
#include <stdlib.h>
#include <winsock2.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread_time.h>
#include <regex>

#include "AddressRegexes.hpp"

enum class AddressType
{
    IPv4
};

class Address
{
private:
    AddressType type;
    std::string address;

    AddressRegexes regexContainer;

public:
    explicit Address(std::string& address, AddressRegexes& regexContainer);
    ~Address() = default;

    std::string get();
    AddressType getType();

private:
    std::string DNSLookup(std::string& address);

};


#endif //SIECI_ADDRESS_HPP
