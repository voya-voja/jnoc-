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
 * File:		SerializableCreator.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef inexum_OSP_SerializableCreator_h
#define inexum_OSP_SerializableCreator_h

#include <inexum/definitions.h>
#include "Serializable.h"
#include "Serialize.h"
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
		/** A functional object that creates Serializable objects.
		  *
		  * @see Serializable
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier SerializableCreator
		{
		public:
			/** Override to create a object of a Seriazable subclass.
			  *
			  * @return the pointer to created Serializable object.
			  */
			virtual Serializable* create() = 0;

			/// Virtual destructor.
			virtual ~SerializableCreator() {};

		protected:
			/** Overloaded constructor. Create an instance of 
			  * SerializableCreator for the specified java class name.
			  *
			  * @param javaClassName - the java class name string.
			  */
			SerializableCreator(const std::string& javaClassName);

			/** Java class name getter.
			  *
			  * @return the java class name string.
			  */
			const std::string& javaClassName() const { return(m_javaClassName); }

		private:
			/// Java class name
			std::string	m_javaClassName;

			/// Pointer to an object of Serializable specialization
			Serializable*	m_pSerializable;
		};

		/** A template of a functional object that creates Serialize objects.
		  *
		  * @param CLASS - the parameter of Serialize template class 
		  *
		  * @see Serialize
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template<class CLASS>
		class SerializeCreator : public SerializableCreator
		{
			/** Overloaded constructor. Create an instance of 
			  * SerializeCreator for the specified java class name.
			  *
			  * @param javaClassName - the java class name string.
			  */
			SerializeCreator(const std::string& javaClassName) 
				:SerializableCreator(javaClassName)
			{
			}

			/** Overriden to create a object of a instantiated Seriaze class.
			  *
			  * @return the pointer to created Serializable object.
			  */
			Serializable*	create()
			{
				return(new Serialize<CLASS>(javaClassName()));
			}

		private:
			/// Each given type has 1 instance of Serialize creator
			static SerializeCreator	g_Creator;
		};
	}	// namespace OSP
}	//	namespace inexum

#endif	// inexum_OSP_SerializableCreator_h