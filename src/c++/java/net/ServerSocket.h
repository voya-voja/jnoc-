/*******************************************************************************
*  JNOC++ - Java Network Object Comminication ++:
*	is the implementation of Java Object Serialization protocol
*
*  Copyright (C) 1997 - 2002 iNexum Systems Inc.
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*  
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
*  Lesser General Public License for more details.
*  
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
*  Using the Lesser GPL permits use of the library in proprietary programs; 
*  Using the ordinary GPL for a library makes it available only for free 
*  programs.
*******************************************************************************/
/*----------------------------------------------------------------------------*
 *                                                                            *
 * File:		ServerSocket.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030303	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef java_net_ServerSocket_h
#define java_net_ServerSocket_h

#ifdef WIN32
        #include <winsock2.h>

		typedef int socklen_t;
#else
        #include <sys/socket.h>

		#define INVALID_SOCKET  (SOCKET)(~0)
		#define SOCKET_ERROR            (-1)

        typedef int SOCKET;
#endif

#include <string>
#include "SocketException.h"
#include "SocketAddress.h"
#include <inexum/definitions.h>

/** iNexum's java classes implemented in C++.
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
namespace java
{
	/** iNexum's java/net classes implemented in C++.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
	namespace net
	{
		class Socket;
		class ServerSocketChannel;
		class SocketImplFactory;
		class InetAddress;

		/** A C++ implementation of Java like java/net/ServerSocket class.
		  * This class implements server sockets. A server socket waits for 
		  * requests to come in over the network. It performs some operation 
		  * based on that request, and then possibly returns a result to the 
		  * requester. 
		  *
		  * Refer to SUN's documentation for Java class ServerSocket
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier ServerSocket
		{
		public:
			/** Creates an unbound server socket.
			  *	 
			  *	@exception  SocketException* - IO error when opening the socket.
			  */
			ServerSocket() throw(SocketException*);


			/** Creates a server socket, bound to the specified port. A port of 0 
			  * creates a socket on any free port. 
			  *	The maximum queue length for incoming connection indications 
			  * (a request to connect) is set to 50. If a connection indication 
			  * arrives when the queue is full, the connection is refused. 
			  *	If the application has specified a server socket factory, that 
			  * factory's createSocketImpl method is called to create the actual 
			  * socket implementation. Otherwise a "plain" socket is created. 
			  *	If there is a security manager, its checkListen method is called 
			  * with the port argument as its argument to ensure the operation is 
			  * allowed. This could result in a SecurityException. 
			  *	
			  *	@param port - the port number, or 0 to use any free port. 
			  *	 
			  *	@exception  SocketException* - if an I/O error occurs when opening the socket. 
			  *	@exception  SecurityException - if a security manager exists and its checkListen 
			  * method doesn't allow the operation.
			  *	
			  *	@see SocketImpl
			  *	@see SocketImplFactory.createSocketImpl()
			  *	@see setSocketFactory(java.net.SocketImplFactory)
			  *	@see SecurityManager.checkListen(int)
			  */
			ServerSocket(int port) throw(SocketException*);

			/** Creates a server socket and binds it to the specified local port 
			  * number, with the specified backlog. A port number of 0 creates a 
			  * socket on any free port.
			  *	The maximum queue length for incoming connection indications 
			  * (a request to connect) is set to the backlog parameter. If a 
			  * connection indication arrives when the queue is full, the 
			  * connection is refused. 
			  *	If the application has specified a server socket factory, that 
			  * factory's createSocketImpl method is called to create the actual 
			  * socket implementation. Otherwise a "plain" socket is created. 
			  *	If there is a security manager, its checkListen method is called 
			  * with the port argument as its argument to ensure the operation is
			  * allowed. This could result in a SecurityException. 
			  *	The backlog argument must be a positive value greater than 0. If 
			  * the value passed if equal or less than 0, then the default value 
			  * will be assumed. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param port - the specified port, or 0 to use any free port.
			  *	@param backlog - the maximum length of the queue. 
			  *	
			  *	@exception  SocketException* - if an I/O error occurs when opening the socket. 
			  *	@exception  SecurityException - if a security manager exists and its checkListen 
			  * method doesn't allow the operation.
			  *	
			  *	@see SocketImpl
			  *	@see SocketImplFactory.createSocketImpl()
			  *	@see setSocketFactory(java.net.SocketImplFactory)
			  *	@see SecurityManager.checkListen(int)
			  */
			ServerSocket(int port, int backlog) throw(SocketException*);

			/** Create a server with the specified port, listen backlog, and local
			  * IP address to bind to. The bindAddr argument can be used on a 
			  * multi-homed host for a ServerSocket that will only accept connect 
			  * requests to one of its addresses. If bindAddr is null, it will 
			  * default accepting connections on any/all local addresses. The port
			  * must be between 0 and 65535, inclusive. 
			  *	If there is a security manager, this method calls its checkListen 
			  * method with the port argument as its argument to ensure the operation 
			  * is allowed. This could result in a SecurityException. 
			  *	The backlog argument must be a positive value greater than 0. If the 
			  * value passed if equal or less than 0, then the default value will be 
			  * assumed. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param port - the local TCP port
			  *	@param backlog - the listen backlog
			  *	@param bindAddr - the local InetAddress the server will bind to 
			  *	
			  *	@exception  SecurityException - if a security manager exists and its checkListen 
			  * method doesn't allow the operation. 
			  *	@exception  SocketException* - if an I/O error occurs when opening the socket.
			  *	
			  *	@see SocketOptions
			  *	@see SocketImpl
			  *	@see SecurityManager.checkListen(int)
			  */
			ServerSocket(int port, int backlog, const InetAddress& bindAddr)
						 throw(SocketException*);

			/** Binds the ServerSocket to a specific address (IP address and port 
			  * number). 
			  *	If the address is null, then the system will pick up an ephemeral 
			  * port and a valid local address to bind the socket. 
			  *	
			  *	@param endpoint - The IP address & port number to bind to. 
			  *	
			  *	@exception  SocketException* - if the bind operation fails, or if the socket is 
			  * already bound. 
			  *	@exception  SecurityException - if a SecurityManager is present and its 
			  * checkListen method doesn't allow the operation. 
			  *	@exception  IllegalArgumentException - if endpoint is a SocketAddress subclass 
			  * not supported by this socket
			  */
			void bind(const SocketAddress& endpoint) throw(SocketException*);

			/** Binds the ServerSocket to a specific address (IP address and port 
			  * number). 
			  *	If the address is null, then the system will pick up an ephemeral 
			  * port and a valid local address to bind the socket. 
			  *	The backlog argument must be a positive value greater than 0. If the
			  * value passed if equal or less than 0, then the default value will be
			  * assumed. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param endpoint - The IP address & port number to bind to.
			  *	@param backlog - The listen backlog length. 
			  *	
			  *	@exception  SocketException* - if the bind operation fails, or if the socket is 
			  * already bound. 
			  *	@exception  SecurityException - if a SecurityManager is present and its 
			  * checkListen method doesn't allow the operation. 
			  *	@exception  IllegalArgumentException - if endpoint is a SocketAddress subclass 
			  * not supported by this socket
			  */
			void bind(const SocketAddress& endpoint, int backlog) throw(SocketException*);

			/** Returns the local address of this server socket.
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the address to which this socket is bound, or null if the socket is
			  * unbound.
			  */
			const InetAddress& getInetAddress() const;


			/** Returns the port on which this socket is listening.
			  *	
			  *	@return the port number to which this socket is listening or -1 if the 
			  * socket is not bound yet.
			  */
			int getLocalPort() const;


			/** Returns the address of the endpoint this socket is bound to, or 
			  * null if it is not bound yet. 
			  *	
			  *	@return a SocketAddress representing the local endpoint of this socket, or
			  * null if it is not bound yet.
			  *	
			  *	@see getInetAddress()
			  * @see getLocalPort()
			  * @see bind(SocketAddress)
			  */
			const SocketAddress& getLocalSocketAddress() const;

			/** Listens for a connection to be made to this socket and accepts it. 
			  * The method blocks until a connection is made. 
			  *	A new Socket s is created and, if there is a security manager, the 
			  * security manager's checkAccept method is called with 
			  * s.getInetAddress().getHostAddress() and s.getPort() as its arguments
			  * to ensure the operation is allowed. This could result in a 
			  * SecurityException. 
			  *	
			  *	@return the new Socket 
			  *	
			  *	@exception  SocketException* - if an I/O error occurs when waiting for a connection. 
			  *	@exception  SecurityException - if a security manager exists and its checkListen
			  * method doesn't allow the operation. 
			  *	@exception  SocketTimeoutException - if a timeout was previously set with
			  * setSoTimeout and the timeout has been reached. 
			  *	@exception  IllegalBlockingModeException - if this socket has an associated
			  * channel, and the channel is in non-blocking mode.
			  *	
			  *	@see SecurityManager.checkAccept(java.lang.String, int)
			  */
			Socket* accept() throw(SocketException*);

			/** Closes this socket. Any thread currently blocked in accept() will 
			  * throw a SocketException. 
			  *	If this socket has an associated channel then the channel is closed 
			  * as well. 
			  *	
			  *	@exception  SocketException* - if an I/O error occurs when closing the socket.
			  */
			void close() throw(SocketException*);

			/** Returns the unique ServerSocketChannel object associated with this 
			  * socket, if any. 
			  *	A server socket will have a channel if, and only if, the channel 
			  * itself was created via the ServerSocketChannel.open method. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the server-socket channel associated with this socket, or null if 
			  * this socket was not created for a channel
			  */
			const ServerSocketChannel& getChannel() const;

			/** Returns the binding state of the ServerSocket. 
			  *	
			  *	@return true if the ServerSocket succesfuly bound to an address
			  */
			bool isBound() const;

			/** Returns the closed state of the ServerSocket. 
			  *	
			  *	@return true if the socket has been closed
			  */
			bool isClosed() const;

			/** Enable/disable SO_TIMEOUT with the specified timeout, in milliseconds. With this option set to a non-zero timeout, a call to accept() for this ServerSocket will block for only this amount of time. If the timeout expires, a java.net.SocketTimeoutException is raised, though the ServerSocket is still valid. The option must be enabled prior to entering the blocking operation to have effect. The timeout must be > 0. A timeout of zero is interpreted as an infinite timeout. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param timeout - the specified timeout, in milliseconds 
			  *	
			  *	@exception  SocketException - if there is an error in the underlying protocol, such as a TCP error.
			  *	
			  *	@see getSoTimeout()
			  */
			void setSoTimeout(int timeout) throw(SocketException*);

			/** Retrive setting for SO_TIMEOUT. 0 returns implies that the option is disabled (i.e., timeout of infinity). 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the SO_TIMEOUT value 
			  *	
			  *	@exception  SocketException* - if an I/O error occurs
			  *	
			  *	@see setSoTimeout(int)
			  */
			int getSoTimeout() throw(SocketException*);

			/** Enable/disable the SO_REUSEADDR socket option.
			  *	When a TCP connection is closed the connection may remain in a 
			  * timeout state for a period of time after the connection is closed
			  * (typically known as the TIME_WAIT state or 2MSL wait state). For
			  * applications using a well known socket address or port it may not be
			  * possible to bind a socket to the required SocketAddress if there is
			  * a connection in the timeout state involving the socket address or 
			  * port. 
			  *	Enabling SO_REUSEADDR prior to binding the socket using bind(
			  * SocketAddress) allows the socket to be bound even though a previous 
			  * connection is in a timeout state. 
			  *	When a ServerSocket is created the initial setting of SO_REUSEADDR is
			  * not defined. Applications can use getReuseAddress() to determine the
			  * initial setting of SO_REUSEADDR. 
			  *	The behaviour when SO_REUSEADDR is enabled or disabled after a socket
			  * is bound (See isBound()) is not defined. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param on - whether to enable or disable the socket option 
			  *	
			  *	@exception  SocketException - if an error occurs enabling or disabling the
			  * SO_RESUEADDR socket option, or the socket is closed.
			  *	
			  *	@see getReuseAddress()
			  *	@see bind(SocketAddress)
			  *	@see isBound(), isClosed()
			  */
			void setReuseAddress(bool on) throw(SocketException*);

			/** Tests if SO_REUSEADDR is enabled. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return a boolean indicating whether or not SO_REUSEADDR is enabled. 
			  *	
			  *	@exception  SocketException - if there is an error in the underlying protocol, 
			  * such as a TCP error.
			  *	
			  *	@see setReuseAddress(boolean)
			  */
			bool getReuseAddress() const throw(SocketException*);

			/** Returns the implementation address and implementation port of this
			  * socket as a String. Overrides: toString in class Object
			  *	
			  *	@return a string representation of this socket.
			  */
			const std::string& toString() const;


			/** Sets the server socket implementation factory for the application.
			  * The factory can be specified only once. 
			  *	When an application creates a new server socket, the socket 
			  * implementation factory's createSocketImpl method is called to create
			  * the actual socket implementation. 
			  *	If there is a security manager, this method first calls the security
			  * manager's checkSetFactory method to ensure the operation is allowed.
			  * This could result in a SecurityException. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param fac - the desired factory. 
			  *	
			  *	@exception  SocketException* - if an I/O error occurs when setting the socket factory. 
			  *	@exception  SocketException - if the factory has already been defined. 
			  *	@exception  SecurityException - if a security manager exists and its checkSetFactory 
			  * method doesn't allow the operation.
			  *	
			  *	@see SocketImplFactory.createSocketImpl()
			  * @see SecurityManager.checkSetFactory()
			  */
			static void setSocketFactory(SocketImplFactory& fac) throw(SocketException*);

			/** Sets a default proposed value for the SO_RCVBUF option for sockets 
			  * accepted from this ServerSocket. The value actually set in the 
			  * accepted socket must be determined by calling 
			  * Socket.getReceiveBufferSize() after the socket is returned by 
			  * accept(). 
			  *	The value of SO_RCVBUF is used both to set the size of the internal 
			  * socket receive buffer, and to set the size of the TCP receive window
			  * that is advertized to the remote peer. 
			  *	It is possible to change the value subsequently, by calling 
			  * Socket.setReceiveBufferSize(int). However, if the application wishes
			  * to allow a receive window larger than 64K bytes, as defined by 
			  * RFC1323 then the proposed value must be set in the ServerSocket 
			  * before it is bound to a local address. This implies, that the 
			  * ServerSocket must be created with the no-argument constructor,
			  * then setReceiveBufferSize() must be called and lastly the 
			  * ServerSocket is bound to an address by calling bind(). 
			  *	Failure to do this will not cause an error, and the buffer size may
			  * be set to the requested value but the TCP receive window in sockets
			  * accepted from this ServerSocket will be no larger than 64K bytes. 
			  *	
			  *	@param size - the size to which to set the receive buffer size. This value 
			  * must be greater than 0. 
			  *	
			  *	@exception  SocketException - if there is an error in the underlying protocol, 
			  * such as a TCP error. 
			  *	@exception  IllegalArgumentException - if the value is 0 or is negative.
			  *	@see
			  *	@exception  getReceiveBufferSize()
			  */
			void setReceiveBufferSize(int size) throw(SocketException*);

			/** Gets the value of the SO_RCVBUF option for this ServerSocket, that is the proposed buffer size that will be used for Sockets accepted from this ServerSocket. 
			  *	Note, the value actually set in the accepted socket is determined by calling Socket.getReceiveBufferSize(). 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the value of the SO_RCVBUF option for this Socket. 
			  *	
			  *	@exception  SocketException - if there is an error in the underlying protocol, such as a TCP error.
			  *	
			  *	@see setReceiveBufferSize(int)
			  */	
			int getReceiveBufferSize() const throw(SocketException*);

		protected:
			/** Subclasses of ServerSocket use this method to override accept() to 
			  * return their own subclass of socket. So a FooServerSocket will 
			  * typically hand this method an empty FooSocket. On return from 
			  * implAccept the FooSocket will be connected to a client. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param s - the Socket 
			  *	
			  *	@exception  IllegalBlockingModeException - if this socket has an associated 
			  * channel, and the channel is in non-blocking mode 
			  *	@exception  SocketException* - if an I/O error occurs when waiting for a connection.
			  */
			void implAccept(Socket& s) throw(SocketException*);

		private:
			/// Server socket states
			enum State{ cBound, cClosed };

			/// server socket handle
			SOCKET			mServerSocket;

			/// server socket address
			SocketAddress	mAddress;

			/// Current server socket state
			State			mState;
		};
	}	// namespace net 
} // namespace java

#endif	// java_net_ServerSocket_h