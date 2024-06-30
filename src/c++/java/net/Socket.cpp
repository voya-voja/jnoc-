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
 * File:		Socket.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030304	nmv			create
 *----------------------------------------------------------------------------*/
#include "inexum/definitions.h"
 // disable warning C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
#pragma warning (disable : 4290)

#include "Socket.h"
#include "SocketException.h"
#include <inexum/util/Debug.h>

#ifndef _WINDOWS
    #include <tcl.h>

    #define Sleep(ms)		Tcl_Sleep(ms)
    #define closesocket(s)	shutdown(s, SHUT_RDWR)
    #define SD_RECEIVE		SHUT_RD
    #define SD_SEND			SHUT_WR
	#define NO_ERROR        0
#endif

using namespace inexum::util;

java::net::Socket::Socket() throw(java::net::SocketException*)
: mpInput(NULL), mpOutput(NULL), mState(cClosed)
{
	debug_method(DebugMethod(Debug::c_net, "Socket", "Socket"));
	Socket::InitializeSocket();
    mSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (mSocket == INVALID_SOCKET) 
		throw new SocketException();
}

java::net::Socket::Socket(SocketImpl& impl) throw(java::net::SocketException*)
: mpInput(NULL), mpOutput(NULL), mState(cClosed) 
{
	debug_method(DebugMethod(Debug::c_net, "Socket", "Socket",
					"SocketImpl& impl"));
}

java::net::Socket::Socket(const std::string& host, int port) throw(java::net::SocketException*)
:mAddress(host, port), mpInput(NULL), mpOutput(NULL), mState(cClosed)
{
	debug_method(DebugMethod(Debug::c_net, "Socket", "Socket",
					"host: '%s', port: '%d'", host.c_str(), port));
	Socket::InitializeSocket();
    mSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (mSocket == INVALID_SOCKET) 
		throw new SocketException();

	connect(mAddress);
}

java::net::Socket::Socket(const InetAddress& address, int port) throw(java::net::SocketException*)
: mpInput(NULL), mpOutput(NULL), mState(cClosed) 
{
}

java::net::Socket::Socket(const std::string& host, int port, const InetAddress& localAddr, int localPort) throw(java::net::SocketException*)
: mpInput(NULL), mpOutput(NULL), mState(cClosed) 
{
}

java::net::Socket::Socket(const InetAddress& address, int port, const InetAddress& localAddr,
											int localPort) throw(java::net::SocketException)
: mpInput(NULL), mpOutput(NULL), mState(cClosed) 
{
}

java::net::Socket::~Socket()
{
	if(mpInput != NULL)
		delete mpInput;

	if(mpOutput != NULL)
		delete mpOutput;
}

void java::net::Socket::connect(const SocketAddress& endpoint) throw(java::net::SocketException)
{
	debug_method(DebugMethod(Debug::c_net, "Socket", "connect",
					"const SocketAddress& endpoint"));
	if(::connect(mSocket, endpoint, sizeof(endpoint)) == SOCKET_ERROR)
		throw SocketException();
	mSocketbuf.bind(mSocket);
	mState |= cConnected;
}

void java::net::Socket::connect(const SocketAddress& endpoint, int timeout) throw(java::net::SocketException)
{
	debug_method(DebugMethod(Debug::c_net, "Socket", "connect",
					"const SocketAddress& endpoint, timeout '%d'", timeout));
	const int deltaTime = 50;
	int waited = 0;
	bool connected = false;
	while(!connected)
	{
		try
		{
			connect(endpoint);
			connected = true;
		}
		catch(java::net::SocketException* pExcept)
		{
			if(timeout != 0 && waited >= timeout)
				throw(pExcept);
			delete pExcept;
		}
		Sleep(deltaTime);
		waited += deltaTime;
	}
}

void java::net::Socket::bind(const SocketAddress& bindpoint) throw(java::net::SocketException*)
{
	debug_method(DebugMethod(Debug::c_net, "Socket", "bind",
					"const SocketAddress& endpoint"));
	if(::bind(mSocket, bindpoint, sizeof(bindpoint)) == SOCKET_ERROR)
		throw new SocketException();
	mSocketbuf.bind(mSocket);
	mState |= cBound;
}

const java::net::InetAddress& java::net::Socket::getInetAddress() const
{
	return(*(InetAddress*)NULL);
}

const java::net::InetAddress& java::net::Socket::getLocalAddress() const
{
	return(*(InetAddress*)NULL);
}

int java::net::Socket::getPort() const
{
	return(mAddress.getPort());
}

int java::net::Socket::getLocalPort() const
{
	return(0);
}

const java::net::SocketAddress& java::net::Socket::getRemoteSocketAddress() const
{
	return(mAddress);
}

const java::net::SocketAddress& java::net::Socket::getLocalSocketAddress() const
{
	return(*(SocketAddress*)NULL);
}

