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
 * File:		Socket.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030303	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef java_net_Socket_h
#define java_net_Socket_h

#include <string>
#include <iostream.h>
#ifdef WIN32
    #include <winsock2.h>
#else
    #include <sys/socket.h>

	#define INVALID_SOCKET  (SOCKET)(~0)
	#define SOCKET_ERROR            (-1)

    typedef int SOCKET;
#endif


#include "socketbuf.h"
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
		class SocketImplFactory;
		class SocketImpl;
		class InetAddress;
		class SocketChannel;

		class SocketException;

		/** A C++ implementation of Java like java/net/Socket class.
		  * This class implements client sockets (also called just "sockets"). 
		  * A socket is an endpoint for communication between two machines. 
		  * The actual work of the socket is performed by an instance of the 
		  * socketbuf class. 
		  *
		  * Refer to SUN's documentation for Java class Socket
		  *
		  * @see socketbuf
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier Socket
		{
		public:
			/// Creates an unconnected socket, with the system-default type of SocketImpl.
			 Socket() throw(net::SocketException*);

			/** Creates a stream socket and connects it to the specified port number on the named host.
			  *	If the specified host is null it is the equivalent of specifying the address as
			  * InetAddress.getByName(null). In other words, it is equivalent to specifying an
			  * address of the loopback interface. 
			  *	If the application has specified a server socket factory, that factory's 
			  * createSocketImpl method is called to create the actual socket implementation.
			  * Otherwise a "plain" socket is created. 
			  *	If there is a security manager, its checkConnect method is called with the host
			  * address and port as its arguments. This could result in a SecurityException. 
			  *	
			  *	@param host - the host name, or null for the loopback address.
			  *	@param port - the port number. 
			  *	 
			  *	@exception  UnknownHostException - if the IP address of the host could not be determined. 
			  *	@exception  IOException - if an I/O error occurs when creating the socket. 
			  *	@exception  SecurityException - if a security manager exists and its checkConnect method 
			  * doesn't allow the operation.
			  *	
			  *	@see setSocketImplFactory(java.net.SocketImplFactory)
			  * @see SocketImpl, 
			  * @see SocketImplFactory.createSocketImpl(), 
			  * @see SecurityManager.checkConnect(java.lang.String, int)
			  */
			Socket(const std::string& host, int port) throw(net::SocketException*); 

			/** Creates a stream socket and connects it to the specified port number at 
			  * the specified IP address. 
			  *	If the application has specified a socket factory, that factory's 
			  * createSocketImpl method is called to create the actual socket implementation. 
			  * Otherwise a "plain" socket is created. 
			  *	If there is a security manager, its checkConnect method is called with the host 
			  * address and port as its arguments. This could result in a SecurityException. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param address - the IP address.
			  *	@param port - the port number. 
			  *	 
			  *	@exception  IOException - if an I/O error occurs when creating the socket. 
			  *	@exception  SecurityException - if a security manager exists and its checkConnect 
			  * method doesn't allow the operation.
			  *
			  *	@see setSocketImplFactory(java.net.SocketImplFactory)
			  * @see  SocketImpl
			  * @see SocketImplFactory.createSocketImpl()
			  * @see SecurityManager.checkConnect(java.lang.String, int)
			  */
			Socket(const InetAddress& address, int port) throw(net::SocketException*);

			/** Creates a socket and connects it to the specified remote host on the 
			  * specified remote port. The Socket will also bind() to the local address 
			  * and port supplied.
			  *	If the specified host is null it is the equivalent of specifying the 
			  * address as InetAddress.getByName(null). In other words, it is equivalent
			  * to specifying an address of the loopback interface. 
			  *	If there is a security manager, its checkConnect method is called with
			  * the host address and port as its arguments. This could result in a
			  * SecurityException. 
			  *
			  *	@param host - the name of the remote host, or null for the loopback address.
			  *	@param port - the remote port
			  *	@param localAddr - the local address the socket is bound to
			  *	@param localPort - the local port the socket is bound to 
			  *	
			  *	@exception  IOException - if an I/O error occurs when creating the socket. 
			  *	@exception  SecurityException - if a security manager exists and its checkConnect 
			  * method doesn't allow the operation.
			  *	
			  *	@see SecurityManager.checkConnect(java.lang.String, int)
			  */
			Socket(const std::string& host, int port, const InetAddress& localAddr, int localPort) throw(net::SocketException*);

			/** Creates a socket and connects it to the specified remote address on the 
			  * specified remote port. The Socket will also bind() to the local address 
			  * and port supplied. 
			  *	If there is a security manager, its checkConnect method is called with 
			  * the host address and port as its arguments. This could result in a 
			  * SecurityException. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param address - the remote address
			  *	@param port - the remote port
			  *	@param localAddr - the local address the socket is bound to
			  *	@param localPort - the local port the socket is bound to 
			  * 
			  *	@exception  IOException - if an I/O error occurs when creating the socket. 
			  *	@exception  SecurityException - if a security manager exists and its checkConnect 
			  * method doesn't allow the operation.
			  *	
			  *	@see SecurityManager.checkConnect(java.lang.String, int)
			  */
			Socket(const InetAddress& address, int port, const InetAddress& localAddr,
													int localPort); // throw IOException;
			/// Destructor
			virtual ~Socket();

			/** Connects this socket to the server. 
			  *
			  *	@param endpoint - the SocketAddress 
			  *	 
			  *	@exception  IOException - if an error occurs during the connection 
			  *	@exception  IllegalBlockingModeException - if this socket has an associated channel,
			  * and the channel is in non-blocking mode 
			  *	@exception  IllegalArgumentException - if endpoint is null or is a SocketAddress 
			  * subclass not supported by this socket
			  */
			void connect(const SocketAddress& endpoint) throw(net::SocketException*);

			/** Connects this socket to the server with a specified timeout value. 
			  * A timeout of zero is interpreted as an infinite timeout. 
			  * The connection will then block until established or an error occurs. 
			  *	
			  *	@param endpoint - the SocketAddress
			  *	@param timeout - the timeout value to be used in milliseconds. 
			  *	 
			  *	@exception  IOException - if an error occurs during the connection 
			  *	@exception  SocketTimeoutException - if timeout expires before connecting 
			  *	@exception  IllegalBlockingModeException - if this socket has an associated channel, 
			  * and the channel is in non-blocking mode 
			  *	@exception  IllegalArgumentException - if endpoint is null or is a SocketAddress 
			  * subclass not supported by this socket
			  */
			void connect(const SocketAddress& endpoint, int timeout) throw(net::SocketException*);

			/** Binds the socket to a local address. 
			  *	If the address is null, then the system will pick up an ephemeral port 
			  * and a valid local address to bind the socket. 
			  *	
			  *	@param bindpoint - the SocketAddress to bind to 
			  *	 
			  *	@exception  IOException - if the bind operation fails, or if the socket is already bound. 
			  *	@exception  IllegalArgumentException - if bindpoint is a SocketAddress subclass not 
			  * supported by this socket
			  *	
			  *	@see isBound()
			  */
			void bind(const SocketAddress& bindpoint) throw(net::SocketException*);

			/** Returns the address to which the socket is connected. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the remote IP address to which this socket is connected, or null if the 
			  * socket is not connected.
			  */
			const InetAddress& getInetAddress() const;

			/** Gets the local address to which the socket is bound. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the local address to which the socket is bound or InetAddress.anyLocalAddress() 
			  * if the socket is not bound yet.
			  */
			const InetAddress& getLocalAddress() const;

			/** Returns the remote port to which this socket is connected.
			  *
			  *	@return the remote port number to which this socket is connected, or 0 if the 
			  * socket is not connected yet.
			  */
			int getPort() const;


			/**Returns the local port to which this socket is bound. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the local port number to which this socket is bound or -1 if the socket 
			  * is not bound yet.
			  */
			int getLocalPort() const;


			/**Returns the address of the endpoint this socket is connected to, or null 
			  * if it is unconnected. 
			  *
			  *	@return a SocketAddress reprensenting the remote endpoint of this socket, or null 
			  * if it is not connected yet.
			  *	
			  *	@see getInetAddress()
			  *	@see getPort()
			  *	@see connect(SocketAddress, int)
			  *	@see connect(SocketAddress)
			  */
			const SocketAddress& getRemoteSocketAddress() const;

			/** Returns the address of the endpoint this socket is bound to, or null if 
			  * it is not bound yet. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return a SocketAddress representing the local endpoint of this socket, or null 
			  * if it is not bound yet.
			  *
			  *	@see getLocalAddress()
			  *	@see getLocalPort()
			  *	@see bind(SocketAddress)
			  */
			const SocketAddress& getLocalSocketAddress() const;

			/**Returns the unique SocketChannel object associated with this socket, if any. 
			  *	A socket will have a channel if, and only if, the channel itself was 
			  * created via the SocketChannel.open or ServerSocketChannel.accept methods. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the socket channel associated with this socket, or null if this socket 
			  * was not created for a channel
			  */
			const SocketChannel& getChannel() const;
			
			/** Returns an input stream for this socket. 
			  *	If this socket has an associated channel then the resulting input stream 
			  * delegates all of its operations to the channel. If the channel is in 
			  * non-blocking mode then the input stream's read operations will throw an 
			  * IllegalBlockingModeException. 
			  *	Under abnormal conditions the underlying connection may be broken by the 
			  * remote host or the network software (for example a connection reset in 
			  * the case of TCP connections). When a broken connection is detected by the
			  * network software the following applies to the returned input stream :- 
			  *	The network software may discard bytes that are buffered by the socket. 
			  * Bytes that aren't discarded by the network software can be read using read. 
			  *	If there are no bytes buffered on the socket, or all buffered bytes have 
			  * been consumed by read, then all subsequent calls to read will throw an IOException. 
			  *	If there are no bytes buffered on the socket, and the socket has not been
			  * closed using close, then available will return 0. 
			  *	
			  *	@return an input stream for reading bytes from this socket. 
			  *	
			  *	@exception  IOException - if an I/O error occurs when creating the input stream, the 
			  * socket is closed, the socket is not connected, or the socket input has been 
			  * shutdown using shutdownInput()
			  */
			istream& getInputStream() throw(net::SocketException*);

			/** Returns an output stream for this socket. 
			  *	If this socket has an associated channel then the resulting output 
			  * stream delegates all of its operations to the channel. If the channel 
			  * is in non-blocking mode then the output stream's write operations will 
			  * throw an IllegalBlockingModeException. 
			  *	
			  *	@return an output stream for writing bytes to this socket. 
			  *	
			  *	@exception  IOException - if an I/O error occurs when creating the output stream or
			  * if the socket is not connected.
			  */
			ostream& getOutputStream() throw(net::SocketException*);

			/** Enable/disable TCP_NODELAY (disable/enable Nagle's algorithm). 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param on - true to enable TCP_NODELAY, false to disable. 
			  *	 
			  *	@exception  SocketException - if there is an error in the underlying protocol, such as a TCP error.
			  *	
			  *	@see getTcpNoDelay()
			  */
			void setTcpNoDelay(bool on) throw(net::SocketException*);

			/** Tests if TCP_NODELAY is enabled. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return a bool indicating whether or not TCP_NODELAY is enabled. 
			  *	
			  *	@exception  SocketException - if there is an error in the underlying protocol, 
			  * such as a TCP error.
			  *	
			  *	@see setTcpNoDelay(bool)
			  */
			bool getTcpNoDelay() throw(net::SocketException*);

			/** Enable/disable SO_LINGER with the specified linger time in seconds. 
			  * The maximum timeout value is platform specific. The setting only 
			  * affects socket close. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param on - whether or not to linger on.
			  *	@param linger - how long to linger for, if on is true. 
			  *	 
			  *	@exception  SocketException - if there is an error in the underlying protocol, 
			  * such as a TCP error. 
			  *	@param IllegalArgumentException - if the linger value is negative.
			  *	
			  *	@see getSoLinger()
			  */
			void setSoLinger(bool on, int linger) throw(net::SocketException*);

			/** Returns setting for SO_LINGER. -1 returns implies that the option is
			  * disabled. The setting only affects socket close. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the setting for SO_LINGER. 
			  *	
			  *	@exception  SocketException - if there is an error in the underlying protocol, 
			  * such as a TCP error.
			  *	
			  *	@see setSoLinger(bool, int)
			  */
			int getSoLinger() throw(net::SocketException*);

			/** Send one byte of urgent data on the socket. The byte to be sent is the 
			  * lowest eight bits of the data parameter. The urgent byte is sent after 
			  * any preceding writes to the socket OutputStream and before any future writes 
			  * to the OutputStream. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param data - The byte of data to send 
			  *	 
			  *	@exception  IOException - if there is an error sending the data.
			  */
			void sendUrgentData(int data) throw(net::SocketException*);

			/** Enable/disable OOBINLINE (receipt of TCP urgent data) By default, this
			  * option is disabled and TCP urgent data received on a socket is silently
			  * discarded. If the user wishes to receive urgent data, then this option must
			  * be enabled. When enabled, urgent data is received inline with normal data. 
			  *	Note, only limited support is provided for handling incoming urgent data. 
			  * In particular, no notification of incoming urgent data is provided and there
			  * is no capability to distinguish between normal data and urgent data unless
			  * provided by a higher level protocol. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param on - true to enable OOBINLINE, false to disable. 
			  *	 
			  *	@exception  SocketException - if there is an error in the underlying protocol,
			  * such as a TCP error.
			  *	
			  *	@see getOOBInline()
			  */
			void setOOBInline(bool on) throw(net::SocketException*);

			/** Tests if OOBINLINE is enabled. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return a bool indicating whether or not OOBINLINE is enabled. 
			  *	
			  *	@exception  SocketException - if there is an error in the underlying protocol, 
			  * such as a TCP error.
			  *	
			  *	@see setOOBInline(bool)
			  */
			bool getOOBInline() throw(net::SocketException*);

			/** Enable/disable SO_TIMEOUT with the specified timeout, in milliseconds. 
			  * With this option set to a non-zero timeout, a read() call on the 
			  * InputStream associated with this Socket will block for only this amount 
			  * of time. If the timeout expires, a java.net.SocketTimeoutException is 
			  * raised, though the Socket is still valid. The option must be enabled 
			  * prior to entering the blocking operation to have effect. The timeout 
			  * must be > 0. A timeout of zero is interpreted as an infinite timeout. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param timeout - the specified timeout, in milliseconds. 
			  *	 
			  *	@exception  SocketException - if there is an error in the underlying protocol, 
			  * such as a TCP error.
			  *	
			  *	@see getSoTimeout()
			  */
			void setSoTimeout(int timeout) throw(net::SocketException*);

			/** Returns setting for SO_TIMEOUT. 0 returns implies that the option is
			  * disabled (i.e., timeout of infinity). 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the setting for SO_TIMEOUT 
			  *	
			  *	@exception  SocketException - if there is an error in the underlying protocol, 
			  * such as a TCP error.
			  *	
			  *	@see setSoTimeout(int)
			  */
			int getSoTimeout() throw(net::SocketException*);

			/** Sets the SO_SNDBUF option to the specified value for this Socket. 
			  * The SO_SNDBUF option is used by the platform's networking code as 
			  * a hint for the size to set the underlying network I/O buffers. 
			  *	Because SO_SNDBUF is a hint, applications that want to verify what 
			  * size the buffers were set to should call getSendBufferSize(). 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param size - the size to which to set the send buffer size. This value must
			  * be greater than 0. 
			  *	 
			  *	@exception  SocketException - if there is an error in the underlying protocol, such 
			  * as a TCP error. 
			  *	@exception  IllegalArgumentException - if the value is 0 or is negative.
			  *	
			  *	@see getSendBufferSize()
			  */
			void setSendBufferSize(int size) throw(net::SocketException*);

			/** Get value of the SO_SNDBUF option for this Socket, that is the buffer
			  * size used by the platform for output on this Socket. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the value of the SO_SNDBUF option for this Socket. 
			  *	
			  *	@exception  SocketException - if there is an error in the underlying protocol, such 
			  * as a TCP error.
			  *	
			  *	@see setSendBufferSize(int)
			  */
			int getSendBufferSize() throw(net::SocketException*);

			/** Sets the SO_RCVBUF option to the specified value for this Socket. The 
			  * SO_RCVBUF option is used by the platform's networking code as a hint 
			  * for the size to set the underlying network I/O buffers. 
			  *	Increasing the receive buffer size can increase the performance of 
			  * network I/O for high-volume connection, while decreasing it can help 
			  * reduce the backlog of incoming data. 
			  *	Because SO_RCVBUF is a hint, applications that want to verify what size 
			  * the buffers were set to should call getReceiveBufferSize(). 
			  *	The value of SO_RCVBUF is also used to set the TCP receive window that is 
			  * advertized to the remote peer. Generally, the window size can be modified 
			  * at any time when a socket is connected. However, if a receive window larger 
			  * than 64K is required then this must be requested before the socket is 
			  * connected to the remote peer. There are two cases to be aware of:
			  *	For sockets accepted from a ServerSocket, this must be done by calling 
			  * ServerSocket.setReceiveBufferSize(int) before the ServerSocket is bound
			  * to a local address.
			  *	For client sockets, setReceiveBufferSize() must be called before 
			  * connecting the socket to its remote peer.
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param size - the size to which to set the receive buffer size. This value 
			  * must be greater than 0. 
			  *	 
			  *	@exception  IllegalArgumentException - if the value is 0 or is negative. 
			  *	@exception  SocketException - if there is an error in the underlying protocol, such 
			  * as a TCP error.
			  *	
			  *	@see getReceiveBufferSize()
			  *	@see ServerSocket.setReceiveBufferSize(int)
			  */
			void setReceiveBufferSize(int size) throw(net::SocketException*);

			/** Gets the value of the SO_RCVBUF option for this Socket, that is the 
			  * buffer size used by the platform for input on this Socket. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the value of the SO_RCVBUF option for this Socket. 
			  *	
			  *	@exception  SocketException - if there is an error in the underlying protocol, such 
			  * as a TCP error.
			  *	
			  *	@see setReceiveBufferSize(int)
			  */
			int getReceiveBufferSize() throw(net::SocketException*);

			/** Enable/disable SO_KEEPALIVE. 
			  *	
			  *	@param on - whether or not to have socket keep alive turned on. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@exception  SocketException - if there is an error in the underlying protocol, such 
			  * as a TCP error.
			  *	
			  *	@see getKeepAlive()
			  */
			void setKeepAlive(bool on) throw(net::SocketException*);

			/** Tests if SO_KEEPALIVE is enabled. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return a bool indicating whether or not SO_KEEPALIVE is enabled. 
			  *	
			  *	@exception  SocketException - if there is an error in the underlying protocol, such 
			  * as a TCP error.
			  *	
			  *	@see setKeepAlive(bool)
			  */
			bool getKeepAlive() throw(net::SocketException*);

			/** Sets traffic class or type-of-service octet in the IP header for packets
			  * sent from this Socket. As the underlying network implementation may 
			  * ignore this value applications should consider it a hint. 
			  *	The tc must be in the range 0 <= tc <= 255 or an 
			  * IllegalArgumentException will be thrown. 
			  *	@doc Notes: 
			  *	for Internet Protocol v4 the value consists of an octet with precedence
			  * and TOS fields as detailed in RFC 1349. The TOS field is bitset created
			  * by bitwise-or'ing values such the following :- 
			  *	IPTOS_LOWCOST (0x02) 
			  *	IPTOS_RELIABILITY (0x04) 
			  *	IPTOS_THROUGHPUT (0x08) 
			  *	IPTOS_LOWDELAY (0x10) 
			  *	The last low order bit is always ignored as this corresponds to the MBZ 
			  * (must be zero) bit. 
			  *	Setting bits in the precedence field may result in a SocketException 
			  * indicating that the operation is not permitted. 
			  *	for Internet Protocol v6 tc is the value that would be placed into the 
			  * sin6_flowinfo field of the IP header. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param tc - an int value for the bitset. 
			  *	
			  *	@exception  SocketException - if there is an error setting the traffic class or 
			  * type-of-service
			  *	
			  *	@see getTrafficClass()
			  */
			void setTrafficClass(int tc) throw(net::SocketException*);

			/** Gets traffic class or type-of-service in the IP header for packets sent 
			  * from this Socket 
			  *	As the underlying network implementation may ignore the traffic class or
			  * type-of-service set using #setTrafficClass() this method may return a 
			  * different value than was previously set using the #setTrafficClass() 
			  * method on this Socket. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return the traffic class or type-of-service already set 
			  *	
			  *	@exception  SocketException - if there is an error obtaining the traffic class or 
			  * type-of-service value.
			  *	
			  *	@see setTrafficClass(int)
			  */
			int getTrafficClass() throw(net::SocketException*);

			/** Enable/disable the SO_REUSEADDR socket option. 
			  *	When a TCP connection is closed the connection may remain in a timeout
			  * state for a period of time after the connection is closed (typically
			  * known as the TIME_WAIT state or 2MSL wait state). For applications using
			  * a well known socket address or port it may not be possible to bind a 
			  * socket to the required SocketAddress if there is a connection in the
			  * timeout state involving the socket address or port. 
			  *	Enabling SO_REUSEADDR prior to binding the socket using 
			  * bind(SocketAddress) allows the socket to be bound even though a previous
			  * connection is in a timeout state. 
			  *	When a Socket is created the initial setting of SO_REUSEADDR is disabled. 
			  *	The behaviour when SO_REUSEADDR is enabled or disabled after a socket is 
			  * bound (See isBound()) is not defined. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@param on - whether to enable or disable the socket option 
			  *	 
			  *	@thorw SocketException - if an error occurs enabling or disabling the SO_RESUEADDR 
			  * socket option, or the socket is closed.
			  *	
			  *	@see getReuseAddress()
			  *	@see bind(SocketAddress)
			  *	@see isClosed()
			  *	@see isBound()
			  */
			void setReuseAddress(bool on) throw(net::SocketException*);

			/** Tests if SO_REUSEADDR is enabled. 
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return a bool indicating whether or not SO_REUSEADDR is enabled. 
			  *	
			  *	@exception  SocketException - if there is an error in the underlying protocol, such 
			  * as a TCP error.
			  *	
			  *	@see setReuseAddress(bool)
			  */
			bool getReuseAddress() throw(net::SocketException*);

			/** Closes this socket.
			  *	Any thread currently blocked in an I/O operation upon this socket will
			  * throw a SocketException. 
			  *	Once a socket has been closed, it is not available for further networking
			  * use (i.e. can't be reconnected or rebound). A new socket needs to be created. 
			  *	If this socket has an associated channel then the channel is closed as well. 
			  *	
			  *	@exception  IOException - if an I/O error occurs when closing this socket.
			  *	
			  *	@see isClosed()
			  */
			void close() throw(net::SocketException*);

			/** Places the input stream for this socket at "end of stream". Any data 
			  * sent to the input stream side of the socket is acknowledged and then 
			  * silently discarded. 
			  *	If you read from a socket input stream after invoking shutdownInput() 
			  * on the socket, the stream will return EOF. 
			  *	
			  *	@exception  IOException - if an I/O error occurs when shutting down this socket.
			  *	
			  *	@see shutdownOutput()
			  *	@see close()
			  *	@see setSoLinger(bool, int)
			  *	@see isInputShutdown()
			  */
			void shutdownInput() throw(net::SocketException*);

			/** Disables the output stream for this socket. For a TCP socket, any 
			  * previously written data will be sent followed by TCP's normal connection
			  * termination sequence. If you write to a socket output stream after 
			  * invoking shutdownOutput() on the socket, the stream will throw an IOException. 
			  *	
			  *	@exception  IOException - if an I/O error occurs when shutting down this socket.
			  *	
			  *	@see shutdownInput()
			  *	@see close()
			  *	@see setSoLinger(bool, int)
			  *	@see isOutputShutdown()
			  */
			void shutdownOutput() throw(net::SocketException*);

			/** Converts this socket to a String. Overrides: toString in class Object
			  *	
			  * @memo NOT SUPPOTED by this version.
			  *
			  *	@return a string representation of this socket.
			  */
			const std::string& toString() const;


			/** Returns the connection state of the socket.
			  *	
			  *	@return true if the socket successfuly connected to a server
			  */
			bool isConnected() const; 

			/** Returns the binding state of the socket. 
			  *	
			  *	@return true if the socket successfuly bound to an address
			  *	
			  *	@see bind(java.net.SocketAddress)
			  */
			bool isBound() const;

			/** Returns the closed state of the socket. 
			  *	
			  *	@return true if the socket has been closed
			  *	
			  *	@see close()
			  */
			bool isClosed() const;

			/** Returns wether the read-half of the socket connection is closed.
			  *	
			  *	@return true if the input of the socket has been shutdown
			  *	
			  *	@see shutdownInput()
			  */
			bool isInputShutdown() const; 

			/** Returns wether the write-half of the socket connection is closed. 
			  *	
			  *	@return true if the output of the socket has been shutdown
			  *	
			  *	@see shutdownOutput()
			  */
			bool isOutputShutdown() const;

			/** Sets the client socket implementation factory for the application.
			  * The factory can be specified only once. 
			  *	When an application creates a new client socket, the socket 
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
			  *	@exception  IOException - if an I/O error occurs when setting the socket factory. 
			  *	@exception  SocketException - if the factory is already defined. 
			  *	@exception  SecurityException - if a security manager exists and its checkSetFactory 
			  * method doesn't allow the operation.
			  *	
			  *	@see SocketImplFactory.createSocketImpl()
			  *	@see SecurityManager.checkSetFactory()
			  */
			static void setSocketImplFactory(const SocketImplFactory& fac) throw(net::SocketException*);

		protected:
			/** Creates an unconnected Socket with a user-specified SocketImpl.
			  *	
			  *	@param impl - an instance of a SocketImpl the subclass wishes to use on the Socket. 
			  *	 
			  *	@exception  SocketException - if there is an error in the underlying protocol, such as a TCP error.
			  */
			 Socket(SocketImpl& impl) throw(SocketException*);

			/** Creates an unconnected Socket with a user-specified SOCKET handle.
			  *	
			  *	@param socket - an socket handle. 
			  */
			 Socket(SOCKET socket) 
				 : mSocket(socket), mSocketbuf(socket), mpInput(NULL), 
				 mpOutput(NULL), mState(cConnected) {};

			/** Initialize socket environment.
			  *	
			  *	@exception  SocketException - if there is an error in socket initialization.
			  */
			 static void InitializeSocket() throw(SocketException*);

		private:
			friend class ServerSocket;

			/// socket states
			enum State {cConnected = 1, cBound = 2, cClosed = 4, cInputShutdown = 8, cOutputShutdown = 16};

			/// socket handle
			SOCKET			mSocket;

			/// the socket address
			SocketAddress	mAddress;

			/// a stream buffer implements the socket
			socketbuf		mSocketbuf;

			/// socket's current state
			int			mState;

			/// socket's input stream
			istream*	mpInput;

			/// socket's output stream
			ostream*	mpOutput;

			/// socket initialization result
			static int gmResult;

			#ifdef WIN32
				/// windows socket initialization data
				static WSADATA gmWsaData;
			#endif
		};
	}	// namespace net
}	// namespace java

#endif	//java_net_Socket_h