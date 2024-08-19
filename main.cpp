#include <iostream>
#include <limits>

#include <boost/asio.hpp>
#include <boost/lambda/lambda.hpp>

#include "ChatServer.h"
#include "ChatClient.h"

using namespace std;

bool getInputInt(int &intToSet) {
	try {
		string userChoice;
		getline(cin, userChoice);
		int intChoice = stoi(userChoice);
		intToSet = intChoice;
		return true;
	}
	catch (const std::invalid_argument&) {
		cerr << "ERROR, Invalid input, please enter a numeric choice." << endl;
	}
	catch (const std::out_of_range&) {
		cerr << "ERROR, Invalid input, out of range." << endl;
	}

	return false;
}

void setupServer() {
	//get port
	cout << "Please enter a port to host on (1024 - 65535): ";

	int userPort;
	while (!getInputInt(userPort) || userPort < 1024 || userPort > 65535) {
		cerr << "ERROR, Invalid input, please enter a valid port number between 1024 and 65535: ";
	}
	cout << "Valid port entered: " << userPort << endl;

	//start server
	try {
		io_context ioContext;
		ChatServer server(ioContext, userPort);
		ioContext.run();
	}
	catch (exception& e) {
		cout << "ERROR, Exception on server start: " << e.what() << endl;
	}
}

void setupClient() {
	//establish variables
	string input_ip;
	string input_port;
	int port;
	boost::asio::ip::address_v4 ip_addr;

	//get and verify ip
	for (;;) {
		cout << "Please enter an IP to connect to: ";
		getline(cin, input_ip);;

		//verify ip
		try {
			ip_addr = (input_ip.empty()) ? 
				boost::asio::ip::make_address_v4("127.0.0.1") : boost::asio::ip::make_address_v4(input_ip);
			cout << "Valid IP address entered: " << ip_addr.to_string() << endl;
			break;
		}
		catch (exception& e) {
			cerr << "ERROR, Invalid IP address entered: " << e.what() << endl;
			continue;
		}
	}

	//get and verify port
	cout << "Please enter a port (1024 - 65535) to connect to: ";
	while (!getInputInt(port) || port < 1024 || port > 65535) {
		cerr << "ERROR, Invalid input, please enter a valid port (1024 - 65535) to connect to: ";
	}

	//move on to connection
	try {
		io_context ioContext;
		ChatClient client(ioContext, ip_addr, port);
		client.start();
	}
	catch(const exception& e){
		cerr << "ERROR, Exception on client connection: " << e.what() << endl;
	}
}

int main()
{
	//determine if user is hosting or joining server
	for (;;) {
		cout << "Please enter '1' to host a server or '2' to find a server: ";

		int userChoice;
		while (!getInputInt(userChoice) || (userChoice != 1 && userChoice != 2)) {
			cerr << "ERROR, Invalid input, please enter '1' to host a server or '2' to find a server: ";
		}

		if (userChoice == 1) {
			setupServer();
		}
		else if (userChoice == 2) {
			setupClient();
		}
	}
	
	return 0;
}