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
 * File:		ServerSocket.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#include "inexum/definitions.h"
 // disable warning C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
#pragma warning (disable : 4290)

#include "ServerSocket.h"
#include "Socket.h"
#include <inexum/util/Debug.h>

#ifdef _WINDOWS
    typedef int socklen_t;
#else
    #define closesocket(s) shutdown(s, SHUT_RDWR)
#endif

using namespace inexum::util;

java::net::ServerSocket::ServerSocket() throw(SocketException*)
:mState(cClosed)
{
	debug_method(DebugMethod(Debug::c_net, "ServerSocket", "ServerSocket"));
	Socket::InitializeSocket();
    mServerSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (mServerSocket == INVALID_SOCKET) 
		throw new SocketException();
}

java::net::ServerSocket::ServerSocket(int port) throw(SocketException*)
:mAddress(port), mState(cClosed)
{
	debug_method(DebugMethod(Debug::c_net, "ServerSocket", "ServerSocket",
					"port: '%d'", port));
	Socket::InitializeSocket();
    mServerSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (mServerSocket == INVALID_SOCKET) 
		throw new SocketException();

	bind(mAddress);
}

java::net::ServerSocket::ServerSocket(int port, int backlog) throw(SocketException*)
:mAddress(port), mState(cClosed)
{
	debug_method(DebugMethod(Debug::c_net, "ServerSocket", "ServerSocket",
					"port: '%d', backlog: '%d'", port, backlog));
	Socket::InitializeSocket();
    mServerSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (mServerSocket == INVALID_SOCKET) 
		throw new SocketException();

	bind(mAddress, backlog);
}

java::net::ServerSocket::ServerSocket(int port, int backlog, const InetAddress& bindAddr)
										throw(SocketException*)
{
}

void java::net::ServerSocket::bind(const SocketAddress& endpoint) throw(SocketException*)
{
	debug_method(DebugMethod(Debug::c_net, "ServerSocket", "bind",
					"const SocketAddress& endpoint"));
	if(::bind(mServerSocket, endpoint, sizeof(endpoint)) == SOCKET_ERROR)
		throw new SocketException();
	if(::listen(mServerSocket, SOMAXCONN) == SOCKET_ERROR)
		throw new SocketException();
	mState = cBound;
}

void java::net::ServerSocket::bind(const SocketAddress& endpoint, int backlog) throw(SocketException*)
{
	debug_method(DebugMethod(Debug::c_net, "ServerSocket", "bind",
					"const SocketAddress& endpoint, int backlog"));
	bind(endpoint);
}

const java::net::InetAddress& java::net::ServerSocket::getInetAddress() const
{
	return(*(InetAddress*)NULL);
}

int java::net::ServerSocket::getLocalPort() const
{
	return(mAddress.getPort());
}

const java::net::SocketAddress& java::net::ServerSocket::getLocalSocketAddress() const
{
	return(mAddress);
}

java::net::Socket* java::net::ServerSocket::accept() throw(SocketException*)
{
	debug_method(DebugMethod(Debug::c_net, "ServerSocket", "accept"));
	socklen_t addressSize = sizeof(mAddress);
	SOCKET socket = ::accept(mServerSocket, mAddress, &addressSize);
	if(socket == SOCKET_ERROR)
		throw new SocketException;
	return(new Socket(socket));
}

void java::net::ServerSocket::close() throw(SocketException*)
{
	debug_method(DebugMethod(Debug::c_net, "ServerSocket", "close"));
	if(::closesocket(mServerSocket) == SOCKET_ERROR)
		throw new SocketException;
	mState = cClosed;
}

const java::net::ServerSocketChannel& java::net::ServerSocket::getChannel() const
{
	return(*(ServerSocketChannel*)NULL);
}

bool java::net::ServerSocket::isBound() const
{
	return(mState == cBound);
}

bool java::net::ServerSocket::isClosed() const
{
	return(mState == cClosed);
}

void java::net::ServerSocket::setSoTimeout(int timeout) throw(SocketException*)
{
}

int java::net::ServerSocket::getSoTimeout() throw(SocketException*)
{
	return(0);
}

void java::net::ServerSocket::setReuseAddress(bool on) throw(SocketException*)
{
}

bool java::net::ServerSocket::getReuseAddress() const throw(SocketException*)
{
	return(false);
}

const std::string& java::net::ServerSocket::toString() const
{
	return(*(std::string*)NULL);
}

void java::net::ServerSocket::setSocketFactory(SocketImplFactory& fac) throw(SocketException*)
{
}

void java::net::ServerSocket::setReceiveBufferSize(int size) throw(SocketException*)
{
}

int java::net::ServerSocket::getReceiveBufferSize() const throw(SocketException*)
{
	return(0);
}

void java::net::ServerSocket::implAccept(Socket& s) throw(SocketException*)
{
}