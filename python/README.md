# Python Proxy Server

This is a simple HTTP proxy server implemented in Python. It accepts client connections, forwards the HTTP requests to the target server, and then sends the server's response back to the client.

## Features
- Handles HTTP GET requests
- Multi-threaded to handle multiple client connections simultaneously
- Works on default port 8888 (can be changed in the code)

## Usage

1. **Run the proxy server**:
   ```bash
   python proxy_server.py

2. **Configure your browser (or any HTTP client) to use the proxy**:

Proxy host: 127.0.0.1
Proxy port: 8888
Test the proxy:

3. **Open a web browser or an HTTP client (like curl) and make requests to any website**.

The proxy server will display the incoming connections and relay the data between your client and the server.

