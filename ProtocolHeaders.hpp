//
// Created by Busiu on 01.11.2018.
//

#ifndef SIECI_PROTOCOLHEADERS_HPP
#define SIECI_PROTOCOLHEADERS_HPP

struct icmpHeader
{
    uint8_t type;                       //  0 - 7
    uint8_t code;                       //  8 - 15
    uint16_t checksum;                  //  16 - 31
    uint16_t identifier;                //  32 - 47
    uint16_t sequenceNumber;            //  48 - 63
    uint32_t payload;                   //  64 - 95
};

#endif //SIECI_PROTOCOLHEADERS_HPP
