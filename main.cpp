#include <iostream>
#include <regex>

#include "Address.hpp"
#include "NetCommander.hpp"

int main()
{
    std::cout << "Hello, World!" << std::endl;

    NetCommander netCommander;
    AddressRegexes regexes;

    // Test of Addresses -----------------------------------------------------------------------------------------------

    std::string ip1 = "8.8.8.8";
    std::string ip2 = "139.130.4.5";
    std::string domainName1 = "google.com";
    std::string domainName2 = "pornhub.com";

    Address address1(ip1, regexes);
    Address address2(ip2, regexes);
    Address address3(domainName1, regexes);
    Address address4(domainName2, regexes);

    std::cout << address1.get() << std::endl;
    std::cout << address2.get() << std::endl;
    std::cout << address3.get() << std::endl;
    std::cout << address4.get() << std::endl;

    // Test of Ping ----------------------------------------------------------------------------------------------------

    netCommander.ping(address1, 10);
    netCommander.ping(address2, 10);
    netCommander.ping(address3, 10);
    netCommander.ping(address4, 10);

    return 0;
}