#pragma once

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

void handleConnection(boost::asio::ip::address_v4 connIP, int connPort);