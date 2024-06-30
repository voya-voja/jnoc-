Class SocketImpl
	fd
	protected FileDescriptor fdThe file descriptor object for this socket. 


	--------------------------------------------------------------------------------

	address
	protected InetAddress addressThe IP address of the remote end of this socket. 


	--------------------------------------------------------------------------------

	port
	protected int portThe port number on the remote host to which this socket is connected. 


	--------------------------------------------------------------------------------

	localport
	protected int localportThe local port number to which this socket is connected. 

	Constructor Detail 

	SocketImpl
	public SocketImpl()Method Detail 

	create
	protected abstract void create(boolean stream)
							throws IOExceptionCreates either a stream or a datagram socket. 

	Parameters:
	stream - if true, create a stream socket; otherwise, create a datagram socket. 
	Throws: 
	IOException - if an I/O error occurs while creating the socket.

	--------------------------------------------------------------------------------

	connect
	protected abstract void connect(String host,
									int port)
							 throws IOExceptionConnects this socket to the specified port on the named host. 

	Parameters:
	host - the name of the remote host.
	port - the port number. 
	Throws: 
	IOException - if an I/O error occurs when connecting to the remote host.

	--------------------------------------------------------------------------------

	connect
	protected abstract void connect(InetAddress address,
									int port)
							 throws IOExceptionConnects this socket to the specified port number on the specified host. 

	Parameters:
	address - the IP address of the remote host.
	port - the port number. 
	Throws: 
	IOException - if an I/O error occurs when attempting a connection.

	--------------------------------------------------------------------------------

	connect
	protected abstract void connect(SocketAddress address,
									int timeout)
							 throws IOExceptionConnects this socket to the specified port number on the specified host. A timeout of zero is interpreted as an infinite timeout. The connection will then block until established or an error occurs. 

	Parameters:
	address - the Socket address of the remote host.
	timeout - the timeout value, in milliseconds, or zero for no timeout. 
	Throws: 
	IOException - if an I/O error occurs when attempting a connection.
	Since: 
	1.4 

	--------------------------------------------------------------------------------

	bind
	protected abstract void bind(InetAddress host,
								 int port)
						  throws IOExceptionBinds this socket to the specified port number on the specified host. 

	Parameters:
	host - the IP address of the remote host.
	port - the port number. 
	Throws: 
	IOException - if an I/O error occurs when binding this socket.

	--------------------------------------------------------------------------------

	listen
	protected abstract void listen(int backlog)
							throws IOExceptionSets the maximum queue length for incoming connection indications (a request to connect) to the count argument. If a connection indication arrives when the queue is full, the connection is refused. 

	Parameters:
	backlog - the maximum length of the queue. 
	Throws: 
	IOException - if an I/O error occurs when creating the queue.

	--------------------------------------------------------------------------------

	accept
	protected abstract void accept(SocketImpl s)
							throws IOExceptionAccepts a connection. 

	Parameters:
	s - the accepted connection. 
	Throws: 
	IOException - if an I/O error occurs when accepting the connection.

	--------------------------------------------------------------------------------

	getInputStream
	protected abstract InputStream getInputStream()
										   throws IOExceptionReturns an input stream for this socket. 

	Returns:
	a stream for reading from this socket. 
	Throws: 
	IOException - if an I/O error occurs when creating the input stream.

	--------------------------------------------------------------------------------

	getOutputStream
	protected abstract OutputStream getOutputStream()
											 throws IOExceptionReturns an output stream for this socket. 

	Returns:
	an output stream for writing to this socket. 
	Throws: 
	IOException - if an I/O error occurs when creating the output stream.

	--------------------------------------------------------------------------------

	available
	protected abstract int available()
							  throws IOExceptionReturns the number of bytes that can be read from this socket without blocking. 

	Returns:
	the number of bytes that can be read from this socket without blocking. 
	Throws: 
	IOException - if an I/O error occurs when determining the number of bytes available.

	--------------------------------------------------------------------------------

	close
	protected abstract void close()
						   throws IOExceptionCloses this socket. 

	Throws: 
	IOException - if an I/O error occurs when closing this socket.

	--------------------------------------------------------------------------------

	shutdownInput
	protected void shutdownInput()
						  throws IOExceptionPlaces the input stream for this socket at "end of stream". Any data sent to this socket is acknowledged and then silently discarded. If you read from a socket input stream after invoking shutdownInput() on the socket, the stream will return EOF. 

	Throws: 
	IOException - if an I/O error occurs when shutting down this socket.
	See Also:
	Socket.shutdownOutput(), Socket.close(), Socket.setSoLinger(boolean, int)

	--------------------------------------------------------------------------------

	shutdownOutput
	protected void shutdownOutput()
						   throws IOExceptionDisables the output stream for this socket. For a TCP socket, any previously written data will be sent followed by TCP's normal connection termination sequence. If you write to a socket output stream after invoking shutdownOutput() on the socket, the stream will throw an IOException. 

	Throws: 
	IOException - if an I/O error occurs when shutting down this socket.
	See Also:
	Socket.shutdownInput(), Socket.close(), Socket.setSoLinger(boolean, int)

	--------------------------------------------------------------------------------

	getFileDescriptor
	protected FileDescriptor getFileDescriptor()Returns the value of this socket's fd field. 

	Returns:
	the value of this socket's fd field.
	See Also:
	fd

	--------------------------------------------------------------------------------

	getInetAddress
	protected InetAddress getInetAddress()Returns the value of this socket's address field. 

	Returns:
	the value of this socket's address field.
	See Also:
	address

	--------------------------------------------------------------------------------

	getPort
	protected int getPort()Returns the value of this socket's port field. 

	Returns:
	the value of this socket's port field.
	See Also:
	port

	--------------------------------------------------------------------------------

	supportsUrgentData
	protected boolean supportsUrgentData()Returns whether or not this SocketImpl supports sending urgent data. By default, false is returned unless the method is overridden in a sub-class 

	Returns:
	true if urgent data supported
	Since: 
	1.4 
	See Also:
	address

	--------------------------------------------------------------------------------

	sendUrgentData
	protected abstract void sendUrgentData(int data)
									throws IOExceptionSend one byte of urgent data on the socket. The byte to be sent is the low eight bits of the parameter 

	Parameters:
	data - The byte of data to send 
	Throws: 
	IOException - if there is an error sending the data.
	Since: 
	1.4 

	--------------------------------------------------------------------------------

	getLocalPort
	protected int getLocalPort()Returns the value of this socket's localport field. 

	Returns:
	the value of this socket's localport field.
	See Also:
	localport

	--------------------------------------------------------------------------------

	toString
	public String toString()Returns the address and port of this socket as a String. 

	Overrides:
	toString in class Object
	Returns:
	a string representation of this socket.
