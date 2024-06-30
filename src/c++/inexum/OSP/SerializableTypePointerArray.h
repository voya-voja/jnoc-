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
 * File:		SerializableTypePointerArray.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef inexum_OSP_SerializableTypePointerArray_h
#define inexum_OSP_SerializableTypePointerArray_h

#include <inexum/Types.h>
#include "SerializablePointerArray.h"

#include <typeinfo>

/** iNexum classes.
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
namespace inexum
{
	/** Object Serializable Protocol namespace.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
	namespace OSP
	{
		/** Specialization of Serializable class that provides means to define
		  * a C++ serializable array of pointers. The class uses inexum::VectorPtr 
		  * provide the support of a Java array and garbage collection of contained
		  * objects.
		  *
		  * @see	inexum::SerializablePointerArray<void>
		  * @see	inexum::SerializableVoidPointerArray
		  * @see	serialize_array
		  *
		  * @param TYPE - A type of array's elements.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template<class TYPE>
		class SerializableTypePointerArray : public SerializablePointerArray<TYPE>
		{
		public:
			/** Overloaded constructor creates a serializable wrapper for an array
			  * of pointers. The class name is expected to be in format 
			  *	'['<base element type>.
			  * 
			  * @param className - the Java object serialization array name.
			  */
			SerializableTypePointerArray( const std::string& className ) 
				: SerializablePointerArray<TYPE>( className )
			{}


			/** Specialize for diferent instantiation of SerializableTypePointerArray.
			  * 
			  * @return a serializable version unique identifier.
			  */
			JLong serialVersionUID() const;

		protected:

			/** Type of an element at the specified address.
			  *
			  * @param address - the object address 
			  *	@return the element type.
			  */
			virtual std::string elementType( void* address ) const
			{
				return( Serializable::CppJavaNamesRegister::javaName( 
										typeid( *(TYPE*)address ).name() 
														+ Serializable::ClassSize() ) );
			}

		private:
			static Serializable::CppJavaNamesRegister gm_namesRegister;
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// inexum_OSP_SerializableTypePointerArray_h

