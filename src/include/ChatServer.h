#pragma once
#include <array>
#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <vector>

class Client : public std::enable_shared_from_this<Client> {
public:
    using MessageHandler = std::function<void(const std::string&, int)>;

    Client(int clientId, std::shared_ptr<boost::asio::ip::tcp::socket> socket, MessageHandler handler);

    int getId() const;
    void startRead();
    void sendMessage(const std::string& msg);

private:
    int id;
    std::shared_ptr<boost::asio::ip::tcp::socket> socket_;
    boost::asio::streambuf readBuffer_;
    MessageHandler messageHandler_;

    void handleRead(const boost::system::error_code& ec, std::size_t bytesTransferred);
};

class ChatServer {
public:
	ChatServer(boost::asio::io_context& ioContext, int port);

private:
	boost::asio::io_context& servContext;
	int servPort;
	int nextClientId;
	std::vector<std::shared_ptr<Client>> servClients;
	boost::asio::ip::tcp::acceptor servAcceptor;

	void startAccept();
	void broadcastMessage(const std::string& msg, int senderId);
};