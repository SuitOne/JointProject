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
			acceptor.accept(socket);
			boost::system::error_code error;

			string response;

			cout << "Enter the message to send: ";
			cin >> response;

			//send the full response
			size_t bytes_transferred = write(socket, buffer(response + "TERM"), error);

			//error handling
			if (!error) {
				cout << "Sent " << bytes_transferred << " bytes successfully." << endl;
			}
			else {
				cout << "Error: " << error.message() << endl;
			}
		}

	}
	catch (exception& e) {
		cout << "Error: " << e.what() << endl;
	}
}