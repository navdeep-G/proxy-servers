import socket
import threading

# Function to handle client requests
def handle_client(client_socket):
    # Receive the request from the client
    request = client_socket.recv(1024)

    # Parse the first line of the request to extract the destination URL
    first_line = request.split(b'\n')[0]
    url = first_line.split(b' ')[1]

    # Extract the hostname from the URL
    http_pos = url.find(b'://')  # find position of "://"
    if http_pos == -1:
        temp = url
    else:
        temp = url[(http_pos+3):]  # get the rest of the url

    port_pos = temp.find(b':')  # find the port if present

    # Find the end of the web server
    webserver_pos = temp.find(b'/')
    if webserver_pos == -1:
        webserver_pos = len(temp)

    webserver = ""
    port = -1
    if port_pos == -1 or webserver_pos < port_pos: 
        # Default port
        port = 80
        webserver = temp[:webserver_pos]
    else:  # Specific port
        port = int(temp[(port_pos+1):][:webserver_pos-port_pos-1])
        webserver = temp[:port_pos]

    # Create a socket to connect to the web server
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.connect((webserver, port))
        server_socket.send(request)  # Send the client's request to the server

        while True:
            # Receive data from the web server
            data = server_socket.recv(4096)

            if len(data) > 0:
                # Send the data to the client
                client_socket.send(data)
            else:
                break
    except socket.error as e:
        print(f"Error: {e}")
    finally:
        # Close the sockets
        client_socket.close()
        server_socket.close()

def start_proxy_server(port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('0.0.0.0', port))
    server.listen(5)
    print(f"[*] Proxy server listening on port {port}")

    while True:
        client_socket, addr = server.accept()
        print(f"[*] Received connection from {addr}")
        client_handler = threading.Thread(target=handle_client, args=(client_socket,))
        client_handler.start()

if __name__ == "__main__":
    port = 8888
    start_proxy_server(port)
