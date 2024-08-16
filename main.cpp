#include <iostream>
#include <limits>

#include <boost/asio.hpp>
#include <boost/lambda/lambda.hpp>

#include "client.h"
#include "server.h"

using namespace std;

void setupServer() {
	//get port
	cout << "Please enter a port to host the server with: ";
	int userPort;
	cin >> userPort;

	//start server
	handleServer(userPort);
}

void setupClient() {
	string input_ip;
	string input_port;
	int port;
	boost::asio::ip::address_v4 ip_addr;

	for (;;) {
		cout << "Please enter an IP to connect to: ";
		cin >> input_ip;

		cout << "Please enter a port (1024 - 65535) to connect to: ";
		cin >> input_port;

		//verify ip
		try {
			ip_addr = boost::asio::ip::make_address_v4(input_ip);
			cout << "Valid IP address entered: " << ip_addr.to_string() << endl;

			
		}
		catch (exception& e) {
			cerr << "Invalid IP address entered: " << e.what() << endl;
			continue;
		}

		//verify port
		try {
			port = stoi(input_port);

			if (port >= 1024 && port <= 65535) {
				cout << "Valid port entered: " << port << endl;
				break; //valid
			}
			else {
				cerr << "Port number must be between 1024 and 65535." << endl;
			}
		}
		catch (invalid_argument&) {
			cerr << "Invalid input, please enter a numeric port number." << endl;
			continue;
		}
		catch (out_of_range&) {
			cerr << "Invalid input, please enter a port number in range." << endl;
			continue;
		}
	}

	//move on to connection
	handleConnection(ip_addr, port);
}

int main()
{
	for (;;) {
		cout << "Please enter '1' to host a server or '2' to find a server: ";
		int userChoice;
		cin >> userChoice;

		if (userChoice == 1) {
			setupServer();
		}
		else if (userChoice == 2) {
			setupClient();
		}
	}
	
	return 0;
}