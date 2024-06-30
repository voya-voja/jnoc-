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
 * File:		Object.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef inexum_OSP_Object_h
#define inexum_OSP_Object_h

#include "JavaObjectParser.h"
#include "Entity.h"

#include <inexum/Types.h>
#include <inexum/util/Debug.h>

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
		/** An encapsulation of a class as an element for the table of symbols  
		  *	of a Java object parser.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class /*DeclarationSpecifier*/ Object : public Entity
		{
		public:
			/// Object symbol default constructor
			Object() : m_pReferencedObject(NULL), m_address(NULL) {}

			/// Object symbol copy constructor
			Object(const Object& right) 
				: Entity(right), m_pReferencedObject(right.m_pReferencedObject), 
					m_address(right.m_address) 
			{}

			/** Overloaded Object symbol constructor:
			  *
			  * @param name - the object name string
			  */
			Object(const std::string& name) 
				: Entity(name), m_pReferencedObject(NULL), m_address(NULL) 
			{}

			/// Object symbol destructor
			virtual ~Object() 
			{
			};

			/** Object symbol clone method:
			  * 
			  * @return a cloned instance of the Object symbol
			  */
			virtual Object* clone() const = 0;

			/** Return the parser's read state for the next token.
			  * 
			  * @return default that is JavaObjectParser::k_ReturnByte
			  */
			virtual JavaObjectParser::State getState() const 
			{ return(JavaObjectParser::k_ReturnByte); };

			/** Return the parser's token for the end of the object if applicable.
			  * 
			  * @return default that is no end token
			  */
			virtual int getEndToken() const { return(-1); }

			/** If this is a reference to an object, retrieves the address from
			  * the referenced object. Otherwise, calls instantiateObject() method
			  * and returns the address of created object.
			  * 
			  * @return the void pointer address of the object
			  * @see instantiateObject;
			  * @see reference;
			  */
			virtual void* instantiate()
			{
				if(m_pReferencedObject != NULL) 
					return(m_pReferencedObject->address());
				else
				{
					m_address = instantiateObject();
					return(m_address);
				}
			}

			/** Link the object's address to the thsi object description and calls
			  * initializeObject() method.
			  * 
			  * @param address - the void pointer address of the object
			  * @see initializeObject;
			  */
			virtual void initialize(void* address)
			{
				m_address = address;
				initializeObject(address);
			}

			/** This object description references the provided object 
			  * description.
			  * 
			  * @param object - the reference of an object description
			  */
			void reference(Object& object) { m_pReferencedObject = &object; }

		protected:
			/** Override to create and initialize the appropriate C++ object.
			  * 
			  * @return the void pointer address of the object
			  */
			virtual void* instantiateObject() const = 0;

			/** Override to initialize the provided C++ object that is of appropriate 
			  * type.
			  * 
			  * @param address - the void pointer address of the object
			  */
			virtual void initializeObject(void* address) const = 0;

		private:
			void*	address() const { return(m_address); }

			Object*		m_pReferencedObject;
			void*		m_address;

			#ifdef iNxmDebug
				friend util::DebugClass<Object>;
			#endif	// iNxmDebug
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// iNexum_Object_h

