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
 * File:		Array.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef iNexum_OSP_Array_h
#define iNexum_OSP_Array_h

#include "Class.h"
#include <inexum/Types.h>

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
		/** Java object parser symbol encapsulates the class description of an array.
		  * Responsible for deserialization of an array.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class Array : public Class
		{
		public:
			/// Array symbol default constructor
			Array() :m_elementType(0) {};
			
			/// Array symbol copy constructor
			Array(const Array& right) 
				:Class(right), m_elementType(right.m_elementType) {}

			/// Array symbol destructor
			~Array() {}

			/** Provide more descriptive array name
			  * and to capture the elements' type. The name should corresponde to
			  * java serialization format, e.g. '[B' or '[Ljava.lang.Long;'.
			  *
			  *	@param name - a string name in Java serialization format
			  */
			void setName(const std::string& name);

			/** Add specified number of elements of arrays type. It can be called
			  *	only after setName, because it requires elements' type.
			  *
			  * @param count - the number of elemnets to be added
			  */
			void addElements(int count);

			/** Array symbol clone method:
			  * 
			  * @return a cloned array symbol instance as a Class symbol
			  */
			virtual Class* clone() const { return(new Array(*this)); }

			/** Array does not provide conversion of class description flags to
			  * parser tokens.
			  *
			  * @return JavaObjectParser::InsertNoToken()
			  */
			int classDescriptionFlag2Token() const;

			/** Create an instance of std::vector for appropriate element type
			  * and initialize elements with values from this array symbol.
			  *
			  * @return the address of a created object as a void pointer. Return NULL if error.
			  */
			void* instantiate() const;

			/** Initialize elements of an std:vector instantiated for appropriate 
			  * element type with array's deserialized values.
			  *
			  * @param address - the void pointer address of the object to be 
			  *					initialized.
			  */
			void initialize(void* address) const;

		protected:
		private:
			/// The element type expected to have one of the Java specified values. 
			char		m_elementType;
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// iNexum_OSP_Array_h

