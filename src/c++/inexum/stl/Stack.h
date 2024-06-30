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
 * File:		Stack.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					980912	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef inexum_stl_Stack_h
#define inexum_stl_Stack_h

/** iNexum classes.
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
namespace inexum
{
	/** Standard Template Library extensions.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
	namespace stl
	{
		/** The stack of pointers to the objects with garbage. At the 
		  * time of the destruction all contained objects wil be removed.
		  *
		  * @param T - the type of pointer elements
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template< class T >
		class StackPtr : public std::stack<T*>
		{
		public:
			typedef std::stack<T*>::iterator iterator;
			typedef std::stack<T*>::const_iterator const_iterator;

			/// The StackPtr destructor removes all the elements
			~StackPtr()
			{
				const_iterator theEnd = end();
				for( iterator at = begin(); at < theEnd; at++ )
				{
					delete *at;
				}
			}
		};
	}	// namespace stl
}	// namespace inexum

#endif	// inexum_stl_Stack_h
