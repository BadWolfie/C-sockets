# C-sockets
Code samples for Berkeley sockets in C.

### Including
* TCP-IP sockets
	* Client
	* Server
		* Blocking
		* Non-blocking

* UDP sockets
	* Client
	* Server

## Usage
This sample codes have the only intention of showing how to implement Clients and Servers using the Berkeley sockets API in C. They implement a simple message passing between the client and the server:  
The client sends a message to the server and the server sends back a confirmation, this continues until the client sends the message "Close connection." and breaks the communication.

You must modify the code to make them do whatever you want them to.