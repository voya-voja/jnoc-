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
 * File:		IOException.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030303	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef java_io_IOException_h
#define java_io_IOException_h

#include <inexum/Throwable.h>

/** iNexum's java classes implemented in C++.
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
namespace java
{
	/** iNexum's java/io classes implemented in C++.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
	namespace io
	{
		/** iNexum's C++ implementation of a 'java/io/IOException' class.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class IOException : public java::lang::Exception
		{
		};
	}	// namespace io
}	// namespace java

#endif	// java_io_IOException_h