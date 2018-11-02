//
// Created by Busiu on 01.11.2018.
//

#ifndef SIECI_NETCOMMANDER_HPP
#define SIECI_NETCOMMANDER_HPP

#include <winsock2.h>
#include <iostream>

#include "Address.hpp"
#include "ProtocolHeaders.hpp"

class NetCommander
{
private:

public:
    explicit NetCommander();
    ~NetCommander();

    void ping(Address& address, unsigned noPackets);

private:
    double getTimeInterval(struct timespec& timeStart, struct timespec& timeEnd);

};


#endif //SIECI_NETCOMMANDER_HPP
