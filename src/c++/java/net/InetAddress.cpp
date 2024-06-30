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
 * File:		InetAddress.cpp
 * Description:	
 * Notes:
 *
 * Modification History:YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030715	nmv			create
 *----------------------------------------------------------------------------*/

#include "InetAddress.h"
#ifndef WIN32
	#include <arpa/inet.h>
#endif

bool java::net::InetAddress::isMulticastAddress() const
{
	return(false);
}

bool java::net::InetAddress::isAnyLocalAddress() const
{
	return(false);
}


bool java::net::InetAddress::isLoopbackAddress() const
{
	return(false);
}


bool java::net::InetAddress::isLinkLocalAddress() const
{
	return(false);
}


bool java::net::InetAddress::isSiteLocalAddress() const
{
	return(false);
}


bool java::net::InetAddress::isMCGlobal() const
{
	return(false);
}


bool java::net::InetAddress::isMCNodeLocal() const
{
	return(false);
}


bool java::net::InetAddress::isMCLinkLocal() const
{
	return(false);
}


bool java::net::InetAddress::isMCSiteLocal() const
{
	return(false);
}


bool java::net::InetAddress::isMCOrgLocal() const
{
	return(false);
}

std::string java::net::InetAddress::getHostName() const
{
	return(std::string(""));
}


std::string java::net::InetAddress::getCanonicalHostName() const
{
	return(std::string(""));
}


byte* java::net::InetAddress::getAddress() const
{
	return(NULL);
}


std::string java::net::InetAddress::getHostAddress() const
{
	return("");
}


int java::net::InetAddress::hashCode() const
{
	return(0);
}


bool java::net::InetAddress::equals(const void* obj) const
{
	return(false);
}


bool java::net::InetAddress::operator==(const InetAddress& right) const
{
	return(false);
}


std::string java::net::InetAddress::toString() const
{
	return("");
}


java::net::InetAddress::operator std::string() const
{
	return("");
}


java::net::InetAddress java::net::InetAddress::getByAddress(const std::string& host, byte* addr)
									throw(UnknownHostException*)
{
	return(InetAddress(host, addr));
}


java::net::InetAddress java::net::InetAddress::getByName(const std::string& host)
								throw(java::net::UnknownHostException*)
{
	return(InetAddress(inet_addr(host.c_str())));
}


std::vector<java::net::InetAddress> java::net::InetAddress::getAllByName(const std::string& host)
									throw(java::net::UnknownHostException*)
{
	return(*(std::vector<InetAddress>*)NULL);
}


java::net::InetAddress java::net::InetAddress::getByAddress(byte* addr)
							throw(java::net::UnknownHostException*)
{
	return(*(InetAddress*)NULL);
}


java::net::InetAddress java::net::InetAddress::getLocalHost() throw(java::net::UnknownHostException*)
{
	return(*(InetAddress*)NULL);
}


