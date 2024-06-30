/*******************************************************************************
*  Copyright (C) 1997 - 2002 iNexum Systems Inc.
*  All Rights Reserved
*  This Module contains Proprietary Information of iNexum Systems Inc.,
*
*  The copyright notice above does not evidence any
*  actual or intended publication of such source code.
*******************************************************************************/
/*----------------------------------------------------------------------------*
 *                                                                            *
 * File:		ObjectReference.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef inexum_OSP_ObjectReference_h
#define inexum_OSP_ObjectReference_h

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
	/** An encapsulation of a Java object reference as an element for the table of 
	  *	symbols of a Java object parser.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
		class ObjectReference : public Object
		{
		public:
			/// Default constructor
			ObjectReference() : m_reference(NULL) {}

			/// Copy constructor
			ObjectReference(const ObjectReference& right) 
				: Object(right), m_reference(right.m_reference) {}

			/** Overloaded constructor:
			  *
			  * @param name - the name of the object
			  */
			ObjectReference(const std::string& name) 
				: Object(name), m_reference(NULL) {}

			/** Overloaded constructor:
			  *
			  * @param name - the name of the object of a string type
			  * @param entity - a reference to an entity of this object
			  */
			ObjectReference(const std::string& name, Entity& entity) 
				: Object(name), m_reference(&entity) {}

			/** Overloaded constructor:
			  *
			  * @param object - the object to be a reference
			  * @param entity - a reference to an entity of this object
			  */
			ObjectReference(const Object& object, Entity& entity) 
				: Object(object), m_reference(&entity) {}

			/** Object reference getter.
			  *
			  * @return string object value.
			  */
			Entity* reference() const { return(m_reference); }

			/** Object reference setter.
			  *
			  * @param entity - a reference to an entity.
			  */
			void reference(Entity& entity) { m_reference = &entity; }

			/** Class Object symbol clone method:
			  * 
			  * @return a cloned Class Object symbol instance as an Object symbol
			  */
			Object* clone() const { return(new ObjectReference(*this)); }

			/** Overridden to create and initialize the std::string instance.
			  * 
			  * @return the void pointer address of the instance of std::string.
			  */
			void* instantiate() const
			{
				return(m_reference->instantiate());
			}

			/** Overriden to initialize the provided instance of std::string.
			  * 
			  * @param address - the void pointer address of the std::string.
			  */
			void initialize(void* address) const
			{
				m_reference->initialize(address);
			}

			 /* A debug method that dumps the string object content
			  *
			  * @param out - an output stream
			  * @param indent - the indent level
			  */
			void print(ostream& out, const std::string& indent) const
			{
				Object::print(out, indent);
				out << m_reference << endl;
			}

		protected:
		private:
			Entity*		m_reference;
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// inexum_OSP_ObjectReference_h

