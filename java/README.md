# Java Proxy Server

This is a simple HTTP proxy server implemented in Java. It accepts client connections, forwards the HTTP requests to the target server, and then sends the server's response back to the client.

## Features
- Handles HTTP GET requests
- Multi-threaded to handle multiple client connections simultaneously
- Works on default port 8888

## Usage

1. **Compile and run the proxy server**:
   ```bash
   javac ProxyServer.java
   java ProxyServer

