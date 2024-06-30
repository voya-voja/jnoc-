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
 * File:		ClassObject.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef iNexum_ClassObject_h
#define iNexum_ClassObject_h

#include "Object.h"
#include "Class.h"
#include "javaObjParser.h"

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
		/** Java object parser symbol that encapsulates the description of a class
		  * instance.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class ClassObject : public Object 
		{
		public:
			/// Class object symbol default constructor
			ClassObject() :m_pClass(NULL) {}

			/// Class object symbol copy constructor
			ClassObject(const ClassObject& right);

			/** Overloaded Class Object symbol constructor:
			  *
			  * @param name - the class object name string
			  */
			ClassObject(const std::string& name) 
				:Object(name), m_pClass(NULL) {}

			/** Overloaded Class Object symbol constructor, creates the instance 
			  * of the object symbol for a given class symbol.
			  *
			  * @param aClass - the instance of a class symbol.
			  */
			ClassObject(const Class& aClass) : m_pClass(aClass.clone()) {}

			/// Class Object symbol destructor
			~ClassObject();

			/** Class Object symbol clone method:
			  * 
			  * @return a cloned Class Object symbol instance as an Object symbol
			  */
			Object* clone() const { return(new ClassObject(*this)); }

			/** Check have been all class member symbols loaded to the class symbol 
			  * instance that is referenced by this object.
			  *
			  * @return true is all the symbols have been loaded, otherwise false.
			  */
			virtual bool isComplete() const { return(m_pClass->isComplete()); }

			/** Verify does the class's internal cursor points to the last member of
			  * the class description for this object.
			  *
			  * @return true if cursor is at last member, otherwise false.
			  */
			virtual bool isLastMember() const { return(m_pClass->isLastMember()); }

			/** The class name setter. If there is class symbol referenced by the 
			  * instance of class object symbol it will be deleted.
			  *
			  * @param pClass - a pointer to a Class symbol
			  */
			void setClass(Class* pClass) 
			{ 
				if(m_pClass != NULL)
					delete m_pClass;
				m_pClass = pClass->clone(); 
			}

			/** Class Symbol's member count getter. Return the number of members of
			  * referenced class symbol.
			  *
			  * @return the number of Class symbol members
			  */
			int membersCount() const { return(m_pClass->membersCount()); }

			/** Sets the internal cursor of referenced class symbol to the specified 
			  * class member symbol.
			  *
			  *	@param index - the member's index
			  */
			void moveToMember(int index) { m_pClass->moveToMember(index); }

			/** Return the current member symbol and move to the next member of a 
			  * referenced class symbol.
			  *
			  *	@return a reference to an Object symbol instance representing the 
			  *			current member
			  */
			Object& nextMember() { return(m_pClass->nextMember()); }

			/** Overridden to return class object's end.
			  * 
			  * @return the end of object token
			  */
			int getEndToken() const { return(OBJECT_END); }

			/** The class getter.
			  * 
			  * @return the reference to the class symbol.
			  */
			Class& type() { return(*m_pClass); }

		protected:
			/** Overridden to create and initialize the appropriate C++ class instance.
			  * 
			  * @return the void pointer address of the instance of the class that is 
			  *			described by the class symbol refrenced by this class object.
			  */
			void* instantiateObject() const
			{
				if(m_pClass == NULL) return(NULL);

				return(m_pClass->instantiate()); 
			}

			/** Overriden to initialize the provided instance of the class that is 
			  * described by the class symbol refrenced by this class object symbol.
			  * 
			  * @param address - the void pointer address of the object
			  */
			void initializeObject(void* address) const 
			{
				m_pClass->initialize(address);
			}

		private:
			/// A reference to the class symbol.
			Class*									m_pClass;

			#ifdef iNxmDebug
				friend util::DebugClass<ClassObject>;
			#endif	// iNxmDebug
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// iNexum_ClassObject_h

