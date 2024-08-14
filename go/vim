package main

import (
	"fmt"
	"io"
	"net"
	"strings"
)

func handleClient(client net.Conn) {
	defer client.Close()

	// Read the request from the client
	request := make([]byte, 1024)
	client.Read(request)

	// Extract the host and port from the request
	lines := strings.Split(string(request), "\n")
	hostPort := strings.Split(lines[0], " ")[1]
	hostPort = strings.TrimPrefix(hostPort, "http://")
	hostPort = strings.Split(hostPort, "/")[0]

	// Split into host and port
	host := hostPort
	port := "80"
	if strings.Contains(hostPort, ":") {
		hostPortSplit := strings.Split(hostPort, ":")
		host = hostPortSplit[0]
		port = hostPortSplit[1]
	}

	// Connect to the remote server
	server, err := net.Dial("tcp", net.JoinHostPort(host, port))
	if err != nil {
		fmt.Println("Error connecting to server:", err)
		return
	}
	defer server.Close()

	// Send the request to the server
	server.Write(request)

	// Copy the server's response back to the client
	io.Copy(client, server)
}

func main() {
	// Listen on port 8888
	listener, err := net.Listen("tcp", ":8888")
	if err != nil {
		fmt.Println("Error starting proxy server:", err)
		return
	}
	defer listener.Close()

	fmt.Println("Proxy server listening on port 8888")

	for {
		client, err := listener.Accept()
		if err != nil {
			fmt.Println("Error accepting connection:", err)
			continue
		}

		go handleClient(client)
	}
}

