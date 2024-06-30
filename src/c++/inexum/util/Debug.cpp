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
 * File:		Debug.cpp
 * Description:	
 * Notes:
 *
 * Modification History:YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					980715	nmv			create
 *----------------------------------------------------------------------------*/
#include "inexum/definitions.h"

#include "Debug.h"

#ifdef iNxmDebug

ofstream	inexum::util::Debug::g_log( "debug.log" );

std::string	inexum::util::Debug::g_indent;

inexum::util::Debug::Mode inexum::util::Debug::g_mode = inexum::util::Debug::c_non; 

namespace inexum { 
	namespace util 
	{
		std::string hexadecimal(const byte* bytes, int size, bool number)
		{
			std::string hex;
			if(number)
			{
				for(int count = size - 1; count >= 0; count--)
				{
					byte b = bytes[ count ] & 0xf0;
					b >>= 4;
					if(b < 0x0a)
						hex += 0x30 + b;
					else
						hex += 0x61 + b - 0x0a;

					b = bytes[ count ] & 0x0f;
					if(b < 0x0a)
						hex += 0x30 + b;
					else
						hex += 0x61 + b - 0x0a;
				}
			}
			else
			{
				for(int count = 0; count < size; count++)
				{
					byte b = bytes[ count ] & 0xf0;
					b >>= 4;
					if(b < 0x0a)
						hex += 0x30 + b;
					else
						hex += 0x61 + b - 0x0a;

					b = bytes[ count ] & 0x0f;
					if(b < 0x0a)
						hex += 0x30 + b;
					else
						hex += 0x61 + b - 0x0a;
				}
			}
			return(hex);
		}
	} 
}

#endif	// iNxmDebug

