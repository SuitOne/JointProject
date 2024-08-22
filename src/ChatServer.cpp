#include "./include/ChatServer.h"
#include <array>
#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <vector>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

Client::Client(int clientId, std::shared_ptr<tcp::socket> socket, MessageHandler messageHandler) :
    id(clientId), socket_(std::move(socket)), messageHandler_(std::move(messageHandler)) {}

int Client::getId() const {
    return id;
}

void Client::startRead() {
    // Read from buffer until terminated
    async_read_until(*socket_, readBuffer_, "\n",
        [self = shared_from_this()](const boost::system::error_code& ec, std::size_t bytesTransferred) {
            self->handleRead(ec, bytesTransferred);
        });
}

void Client::handleRead(const boost::system::error_code& ec, std::size_t bytesTransferred) {
    if (!ec) {
        std::istream is(&readBuffer_);
        auto message = std::make_shared<std::string>();
        std::getline(is, *message);

        if (is && !message->empty()) {
            std::cout << "Received message: " << *message << " from CLIENT " << id << " (" << bytesTransferred << " bytes)" << std::endl;

            // Broadcast the message using the shared pointer
            messageHandler_(*message, id);
        }
        else {
            std::cerr << "Received an empty message or stream issue" << std::endl;
        }

        // Clear the buffer after processing the message
        readBuffer_.consume(bytesTransferred);

        // Continue reading from the client
        startRead();
    }
    else {
        std::cerr << "ERROR: " << ec.message() << std::endl;
        socket_->close();
    }
}

void Client::sendMessage(const std::string& msg) {
    auto msgPtr = std::make_shared<std::string>(msg);
    // Send message to client
    async_write(*socket_, boost::asio::buffer(*msgPtr),
        [self = shared_from_this(), msgPtr](const boost::system::error_code& ec, std::size_t bytesTransferred) {
            if (!ec) {
                std::cout << "Message successfully delivered to CLIENT " << self->getId() << " (" << bytesTransferred << " bytes)." << std::endl;
            }
            else {
                std::cerr << "ERROR, Failed to send message to Client " << self->getId() << ": " << ec.message() << std::endl;
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
    std::cout << "Listening for connections on PORT " << servPort << std::endl;

    auto nextClientSocket = std::make_shared<tcp::socket>(servContext);

    servAcceptor.async_accept(*nextClientSocket,
        [this, nextClientSocket](boost::system::error_code ec) {
            if (!ec) {
                auto client = std::make_shared<Client>(nextClientId++, nextClientSocket,
                    [this](const std::string& message, int senderId) {
                        broadcastMessage(message, senderId);
                    });

                servClients.push_back(client);

                std::cout << "Connection established with Client ID " << client->getId() << std::endl;

                client->startRead();
                startAccept();
            }
            else {
                std::cerr << "ERROR, Failure during connection: " << ec.message() << std::endl;
            }
        });
}

void ChatServer::broadcastMessage(const std::string& msg, int senderId) {
    std::cout << "Broadcasting message from CLIENT " << senderId << ": " << msg << std::endl;

    auto msgPtr = std::make_shared<std::string>("CLIENT " + std::to_string(senderId) + ": " + msg + "\n");

    for (const auto& client : servClients) {
        client->sendMessage(*msgPtr);
    }
}
