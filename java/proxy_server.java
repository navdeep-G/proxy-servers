import java.io.*;
import java.net.*;

public class ProxyServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8888);
        System.out.println("Proxy server listening on port 8888");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            new Thread(() -> handleClient(clientSocket)).start();
        }
    }

    public static void handleClient(Socket clientSocket) {
        try {
            BufferedReader inFromClient = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            DataOutputStream outToClient = new DataOutputStream(clientSocket.getOutputStream());

            // Read the request from the client
            String requestLine = inFromClient.readLine();
            String[] tokens = requestLine.split(" ");
            String url = tokens[1];
            URL urlObj = new URL(url);
            String host = urlObj.getHost();
            int port = urlObj.getPort() == -1 ? 80 : urlObj.getPort();

            // Connect to the remote server
            Socket serverSocket = new Socket(host, port);
            BufferedReader inFromServer = new BufferedReader(new InputStreamReader(serverSocket.getInputStream()));
            DataOutputStream outToServer = new DataOutputStream(serverSocket.getOutputStream());

            // Send the request to the server
            outToServer.writeBytes(requestLine + "\r\n");
            String headerLine;
            while (!(headerLine = inFromClient.readLine()).equals("")) {
                outToServer.writeBytes(headerLine + "\r\n");
            }
            outToServer.writeBytes("\r\n");

            // Read the server's response and send it to the client
            String responseLine;
            while ((responseLine = inFromServer.readLine()) != null) {
                outToClient.writeBytes(responseLine + "\r\n");
            }

            serverSocket.close();
            clientSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
