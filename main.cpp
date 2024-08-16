#include <boost/asio.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

int main()
{
	cout << "Starting HTTP server on PORT 80!" << endl;
	
	//attempt to start server
	try {
		
		//create io and socket info
		io_context io;
		tcp::endpoint addr_info(tcp::v4(), 80);
		tcp::acceptor acceptor(io, addr_info);

		for (;;) {
			//establishing connection
			cout << "Waiting for connection..." << endl;
			tcp::socket socket(io);
			acceptor.accept(socket);
			boost::system::error_code error;

			//get html file
			ifstream html_file("index.html");
			if (!html_file.is_open()) {
				cerr << "Error: Could not open file 'index.html'" << endl;
				continue;
			}

			//read the entire HTML file into a string
			stringstream html_stream;
			html_stream << html_file.rdbuf();
			string body = html_stream.str();

			//prepare HTTP response headers
			string headers =
				"HTTP/1.1 200 OK\r\n"
				"Content-Length: " + to_string(body.size()) + "\r\n"
				"Content-Type: text/html\r\n"
				"\r\n";

			//combine headers and body
			string response = headers + body;

			//send the full response
			size_t bytes_transferred = write(socket, buffer(response), error);

			//error handling
			if (!error) {
				cout << "Sent " << bytes_transferred << " bytes successfully." << endl;
			}
			else {
				cout << "Error: " << error.message() << endl;
			}
		}
		
	} catch(exception& e){
		cout << "Error: " << e.what() << endl;
	}
	
	return 0;
}