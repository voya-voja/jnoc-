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
 * File:		BuiltinObject.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef iNexum_BuiltinObject_h
#define iNexum_BuiltinObject_h

#include "Object.h"
#include "JavaObjectParser.h"
#include "PrimitiveValue.h"

#include <inexum/Types.h>
#include <memory>

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
		/** Symbol of java object parser - encapsulates the description of Java 
		  * builtin type.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class PrimitiveObject : public Object 
		{
		public:
			/** Provide the list of all one character Java type descriptions
			  *
			  * @return a constant string with all permisable charater types
			  */
			static const std::string& Types() { return(c_primitiveTypes); }

			/** Override to provide the support for specific value.
			  * 
			  * @param pValue - pointer to the value encapsulation object
			  */
			virtual void setValue(Value* pValue) = 0;

		protected:
		private:
			/// The list of Java type permisable characters.
			const static std::string 	c_primitiveTypes;
		};

		/** PrimitiveObject Specialization implements Java object parser symbol 
		  * description for each Java bultin types.
		  *
		  * @param TYPE - the builtin type
		  * @param state - the corresponding parser state
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template<class TYPE, JavaObjectParser::State state>
		class BuiltinObject : public PrimitiveObject 
		{
		public:
			/// Default constructor
			BuiltinObject() {}

			/// Copy constructor
			BuiltinObject(const BuiltinObject<TYPE, state>& right) 
				: PrimitiveObject(right), m_value(right.m_value) {}

			/** Overloaded constructor
			  *
			  * @param value - the reference to the value assigned to the object
			  */
			BuiltinObject(const TYPE& value) : m_value(value) {}

			/** Clone the object's description.
			  *
			  * @return a cloned object
			  */
			Object* clone() const 
			{ 
				return(new BuiltinObject<TYPE, state>(*this)); 
			}

			/** The object's value getter.
			  *
			  * @return the constant reference to the contained value
			  */
			const TYPE& value() const { return(m_value); }

			/** The object's value setter.
			  *
			  * @param value - a constant reference to the setting value
			  */
			void setValue(const TYPE& value) { m_value = value; }


			/** The object's value setter. Retreve the the value from Value wrapper.
			  *
			  * @param pValue - pointer to a value wrapper
			  */
			void setValue(Value* pValue) 
			{
				PrimitiveValue<TYPE>* pBTV = 
						dynamic_cast<PrimitiveValue<TYPE>*>(pValue);
				setValue(pBTV->get()); 
				delete pValue;
			}
			
			/** The getter of object's corresponding parser state.
			  *
			  * @return instantiated state
			  */
			JavaObjectParser::State getState() const { return(state); }

		protected:
			/** Create and initialize the C++ object of the type described by this 
			  * object. Copy the value to the created object and return its address.
			  *
			  * @return the address of created and initialized C++ object.
			  */
			void* instantiateObject() const
			{
				void* pObject = (void*)new TYPE(m_value);
				return(pObject);
			}

			/** Initialize the C++ object that is described by this object with the 
			  * contained value. Copy the value at the specified address assuming that 
			  * C++ object is of the type that this object describes.
			  *
			  * @param address - the address of C++ object to be initialized.
			  */
			void initializeObject(void* address) const
			{
				memcpy(address, (const void*)&m_value, sizeof(TYPE));
			}

		private:
			/// The value of the object.
			TYPE	m_value;

			#ifdef iNxmDebug
				friend util::DebugClass<BuiltinObject<TYPE, state> >;
			#endif	// iNxmDebug
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// iNexum_BuiltinObject_h

