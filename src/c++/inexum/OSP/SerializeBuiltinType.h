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
 * File:		SerializeBuiltinType.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef inexum_OSP_SerializeBuiltinType_h
#define inexum_OSP_SerializeBuiltinType_h

#include "Serializable.h"
#include "JavaObjectSerializer.h"
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
		/** Specialization of Serializable class that provides means to serialize
		  * Java built-in types.
		  *
		  * @param TYPE - A built-in type.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template< class TYPE >
		class SerializeBuiltinType : public Serializable
		{
		public:
			/** Overloaded constructor.
			  * 
			  * @param className - the Java class name to be serialized.
			  */
			SerializeBuiltinType(const std::string& className) 
				: Serializable(className) 
			{}


		protected:
			/** Instantiate a built-in object of serializable class.
			  * 
			  * @return the void pointer address of a serializable object.
			  */
			void* instantiateObject() { return(new TYPE); }

			/** Empty method. N/A for this specialization of Serializable.
			  * 
			  * @param pObject - the address of an object to be initialized.
			  * @param aClass - the class description corresponding to the object.
			  */	
			void initializeObject(void* pObject, const Class& aClass)
			{
			}

			/** Serialize the C++ serializable object of Java built-in type using
			  *	the provided Java object serializer.
			  *
			  * @param address - the object address 
			  *	@param serializer - Java object serializer.
			  */
			void serialize(const void* address, JavaObjectSerializer& serializer) 
			{
				serializer.writeReverse((const byte*)address, sizeof(TYPE));
			}

		private:
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// inexum_OSP_SerializeBuiltinType_h

