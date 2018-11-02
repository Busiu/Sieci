cmake_minimum_required(VERSION 3.10)
project(Sieci)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sieci    main.cpp
                        Address.cpp
                        AddressRegexes.cpp
                        NetCommander.cpp)

target_link_libraries(Sieci -lws2_32)