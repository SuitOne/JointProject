#pragma once
#include <array>
#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <vector>

using namespace boost::asio;
using namespace boost::asio::ip;

class Client {
public:
	using MessageHandler = std::function<void(const std::string&, int)>;

	Client(int clientId, tcp::socket socket, MessageHandler handler);

	int getId();
	void startRead();
	void sendMessage(std::string msg);

private:
	int id;
	tcp::socket socket_;
	boost::asio::streambuf readBuffer_;
	MessageHandler messageHandler_;

	void handleRead(const::boost::system::error_code& ec, std::size_t bytesTransf);
};

class ChatServer {
public:
	ChatServer(io_context& ioContext, int port);

private:
	io_context& servContext;
	int servPort;
	int nextClientId;
	std::vector<std::shared_ptr<Client>> servClients;
	tcp::acceptor servAcceptor;

	void startAccept();
	void broadcastMessage(const std::string& msg, int senderId);
};