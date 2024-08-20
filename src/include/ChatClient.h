#pragma once

#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

class ChatClient {
public:
    ChatClient(io_context& ioContext, const ip::address_v4& serverIp, int serverPort);

    void start();

private:
    void handleConnect(const boost::system::error_code& ec);
    void handleRead(const boost::system::error_code& ec, std::size_t bytesTransferred);
    void handleWrite(const boost::system::error_code& ec, std::size_t bytesTransferred);

    void startRead();
    void startWrite(std::string message);

    io_context& ioContext_;
    tcp::socket socket_;
    tcp::endpoint endpoint_;
    boost::asio::streambuf readBuffer_;
};
