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
 * File:		StringObject.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef inexum_OSP_StringObject_h
#define inexum_OSP_StringObject_h

#include <inexum/Types.h>
#include "Object.h"

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
	/** An encapsulation of a Java String as an element for the table of symbols  
	  *	of a Java object parser.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
		class StringObject : public Object
		{
		public:
			/// Default constructor
			StringObject() {}

			/// Copy constructor
			StringObject( const StringObject& right ) 
				: Object( right ), m_value( right.m_value ) {}

			/** Overloaded constructor:
			  *
			  * @param name - the name of the object of a string type
			  */
			StringObject( const std::string& name ) 
				: Object( name ) {}

			/** Overloaded constructor:
			  *
			  * @param name - the name of the object of a string type
			  * @param value - a constant reference to a string value of this object
			  */
			StringObject( const std::string& name, const std::string& value ) 
				: Object( name ), m_value( value ) {}

			/** String value getter.
			  *
			  * @return string object value.
			  */
			const std::string& value() const { return( m_value ); }

			/** String value setter.
			  *
			  * @param v - a constant reference to a string value.
			  */
			void value( const std::string& v ) { m_value = v; }

			/** Class Object symbol clone method:
			  * 
			  * @return a cloned Class Object symbol instance as an Object symbol
			  */
			Object* clone() const { return( new StringObject( *this ) ); }

		protected:
			/** Overridden to create and initialize the std::string instance.
			  * 
			  * @return the void pointer address of the instance of std::string.
			  */
			void* instantiateObject() const
			{
				void* pObject = (void*)new std::string( m_value );
				return( pObject );
			}

			/** Overriden to initialize the provided instance of std::string.
			  * 
			  * @param address - the void pointer address of the std::string.
			  */
			void initializeObject( void* address ) const
			{
				std::string& obj = *(std::string*)address;
				obj = m_value;
			}

		private:
			std::string		m_value;

			#ifdef iNxmDebug
				friend util::DebugClass<StringObject>;
			#endif	// iNxmDebug
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// inexum_OSP_StringObject_h

