#include <iostream>

#define ASIO_STANDALONE
#include <asio.hpp>

using asio::ip::tcp;

int main() {
  try {
    asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::socket socket(io_context);

    // Resolve the host name and port number
    auto endpoints = resolver.resolve("example.com", "80");

    // Connect to the server
    asio::connect(socket, endpoints);

    // Prepare the HTTP request
    std::ostringstream request_stream;
    request_stream << "GET / HTTP/1.1\r\n";
    request_stream << "Host: example.com\r\n";
    request_stream << "Connection: close\r\n";
    request_stream << "\r\n";
    std::string request = request_stream.str();

    // Send the HTTP request asynchronously
    asio::async_write(socket, asio::buffer(request),
        [&](std::error_code ec, std::size_t length) {
          if (!ec) {
            std::cout << "Request sent successfully!" << std::endl;
          }
        });

    // Read the HTTP response asynchronously
    std::string response;
    asio::async_read_until(socket, asio::dynamic_buffer(response), "\r\n",
        [&](std::error_code ec, std::size_t length) {
          if (!ec) {
            std::cout << "Response received successfully!" << std::endl;
            std::cout << "Status line: " << response << std::endl;
          }
        });

    // Run the I/O context to start the asynchronous operations
    io_context.run();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  system("pause");
  return 0;
}