#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

void handleConnection(boost::asio::ip::address_v4 connIP, int connPort) {
    boost::asio::io_context connIO;
    boost::system::error_code connError;

    tcp::socket connSocket(connIO);
    tcp::endpoint connEndpoint(connIP, connPort);

    connSocket.connect(connEndpoint, connError);

    if (!connError) {
        cout << "Successfully connected to " << connIP.to_string() << ":" << connPort << endl;

        //continuous reading loop
        while (connSocket.is_open()) {
            boost::asio::streambuf buffer;
            boost::system::error_code readError;

            //blocking read until delimiter "\r\n.\r\n" is received
            boost::asio::read_until(connSocket, buffer, "\r\n.\r\n", readError);

            if (readError == boost::asio::error::eof) {
                cerr << "Server closed the connection." << endl;
                break; //exit the loop if the server has closed the connection
            }
            else if (readError) {
                cerr << "Error occurred with inbound message: " << readError.message() << endl;
                break; //exit the loop on other errors
            }
            else {
                //convert the buffer into a string
                istream is(&buffer);
                string message;
                getline(is, message, '\0');

                //remove the delimiter from the message
                size_t delimiter_pos = message.find("\r\n.\r\n");
                if (delimiter_pos != string::npos) {
                    message.erase(delimiter_pos);
                }

                //print the received message
                cout << "Received: " << message << endl;
            }
        }
    }
    else {
        cerr << "Error occurred while connecting: " << connError.message() << endl;
    }
}