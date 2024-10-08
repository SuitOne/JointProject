#include "./include/ChatClient.h"

ChatClient::ChatClient(boost::asio::io_context& ioContext, const boost::asio::ip::address_v4& serverIp, int serverPort)
    : ioContext_(ioContext), socket_(ioContext), endpoint_(serverIp, serverPort) {
}

void ChatClient::start() {
    // Attempt to connect to the server
    socket_.async_connect(endpoint_,
        [this](const boost::system::error_code& ec) {
            handleConnect(ec);
        });

    // Create a thread to handle user input without blocking async operations
    std::thread inputThread([this]() {
        std::string message;
        while (std::getline(std::cin, message)) {
            if (message == "!q") {
                socket_.close();
                break;
            }
            startWrite(message);
        }
        });

    // Run the I/O context to process asynchronous events
    ioContext_.run();
    inputThread.join();  // Wait for the input thread to finish, then rejoin the threads
}

void ChatClient::handleConnect(const boost::system::error_code& ec) {
    if (!ec) {
        std::cout << "Connected to server!" << std::endl;
        startRead();  // Begin reading from the server
    }
    else {
        std::cerr << "ERROR, Failed to connect: " << ec.message() << std::endl;
    }
}

void ChatClient::startRead() {
    // Read input from server until the newline character
    boost::asio::async_read_until(socket_, readBuffer_, "\n",
        [this](const boost::system::error_code& ec, std::size_t bytesTransferred) {
            handleRead(ec, bytesTransferred);
        });
}

void ChatClient::handleRead(const boost::system::error_code& ec, std::size_t bytesTransferred) {
    if (!ec) {
        // Print the received message
        std::istream is(&readBuffer_);
        std::string message;
        std::getline(is, message);
        std::cout << message << std::endl;

        startRead();  // Continue reading from the server
    }
    else {
        std::cerr << "ERROR: " << ec.message() << std::endl;
        socket_.close();
        ioContext_.stop();  // Stop the I/O context on error
    }
}

void ChatClient::startWrite(const std::string& message) {
    // Copy the message into a shared_ptr to manage its lifetime
    auto msg = std::make_shared<std::string>(message + '\n');

    // Send the message to the server
    boost::asio::async_write(socket_, boost::asio::buffer(*msg),
        [this, msg](const boost::system::error_code& ec, std::size_t bytesTransferred) {
            handleWrite(ec, bytesTransferred);
        });
}

void ChatClient::handleWrite(const boost::system::error_code& ec, std::size_t bytesTransferred) {
    if (!ec) {
        // Confirm that the message was sent successfully
        std::cout << "Message sent (" << bytesTransferred << " bytes)." << std::endl;
    }
    else {
        std::cerr << "ERROR, Write failed: " << ec.message() << std::endl;
    }
}
