#include <array>
#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

void handleServer(int port) {
	cout << "Starting server on PORT " << port << endl;

	//attempt to start server
	try {

		//create io and socket info
		io_context io;
		tcp::endpoint addr_info(tcp::v4(), port);
		tcp::acceptor acceptor(io, addr_info);

		for (;;) {
			//establishing connection
			cout << "Waiting for connection..." << endl;
			tcp::socket socket(io);
			boost::system::error_code acceptorError;
			acceptor.accept(socket, acceptorError);

			//look for successful connection
			if (!acceptorError) {
				for (;;) {
					cout << "Connection established!" << endl;

					boost::system::error_code transferError;

					//get text to send
					string response;
					string delimiter = "\r\n.\r\n";

					cout << "Enter the message to send: ";
					getline(cin, response);

					//send the full response
					size_t bytes_transferred = write(socket, buffer(response + delimiter), transferError);

					//error handling
					if (!transferError) {
						cout << "Sent " << bytes_transferred << " bytes successfully." << endl;
					}
					else {
						cout << "Error: " << transferError.message() << endl;
					}
				}
			}
			else {
				cout << "Error: " << acceptorError.message() << endl;
			}
		}

	}
	catch (exception& e) {
		cout << "Error: " << e.what() << endl;
	}
}