# Go Proxy Server

This is a simple HTTP proxy server implemented in Go. It accepts client connections, forwards the HTTP requests to the target server, and then sends the server's response back to the client.

## Features
- Handles HTTP GET requests
- Supports concurrent connections using goroutines
- Listens on port 8888 by default

## Usage

1. **Run the proxy server**:
   ```bash
   go run proxy_server.go

2. **Configure your browser (or any HTTP client) to use the proxy:

Proxy host: 127.0.0.1
Proxy port: 8888
Test the proxy:

Open a web browser or an HTTP client (like curl) and make requests to any website.
The proxy server will display the incoming connections and relay the data between your client and the server.
