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
 * File:		Map.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					980715	nmv			create
 *----------------------------------------------------------------------------*/
#pragma warning(disable:4786)

#ifndef inexum_stl_Map_h
#define inexum_stl_Map_h

#include <map>

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
		/** The map of the pointers to teh objects with the garbage collection.
		  * At the destruction time it will remove all contained objects.
		  *
		  * @param KEY - a type of a map's keys
		  * @param T - a type of the pointer element to be stored in a map
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template< class Key, class T >
		class MapPtr : public std::map<Key, T*>
		{
		public:
			/// The iterator type
			typedef std::map<Key, T*>::iterator iterator;

			/// The constant iterator type
			typedef std::map<Key, T*>::const_iterator const_iterator;

			/// MapPtr destructor removes all its elements
			~MapPtr()
			{
				iterator theEnd = end();
				for( iterator at = begin(); at != theEnd; at++ )
				{
					delete (*at).second;
				}
			}
		};
	}	// namespace stl
}	// namespace inexum

#endif	// inexum_stl_Map_h
