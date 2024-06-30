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
 * File:		SerializeString.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef inexum_OSP_SerializeString_h
#define inexum_OSP_SerializeString_h

#include <inexum/definitions.h>
#include "Serializable.h"

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
		/** Serializable class for string objects (std::string).
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class SerializeString : public Serializable
		{
		public:
			/** Overloaded constructor.
			  * 
			  * @param className - the Java class name to be serialized.
			  */
			SerializeString( const std::string& className ) 
				: Serializable( className ) 
			{}


		protected:
			/** Instantiate a built-in object of serializable class.
			  * 
			  * @return the void pointer address of a serializable object.
			  */
			void* instantiateObject() { return( new std::string ); }

			/** Empty method. N/A for this specialization of Serializable.
			  * 
			  * @param pObject - the address of an object to be initialized.
			  * @param aClass - the class description corresponding to the object.
			  */	
			void initializeObject( void* pObject, const Class& aClass )
			{
			}

			/** Serialize the C++ std::string object using the provided Java 
			  *	object serializer.
			  *
			  * @param address - the object address 
			  *	@param serializer - Java object serializer.
			  */
			void serialize( const void* address, JavaObjectSerializer& serializer );

		private:
			static Serializable::CppJavaNamesRegister g_namesRegister;
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// inexum_OSP_SerializeString_h

