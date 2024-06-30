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
 * File:		Vector.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					980715	nmv			create
 *----------------------------------------------------------------------------*/
#pragma warning(disable:4786)

#ifndef inexum_stl_Vector_h
#define inexum_stl_Vector_h

#include <vector>
#include <inexum/definitions.h>

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
		/** The array of pointers to the objects with garbage collection. At the 
		  * time of the destruction all contained objects will be removed.
		  *
		  * @param T - the type of pointer elements
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template< class T >
		class VectorPtr : public std::vector<T*>
		{
		public:
			/// The iterator type
			typedef std::vector<T*>::iterator iterator;

			/// The constant iterator type
			typedef std::vector<T*>::const_iterator const_iterator;

			VectorPtr()
			{
			};

			/// The VectorPtr destructor removes all the elements
			~VectorPtr()
			{
				const_iterator theEnd = this->cend();
				for(iterator at = this->begin(); at < theEnd; at++ )
				{
					delete *at;
				}
			}
		};
	}	//namespace stl
}	// namespace inexum

#endif	// inexum_stl_Vector_h