const java::net::SocketChannel& java::net::Socket::getChannel() const
{
	return(*(SocketChannel*)NULL);
}
	
std::istream& java::net::Socket::getInputStream() throw( java::net::SocketException*)
{
	debug_method(DebugMethod(Debug::c_net, "Socket", "getInputStream"));
	if(mpInput == NULL)
	{
		mpInput = new std::istream(&mSocketbuf);
	}
	return(*mpInput);
}

std::ostream& java::net::Socket::getOutputStream() throw( java::net::SocketException*)
{
	debug_method(DebugMethod(Debug::c_net, "Socket", "getOutputStream"));
	if(mpOutput == NULL)
	{
		mpOutput = new std::ostream(&mSocketbuf);
	}
	return(*mpOutput);
}

void java::net::Socket::setTcpNoDelay(bool on) throw(java::net::SocketException*)
{
}

bool java::net::Socket::getTcpNoDelay() throw(java::net::SocketException*)
{
	return(false);
}

void java::net::Socket::setSoLinger(bool on, int linger) throw(java::net::SocketException*)
{
}

int java::net::Socket::getSoLinger() throw(java::net::SocketException*)
{
	return(0);
}

void java::net::Socket::sendUrgentData(int data) throw(java::net::SocketException*)
{
}

void java::net::Socket::setOOBInline(bool on) throw(java::net::SocketException*)
{
}

bool java::net::Socket::getOOBInline() throw(java::net::SocketException*)
{
	return(false);
}

void java::net::Socket::setSoTimeout(int timeout) throw(java::net::SocketException*)
{
}

int java::net::Socket::getSoTimeout() throw(java::net::SocketException*)
{
	return(0);
}

void java::net::Socket::setSendBufferSize(int size) throw(java::net::SocketException*)
{
}

int java::net::Socket::getSendBufferSize() throw(java::net::SocketException*)
{
	return(0);
}

void java::net::Socket::setReceiveBufferSize(int size) throw(java::net::SocketException*)
{
}

int java::net::Socket::getReceiveBufferSize() throw(java::net::SocketException*)
{
	return(0);
}

void java::net::Socket::setKeepAlive(bool on) throw(java::net::SocketException*)
{
}

bool java::net::Socket::getKeepAlive() throw(java::net::SocketException*)
{
	return(false);
}

void java::net::Socket::setTrafficClass(int tc) throw(java::net::SocketException*)
{
}

int java::net::Socket::getTrafficClass() throw(java::net::SocketException*)
{
	return(0);
}

void java::net::Socket::setReuseAddress(bool on) throw(java::net::SocketException*)
{
}

bool java::net::Socket::getReuseAddress() throw(java::net::SocketException*)
{
	return(false);
}

void java::net::Socket::close() throw(java::net::SocketException*)
{
	debug_method(DebugMethod(Debug::c_net, "Socket", "close"));
	if(::closesocket(mSocket) == SOCKET_ERROR)
		throw new SocketException;
	mState |= cClosed;
}

void java::net::Socket::shutdownInput() throw(java::net::SocketException*)
{
	debug_method(DebugMethod(Debug::c_net, "Socket", "shutdownInput"));
	if(::shutdown(mSocket, SD_RECEIVE) == SOCKET_ERROR)
		throw new SocketException;
	mState |= cInputShutdown;
}

void java::net::Socket::shutdownOutput()
						throw(java::net::SocketException*)
{
	debug_method(DebugMethod(Debug::c_net, "Socket", "shutdownOutput"));
	if(::shutdown(mSocket, SD_SEND) == SOCKET_ERROR)
		throw new SocketException;
	mState |= cOutputShutdown;
}

const std::string& java::net::Socket::toString() const
{
	return(*(std::string*)NULL);
}

bool java::net::Socket::isConnected() const
{
	return((mState & cConnected) >0);
}

bool java::net::Socket::isBound() const
{
	return((mState & cBound) >0);
}

bool java::net::Socket::isClosed() const
{
	return((mState & cClosed) >0);
}

bool java::net::Socket::isInputShutdown() const
{
	return((mState & cInputShutdown) >0);
}

bool java::net::Socket::isOutputShutdown() const
{
	return((mState & cOutputShutdown) >0);
}

void java::net::Socket::setSocketImplFactory(const SocketImplFactory& fac) throw(java::net::SocketException*)
{
}

int java::net::Socket::gmResult = -1;
#ifdef _WINDOWS
	WSADATA java::net::Socket::gmWsaData;
#endif

void java::net::Socket::InitializeSocket() throw(SocketException*)
{
	debug_method(DebugMethod(Debug::c_net, "Socket", "InitializeSocket"));
    // Initialize Winsock.
	if(gmResult == -1)
	{
#ifdef _WINDOWS
		gmResult = WSAStartup( MAKEWORD(2,2), &gmWsaData );
#endif
		if ( gmResult != NO_ERROR )
			throw new SocketException();
	}
}
