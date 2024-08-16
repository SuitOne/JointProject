#pragma once

#include <array>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void handleConnection(boost::asio::ip::address_v4 connIP, int connPort);