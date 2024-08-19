#include "ChatServer.h"
#include <array>
#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <vector>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

Client::Client(int clientId, tcp::socket socket, MessageHandler messageHandler) :
	id(clientId), socket_(std::move(socket)), messageHandler_(messageHandler) {}

int Client::getId() {
	return id;
}

void Client::startRead() {
	//read from buffer until terminated
	async_read_until(socket_, readBuffer_, "\n",
		[this](const boost::system::error_code& ec, std::size_t bytesTransferred) {
			handleRead(ec, bytesTransferred);
		});
}

void Client::handleRead(const boost::system::error_code& ec, std::size_t bytes_Transferred) {
	//broadcast message to all clients
	if (!ec) {
		istream is(&readBuffer_);
		string msg;
		getline(is, msg);

		//trigger servers broadcast handler
		messageHandler_(msg, id);

		//continue reading for more messages
		startRead();
	}
	else {
		cerr << "ERROR, Client " << id << " disconnected or read error: " << ec.message();
		socket_.close();
	}
}

void Client::sendMessage(string msg) {
	//send message to client
	async_write(socket_, boost::asio::buffer(msg),
		[this, msg](const boost::system::error_code& ec, std::size_t /*bytesTransferred*/) {
			if (!ec) {
				cout << "Message successfully delivered to CLIENT " << id << endl;
			}
			else {
				cerr << "ERROR, Failed to send message to Client " << id << ": " << ec.message() << endl;
			}
		});
}

ChatServer::ChatServer(io_context& ioContext, int port) :
	servAcceptor(ioContext, tcp::endpoint(tcp::v4(), port)),
	servContext(ioContext),
	servPort(port),
	nextClientId(1) {
	startAccept();
}

void ChatServer::startAccept() {
	cout << "Listening for connections on PORT " << servPort << endl;

	auto newSocket = make_shared<tcp::socket>(servAcceptor.get_executor());

	servAcceptor.async_accept(*newSocket,
		[this, newSocket](boost::system::error_code ec) {
			if (!ec) {
				//create client, then add to list
				auto client = make_shared<Client>(nextClientId++, move(*newSocket),
					[this](const string& message, int senderId) {
						broadcastMessage(message, senderId);
					});

				servClients.push_back(client);

				cout << "Connection established with Client ID " << client->getId() << endl;

				//start async r/w with connections
				client->startRead();

				//start new connections
				startAccept();
			}
			else {
				cerr << "ERROR, Failure during connection: " << ec.message() << endl;
			}
		});
}

void ChatServer::broadcastMessage(const string& msg, int senderId) {
	//logging
	cout << "Broadcasting message from CLIENT " << senderId << ": " << msg << endl;

	//iterate through list of clients to broadcast a recieved message
	for (auto& client : servClients) {
		client->sendMessage("CLIENT " + to_string(senderId) + ": " + msg);
	}
}

