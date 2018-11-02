//
// Created by Busiu on 01.11.2018.
//

#include "Address.hpp"

Address::Address(std::string& address, AddressRegexes& regexContainer)
        : regexContainer(regexContainer)
{
    if(std::regex_search(address, regexContainer.getRegexIPv4()))
    {
        this->type = AddressType::IPv4;
        this->address = address;
    }
    else
    {
        std::string ipAddress = DNSLookup(address);
        this->type = AddressType::IPv4;
        this->address = ipAddress;
    }
}

std::string Address::DNSLookup(std::string& address)
{
    hostent* hostEntity;
    hostEntity = gethostbyname(address.c_str());

    if (hostEntity == nullptr)
    {
        std::cout << "Looking up DNS failed with error: " + WSAGetLastError() << std::endl;

        // No ip found for hostname
        return "NIE MO XD";
    }

    // Filling up address structure
    std::string ip(inet_ntoa(*(reinterpret_cast<struct in_addr*> (hostEntity->h_addr))));

    return ip;
}

std::string Address::get()
{
    return address;
}

AddressType Address::getType()
{
    return type;
}
