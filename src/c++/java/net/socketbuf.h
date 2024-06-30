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
 * File:		socketbuf.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030303	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef java_net_socketbuf_h
#define java_net_socketbuf_h

#include <iostream>
#include <string>
#ifdef _WINDOWS
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    typedef int SOCKET;
#endif

#include <inexum/definitions.h>

class DeclarationSpecifier streambuf;

/** iNexum's java classes implemented in C++.
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
namespace java
{
	/** iNexum's java.net classes implemented in C++.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
	namespace net
	{
		class Socket;

		/** The specialization of streambuf class for writing into or reading
		  * from a socket. 
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier socketbuf : public std::streambuf
		{
		public:
			/// default constructor
			socketbuf();

			/** Overloaded constructor. Bind this instance of a streambuf to a 
			  * socket.
			  *
			  * @param socket - a socket handle
			  */
			socketbuf(SOCKET socket);

			/// destructor
			virtual ~socketbuf();

			/** Bind this instance of a streambuf to a socket.
			  *
			  * @param socket - a socket handle
			  */
			void bind(SOCKET socket) { mSocket = socket; };

		protected:
			/** Called on write streambuf overflow.
			  *
			  * @param chr - a character to be sent
			  */
			int overflow(int chr=EOF);

			/** Called on read streambuf underflow. Reads the data from a stream
			  * into a sockets input buffer.
			  *
			  * @return a character from a buffer
			  */
			int underflow();

			/** Called on streambuf synchronization. Sends the data stored in 
			  * output socket buffer.
			  *
			  * @return 0
			  */
			int sync();

			//#ifndef _WINDOWS
				/** Tries to set up a Reserve Area.  If one already exists, or if
				  * unbuffered, just returns 0.
				  *
				  * @return allocated size
				  */
				int allocate();

				/** Tries to set up a Reserve Area.  Returns EOF if unsuccessful.
				  *
				  * @return allocated size
				  */
				int doallocate();
			//#endif	// _WINDOWS
		private:
			/** Test does socket contains data sent from the other side.
			  *
			  * @return true if data available to be received, otherwise flase.
			  */
			bool receiveTest() const;

			/** Test the socket for the redines to receive data.
			  *
			  * @return true if socket ready for send, otherwise flase.
			  */
			bool sendTest() const;

			/// The socekt hanlde
			SOCKET mSocket;
		};
	}	// namespace net
}	// namespace java

#endif	// java_net_socketbuf_h