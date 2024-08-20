#include "./include/ChatClient.h"

ChatClient::ChatClient(io_context& ioContext, const ip::address_v4& serverIp, int serverPort)
    : ioContext_(ioContext), socket_(ioContext), endpoint_(serverIp, serverPort) {
}

void ChatClient::start() {
    //connect to the server and listen for messages
    socket_.async_connect(endpoint_,
        [this](const boost::system::error_code& ec) {
            handleConnect(ec);
        });

    //create a thread to handle user input so that it doesn't block async operations
    std::thread inputThread([this]() {
        std::string message;
        while (std::getline(std::cin, message)) {
            startWrite(message);
        }
        });

    ioContext_.run();
    inputThread.join();  //wait for the input thread to finish, then rejoin the threads
}

void ChatClient::handleConnect(const boost::system::error_code& ec) {
    if (!ec) {
        std::cout << "Connected to server!" << std::endl;
        startRead();  //begin reading from the server
    }
    else {
        std::cerr << "ERROR, Failed to connect: " << ec.message() << std::endl;
    }
}

void ChatClient::startRead() {
    //read input from server until termination characters
    async_read_until(socket_, readBuffer_, "\n",
        [this](const boost::system::error_code& ec, std::size_t bytesTransferred) {
            handleRead(ec, bytesTransferred);
        });
}

void ChatClient::handleRead(const boost::system::error_code& ec, std::size_t bytesTransferred) {
    if (!ec) {
        std::istream is(&readBuffer_);
        std::string message;
        std::getline(is, message);
        std::cout << message << std::endl;

        startRead();  //continue reading from the server
    }
    else {
        std::cerr << "ERROR: " << ec.message() << std::endl;
        socket_.close();
    }
}

void ChatClient::startWrite(std::string message) {
    message += "\n";
    //send references message to server
    async_write(socket_, boost::asio::buffer(message + "\n"),
        [this](const boost::system::error_code& ec, std::size_t bytesTransferred) {
            handleWrite(ec, bytesTransferred);
        });
}

void ChatClient::handleWrite(const boost::system::error_code& ec, std::size_t bytesTransferred) {
    if (!ec) {
        std::cout << "Message sent (" << bytesTransferred << " bytes)." << std::endl;
    }
    else {
        std::cerr << "ERROR, Write failed: " << ec.message() << std::endl;
    }
}
