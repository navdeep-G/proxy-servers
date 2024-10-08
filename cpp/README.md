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

2. **Configure your browser (or any HTTP client) to use the proxy**:

   - Proxy host: 127.0.0.1
   - Proxy port: 8888

3. **Test the proxy**:

   - Open a web browser or an HTTP client (like curl) and make requests to any website.
   - The proxy server will display the incoming connections and relay the data between your client and the server.
