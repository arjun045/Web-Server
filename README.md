The project aim was to design and developed a fully functional Client-Server Communication, the server fulfills the request and delivers the response to the client.
The project is divided into two parts:-

For Client :-
//Algorithm for TCP client
1) Find the IP address and port number of server
2) Create a TCP socket
3)Connect the socket to server (Server must be up and listening for new requests)
4)Fork the process into two :- 
	a) Child Process(in with response from server is recieved)
	b) Parent Process(sends request to the server)
5)Close the connection

For Server :-

//Algorithm for TCP server
1)Find the IP address and port number of server
2)Create a TCP server socket
3)Bind the server socket to server IP and Port number (this is the
port to which clients will connect)
4)Accept a new connection in different threads from client and returns a client socket that represents the client which is connected.
5)Divides this thread into two processes
	a) Child Process(in with response from server is received)
	b) Parent Process(sends request to the server)
6)Close the connection with client.
