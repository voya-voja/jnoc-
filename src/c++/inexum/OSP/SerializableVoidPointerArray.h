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
 * File:		SerializableVoidPointerArray.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef inexum_OSP_SerializableVoidPointerArray_h
#define inexum_OSP_SerializableVoidPointerArray_h

#include <inexum/definitions.h>
#include "SerializablePointerArray.h"

#include <map>

ExternTemplate template class DeclarationSpecifier std::vector<void*>;

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
		ExternTemplate template class DeclarationSpecifier SerializablePointerArray<void>;

		/** Specialization of SerializablePointerArray class that provides means to
		  * implement serializable array of objects pointers in C++.
		  *
		  * The class provides means of serialization for any object of 
		  *	std::vector<void*>, C++ complement of Java's array of java.lang.Object.
		  * To populate Void Pointer with 
		  *
		  * @see	inexum::SerializablePointerArray<void>
		  * @see	serialize_array
		  * @see	PushBack
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class SerializableVoidPointerArray : public SerializablePointerArray<void>
		{
			/// Map of member names to the class member symbols
			typedef std::map<unsigned, std::string>	ObjectTypeMap;
			/// Pair of a member name and the class member symbol
			typedef ObjectTypeMap::value_type		ObjectTypePair;

		public:
			/** The functional object that registers types of elements.
			  *
			  * @author		iNexum Systems Inc.
			  * @version	1.0.0
			  */
			class DeclarationSpecifier AddObjectType
			{
			public:
			protected:
				/** Add the elements type
				  *
				  *	@param address - the element's address
				  *	@param type - element's Java object serialization type 
				  */
				void insert(unsigned address, const std::string& type);

			private:
			};

			/** Default constructor creates a serializable wrapper for an array
			  * of void pointers that coresponds to an array of java.lang.Object.
			  *
			  *	@param type - it should be array of java.lang.Object 
			  *				("[java.lang.Object")
			  */
			SerializableVoidPointerArray(const std::string& type);

			/** The serial version unique identifier oof Java Object references 
			  *	array.
			  *
			  *	@return serial version unique identifer
			  */
			JLong serialVersionUID() const { return(0x90ce589f1073296c); }

		protected:
			/** Type of an element at the specified address.
			  *
			  * @param address - the object address 
			  *	@return the element type.
			  */
			virtual std::string elementType(void* address) const;

		private:
			friend class AddObjectType;

			/// The objects' type map
			static ObjectTypeMap g_ObjectTypeMap;
		};


		/** A functional object to be used when adding objects to std::vector<void*>
		  *	records objects' type information.
		  *
		  *	...
		  *
		  *	.	std::vector<void*> objects;
		  *
		  * ...
		  *
		  *	.	PushBack<B> pushBackB(objects);
		  *
		  *	.	pushBackB(new B(555, 666, 777));
		  *
		  *	.	PushBack<java::lang::Integer>(objects)(new java::lang::Short(31));
		  *
		  *	...
		  *
		  * @see	inexum::SerializableVoidPointerArray
		  * @see	serialize_array
		  *
		  * @param TYPE - A type of the array element.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template<class TYPE>
		class PushBack : public SerializableVoidPointerArray::AddObjectType
		{
		public:
			/**	Overloaded constructor.
			  *
			  *	@param	objectArray - the reference to a C++ object array (
			  *							std::vector<void*>)
			  */
			PushBack(std::vector<void*>& objectArray) : m_objectArray(objectArray) {}

			/**	Overloaded operator().
			  *
			  *	@param	pElement - the address of C++ object to be added to the array
			  */
			void operator()(TYPE* pElement)
			{
				insert((unsigned)pElement, 
							typeid(*pElement).name() + Serializable::ClassSize());
				m_objectArray.push_back((void*)pElement);
			}

		protected:
		private:
			///	The reference to an object array
			std::vector<void*>&	m_objectArray;
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// inexum_OSP_SerializableVoidPointerArray_h

