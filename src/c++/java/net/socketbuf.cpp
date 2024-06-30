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
 * File:		socketbuf.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030304	nmv			create
 *----------------------------------------------------------------------------*/

#include "socketbuf.h"
#include <inexum/util/Debug.h>

using namespace inexum::util;
using namespace java::net;

socketbuf::socketbuf()
: mSocket(0)
{
	debug_method(DebugMethod(Debug::c_net, "socketbuf", "socketbuf"));
	int size = allocate();
}

socketbuf::socketbuf(SOCKET socket)
: mSocket(socket)
{
	debug_method(DebugMethod(Debug::c_net, "socketbuf", "socketbuf",
								"SOCKET socket"));
	int size = allocate();
}

socketbuf::~socketbuf()
{
	delete[] pbase();
	delete[] eback();
}

int socketbuf::overflow(int chr) 
{
	debug_method(DebugMethod(Debug::c_net, "socketbuf", "overflow",
								"c: '%c'", chr));
	// Make sure there is a holding area
	if(allocate() == EOF)
		return EOF;

	if(mSocket == 0)
		return(EOF);

	// Make sure there is a put area
	if(!pptr())
	 	setp(pbase(), epptr()-1);

	// If c is not EOF it is a character that must
	// also be consumed.
	if(chr != EOF)
   		// We always leave space
   		*pptr() = chr;

	pbump(1);
	return(chr);
}

int socketbuf::underflow() 
{
	int chr(0);
	debug_method(DebugMethod(Debug::c_net, "socketbuf", "underflow", "%c", &chr));
	// Make sure there is a holding area.
	if (allocate()==EOF)
		return EOF ;

	if(mSocket == 0)
		return(EOF);

	// if buffer is empty, read from a socket
	if(in_avail() == 0)
	{
		// something is writen into the buffer
		if(receiveTest())
		{
			int recvBytes = recv(mSocket, eback(), BUFSIZ, 0);
			debug_line(DebugLine( Debug::c_net, "received:'%s', recvBytes: '%d'", 
						(hexadecimal((const byte*)eback(), recvBytes, false)).c_str(), recvBytes ) );
			if(recvBytes > 0)
   				setg(eback(), eback(), eback() + recvBytes);
			else
				return(EOF);
		}
		else
			return(EOF);
	}
	// get a character from a buffer
	chr = (int)(byte)*gptr();

	// if the 'space' is last character in the buffer move pointer to teh next
	// character
	if(gptr()+1 == egptr() && chr == ' ') 
		gbump(1);

	return chr;
}


int socketbuf::sync()
{
	debug_method(DebugMethod(Debug::c_net, "socketbuf", "sync"));
	if(pptr() && (pptr() > pbase()) && sendTest()) 
	{
		int sendSize = pptr() - pbase();
		send(mSocket, pbase(), sendSize, 0);
		debug_line(DebugLine( Debug::c_net, "sent:'%s', sentBytes: '%d'", 
						(hexadecimal((const byte*)pbase(), sendSize, false)).c_str(), sendSize ) );
		setp(pbase(),epptr());
	}
	return(0);
}

bool socketbuf::receiveTest() const
{
	debug_method(DebugMethod(Debug::c_net, "socketbuf", "receiveTest"));
	fd_set readfds = {1, {mSocket} };
	timeval timeout = {200, 200};
	int sCount = select( 0, &readfds, NULL, NULL, NULL);
	return(sCount == 1);
}

bool socketbuf::sendTest() const
{
	debug_method(DebugMethod(Debug::c_net, "socketbuf", "sendTest"));
	fd_set writefds = {1, {mSocket} };
	timeval timeout = {200, 200};
	int sCount = select( 0, NULL, &writefds, NULL, NULL);
	return(sCount == 1);
}

//#ifndef WIN32
    int socketbuf::allocate()
    {
            if (eback() || pbase())
                    return 0;
            return(socketbuf::doallocate());
    }

    int socketbuf::doallocate()
    {
            char * pptr;
            char * gptr;
            if (!(pptr = new char[BUFSIZ]))
                    return(EOF);
            if (!(gptr = new char[BUFSIZ]))
            {
                    delete pptr;
                    return(EOF);
            }
            setp(pptr, pptr + BUFSIZ);
            setg(gptr, gptr + BUFSIZ, gptr + BUFSIZ);
            return(1);
    }
//#endif	// WIN32
