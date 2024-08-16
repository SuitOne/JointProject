#include <boost/asio.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

int main()
{
	cout << "Starting HTTP server on PORT 80!" << endl;
	
	//attempt to start server
	try {
		//create io
		io_context io;

		//create socket information with listener (acceptor)
		tcp::endpoint addr_info(tcp::v4(), 80);
		tcp::acceptor acceptor(io, addr_info);

		//create buffer to write message
		string body = "<Body>Hello World</Body>";
		string buf =
			"HTTP/1.1 200 OK\r\n"
			"Content-Length: " + to_string(body.size()) + "\r\n"
			"Content-Type: text/html\r\n"
			"\r\n" +
			body;

		for (;;) {
			//establishing connection
			cout << "Waiting for connection..." << endl;
			tcp::socket socket(io);
			acceptor.accept(socket);

			//connection info
			boost::system::error_code error;
			size_t bytes_transferred = write(socket, buffer(buf), error);
			
			//post connection handling
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