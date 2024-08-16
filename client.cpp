#include <array>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

void handleConnection(boost::asio::ip::address_v4 connIP, int connPort) {
	//IO + error
	boost::asio::io_context connIO;
	boost::system::error_code connError;

	//connections
	tcp::socket connSocket(connIO);
	tcp::endpoint connEndpoint(connIP, connPort);

	connSocket.connect(connEndpoint, connError);

	if (!connError) {
		//successful connection
		cout << "Successfully connected to " << connIP.to_string() << ":" << connPort << endl;

		//buffer for inbound data
		boost::asio::streambuf buffer;

		//read data from host
		boost::system::error_code readError;
		boost::asio::read_until(connSocket, buffer, "TERM", readError);

		if (!readError) {
			//convert to string
			string message = boost::asio::buffer_cast<const char*>(buffer.data());

			//print message
			cout << "Recieved: " << message << endl;
		}
		else {
			cerr << "Error occured with inbound message: " << readError.message() << endl;
		}
	}
	else {
		cout << "Error occured while connecting: " << connError.message() << endl;
	}
}