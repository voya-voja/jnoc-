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
 * File:		Types.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020615	nmv			create
 *----------------------------------------------------------------------------*/
#include "inexum/definitions.h"

#include "Types.h"

#include <iostream>

using namespace std;
using namespace inexum;

ostream& operator<<(ostream& out, const std::string& s)
{
	out << s.data();
	return(out);
}

#ifdef _WINDOWS
	ostream& inexum::operator<<(ostream& out, const JLong& value)
	{
		if(value >= 0)
			out << (const UnsignedJLong&)value;
		else
			out << '-' << (const UnsignedJLong&)(-value);
		return(out);
	}

	ostream& inexum::operator<<(ostream& out, const UnsignedJLong& value)
	{
		if(value == 0)
		{
			out << 0;
		}
		else
		{
			UnsignedJLong n(value);
			int digitCount = 0;
			while(n > 0)	// count the number of valid digits
			{
				digitCount++;
				n /= 10;
			}


			char* s = new char[digitCount + 1];
			s[ digitCount ] = '\0';
			n = value;
			for(int i = digitCount - 1; i >= 0; i--)
			{
				s[ i ] = n % 10 + '0';
				n /= 10;
			}
			out << s;
			delete s;
		}
		return(out);
	}
#endif	// _WINDOWS
