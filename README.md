# Use case
We have created two files:
1.)
client_ass2.c- this code takes the input username and password and then accordingly
	       prints the message user registered. If this compiles successfully then write the message to send to user
server_ass2.c- this code receives an input and send the message to the user 
	       according to the user input.
It supports private messaging to clients and chatting with itself

-----------------------------
Commands to run the code:
To run my_server.c:     gcc -o serv my_server.c -lpthread - done by make
./serv <port_number>
To run my_client.c:    gcc -o cli my_client.c -lpthread - done by make
./cli <host_address(local ip)> <port_number>

-------------------------------

Assumptions:
1) The port number must be greater than 1024.
2) Port number must be unique.
3) While running client_ass2.c there must be host_address and port_number and this port number should be same as the port number of 	      server_ass2.c.

-------------------------------

After compilation of Makefile:
Open one terminal to run my_server.c. 
Then open as many terminal as you want for the number of clients. 
Then rum my_client in different terminals.
	Format of the user input in my_client.c:
	Username must be of the type: user-number
		Message that to be sent: 
		To user-number: message

-------------------------------

ERRORS THAT CAN OCCUR AND SOLUTIONS THE CODE PROVIDES
1.)When a port is busy the code will exit. You need to provide a port in the server that is not busy.
2.)It will display "ERROR - restart socket” in the following cases :-
	1.) When there is no host / server available to bind
	2.) When there is an error in writing or opening the socket
	3.) When there is a connection interruption
3.) if the username is not of correct format , it will core dump the code
4.) if the port is not provided after running server or if the local host + port is not provided after running the client - it will core dump the code.

---------------------------------
