//
// Created by Busiu on 01.11.2018.
//

#include <cfloat>
#include "NetCommander.hpp"

NetCommander::NetCommander()
{
    WSADATA wsaData;
    int iResult;

    //  Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        std::cout << "WSAStartup failed: " + iResult << std::endl;
    }
}

NetCommander::~NetCommander()
{
    std::cout << "Exiting." << std::endl;

    //  Exit Winsock
    WSACleanup();
}

void NetCommander::ping(Address& address, unsigned noPackets)
{
    int iResult;
    struct timespec timeStart;
    struct timespec timeEnd;

    unsigned packetsSent = 0;
    unsigned packetsReceived = 0;

    double totalReplyingTime = 0;
    double minReplyingTime = DBL_MAX;
    double maxReplyingTime = -DBL_MAX;


    //  Creating Socket
    SOCKET WSAAPI sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock == INVALID_SOCKET)
    {
        std::cout << "Socket creating failed with error: " + WSAGetLastError() << std::endl;
        return;
    }

    //  Set the appropriate values to our struct, which is our ICMP header
    icmpHeader packet;
    packet.type = 8;                // The echo request is 8
    packet.code = 0;                // No need
    packet.checksum = 0xfff7;       // Fixed checksum since the data is not changing
    packet.identifier = 0;
    packet.sequenceNumber = 0;
    packet.payload = 0x00000000;    // We don't send anything.


    //  Creating a IP Header from a struct that exists in another library
    struct sockaddr_in addressRecv;
    addressRecv.sin_family = AF_INET;
    addressRecv.sin_port = 0;
    addressRecv.sin_addr.s_addr = inet_addr(address.get().c_str());


    //  Loop of sending and receiving packet noPacket times
    std::cout << "Pinging " + address.get() << " with 32 bytes of data:" << std::endl;
    for(int packetIndex = 1; packetIndex <= noPackets; packetIndex++)
    {
        //  Send our PING
        clock_gettime(CLOCK_MONOTONIC, &timeStart);

        iResult = sendto(
                sock,
                reinterpret_cast<char*> (&packet),
                sizeof(packet),
                0,
                reinterpret_cast<struct sockaddr*> (&addressRecv),
                sizeof(addressRecv)
        );

        if (iResult == SOCKET_ERROR)
        {
            std::cout << "Sending package failed with error: " + WSAGetLastError() << std::endl;
            return;
        }
        else
        {
            packetsSent++;
        }


        //  Prepare all the necessary variable to handle the response
        char res[32];
        struct sockaddr resAddress;
        int resAddressSize = sizeof(resAddress);


        //  Read the response from the remote host
        iResult = recvfrom(
                sock,
                res,
                sizeof(res),
                0,
                &resAddress,
                &resAddressSize
        );

        if (iResult == SOCKET_ERROR)
        {
            std::cout << "Receiving package failed with error: " + WSAGetLastError() << std::endl;
        }

        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
        double timeElapsed = getTimeInterval(timeStart, timeEnd);


        //  Create the response variable using our custom struct with mapping (and ignoring IP header)
        icmpHeader* echoResponse;
        echoResponse = (icmpHeader *)&res[20];
        if(echoResponse->type != 0)
        {
            std::cout << "Pinging failed! Received ICMP header with type: " << echoResponse->type << "." << std::endl;
        }
        else
        {
            std::cout << "Packet nr." << packetIndex << "! Reply from: " << address.get() <<
                      " - Time: " << timeElapsed << " ms." << std::endl;

            if(timeElapsed < minReplyingTime)
            {
                minReplyingTime = timeElapsed;
            }
            if(timeElapsed > maxReplyingTime)
            {
                maxReplyingTime = timeElapsed;
            }
            totalReplyingTime += timeElapsed;
            packetsReceived++;
        }
    }
    std::cout << "Ping statistics for: " << address.get() << ":" << std::endl;
    std::cout << "\t Sent = " << packetsSent << std::endl;
    std::cout << "\t Received = " << packetsReceived << std::endl;
    std::cout << "\t Ratio = " << packetsReceived * 100 / packetsSent << "%" << std::endl;
    std::cout << "Round trip times in milli-seconds:" << std::endl;
    std::cout << "\t Minimum = " << minReplyingTime << " ms" << std::endl;
    std::cout << "\t Maximum = " << maxReplyingTime << " ms" << std::endl;
    std::cout << "\t Average = " << totalReplyingTime / packetsReceived << " ms" << std::endl;
    std::cout << std::endl;


    //  Close the socket
    iResult = closesocket(sock);
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "Closing socket failed with error: " + WSAGetLastError() << std::endl;
        return;
    }
}

double NetCommander::getTimeInterval(struct timespec& timeStart, struct timespec& timeEnd)
{
    double timeElapsed = (timeEnd.tv_nsec - timeStart.tv_nsec) / 1000000.0;
    timeElapsed += (timeEnd.tv_sec - timeStart.tv_sec) * 1000.0;

    return timeElapsed;
}
