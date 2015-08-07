The project aim was to design and developed a fully functional Client-Server Communication, the server fulfills the request and delivers the response to the client.
The project is divided into two parts:-

<h1>For Client :-</h1><br>
<b>Algorithm for TCP client</b><br>
1) Find the IP address and port number of server<br>
2) Create a TCP socket<br>
3)Connect the socket to server (Server must be up and listening for new requests)<br>
4)Fork the process into two :- <br>
	a) Child Process(in with response from server is recieved)<br>
	b) Parent Process(sends request to the server)<br>
5)Close the connection

<h1>For Server :-</h1>

<b>Algorithm for TCP server</b><br>
1)Find the IP address and port number of server,br>
2)Create a TCP server socket<br>
3)Bind the server socket to server IP and Port number (this is the
port to which clients will connect)<br>
4)Accept a new connection in different threads from client and returns a client socket that represents the client which is connected.<br>
5)Divides this thread into two processes,br>
	a) Child Process(in with response from server is received)<br>
	b) Parent Process(sends request to the server)<br>
6)Close the connection with client.<br>
