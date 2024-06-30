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
 * File:		SocketAddress.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030303	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef java_net_SocketAddress_h
#define java_net_SocketAddress_h

#ifdef _WINDOWS
    #include <winsock2.h>
#else
    #include <sys/socket.h>
	#include <arpa/inet.h>
#endif

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
		/** A C++ implementation of Java like java/net/SocketAddress class.
		  * This class represents a Socket Address with no protocol attachment.
		  * As an abstract class, it is meant to be subclassed with a specific,
		  * protocol dependent, implementation. 
		  * It provides an immutable object used by sockets for binding, 
		  * connecting, or as returned values.
		  *
		  * Refer to SUN's documentation for Java class SocketAddress
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier SocketAddress
		{
		public:
			/// Default constructor
			SocketAddress() 
			{
				mAddress.sin_family = AF_INET;
				mAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
				mAddress.sin_port = htons(0);
			};

			/// Copy constructor
			SocketAddress(const SocketAddress& right) : mAddress(right.mAddress) {};

			/** Create a socket address for host name and port.
			  *
			  *	@param host - a string containing host name 
			  *	@param port - the socket port number
			  */
			SocketAddress(const std::string& host, int port)
			{
				mAddress.sin_family = AF_INET;
				mAddress.sin_addr.s_addr = inet_addr(host.c_str());
				mAddress.sin_port = htons(port);
			};


			/** Create a socket address for localhost and specified port.
			  *
			  *	@param port - the socket port number on a localhost
			  */
			SocketAddress(int port)
			{
				mAddress.sin_family = AF_INET;
				mAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
				mAddress.sin_port = htons( port );
			};

			/** Create a socket address base on specified socket_in address format.
			  *
			  *	@param address - socket addres in socket_in format
			  */
			SocketAddress(const sockaddr_in& address) :mAddress(address) {};

			/// socketaddr type constantant pointer operator
			operator const sockaddr*() const {return((sockaddr*)&mAddress); };

			/// socketaddr type constantantreference operator
			operator const sockaddr&() const {return(*(sockaddr*)&mAddress); };

			/// socketaddr type pointer operator
			operator sockaddr*() const {return((sockaddr*)&mAddress); };

			/** A socket address poprt getter.
			  *
			  *	@return a port numebr
			  */
			int getPort() const { return(mAddress.sin_port); };

		private:
			/// Socket address
			sockaddr_in	mAddress;
		};
	}	// namespace net
}	// namespace java

#endif	// java_net_SocketAddress_h