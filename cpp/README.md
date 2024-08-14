# C++ Proxy Server

This is a simple HTTP proxy server implemented in C++. It accepts client connections, forwards the HTTP requests to the target server, and then sends the server's response back to the client.

## Features
- Handles HTTP GET requests
- Multi-threaded to handle multiple client connections simultaneously using `std::thread`
- Works on default port 8888

## Usage

1. **Compile and run the proxy server**:
   ```bash
   g++ -o proxy_server proxy_server.cpp -pthread
   ./proxy_server

