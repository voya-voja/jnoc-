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
 * File:		JLong.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef iNexum_JLong_h
#define iNexum_JLong_h

#include <inexum/definitions.h>
#include <iostream>

/** iNexum classes.
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
namespace inexum
{

	/** Java long is 8 bytes long, while C++ long is 4 bytes.
	  *
	  * @see UnsignedJLong
	  *
	  * @author		iNexum System Inc.
	  *	@version	1.0.0
	  */
	#ifdef _WINDOWS
		typedef __int64                 JLong;
	#else
		typedef long long               JLong;
	#endif

	/** Java long is 8 bytes long, while C++ long is 4 bytes.
	  *
	  * @see JLong
	  *
	  * @author		iNexum System Inc.
	  *	@version	1.0.0
	  */
	#ifdef _WINDOWS
		typedef unsigned __int64        UnsignedJLong;
	#else
		typedef unsigned long long      UnsignedJLong;
	#endif

	/** Out stream operator for JLong.
	  *
	  * @param out - an output stream
	  *	@param value - a value of JLong (Java like 8 bytes long)
	  * @return the reference of out parameter.
	  *
	  * @see JLong
	  *
	  * @author		iNexum System Inc.
	  *	@version	1.0.0
	  */
	#ifdef _WINDOWS
		DeclarationSpecifier std::ostream& operator<<(std::ostream& out, const JLong& value );
	#endif
	/** Out stream operator for UnsignedJLong.
	  *
	  * @param out - an output stream
	  *	@param value - a value of UnsignedJLong (Java like 8 bytes long)
	  * @return the reference of out parameter.
	  *
	  * @see UnsignedJLong
	  *
	  * @author		iNexum System Inc.
	  *	@version	1.0.0
	  */
	#ifdef _WINDOWS
		DeclarationSpecifier std::ostream& operator<<(std::ostream& out, const UnsignedJLong& value );
	#endif
}	// namespace inexum

#endif	// iNexum_JLong_h

