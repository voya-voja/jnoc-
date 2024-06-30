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
 * File:		ArrayObject.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef iNexum_ArrayObject_h
#define iNexum_ArrayObject_h

#include "Array.h"
#include "ClassObject.h"
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
		class Object;
		class Class;

		/** Java object parser symbol encapsulates the object description of
		  * an array.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class ArrayObject : public ClassObject
		{
		public:
			/// Default constructor
			ArrayObject() :ClassObject() {}

			/** Construct the array object wrapper with the specified name.
			  * 
			  * @param name - the object name
			  */
			ArrayObject(const std::string& name) 
				:ClassObject(name) {}

			/** Construct the array object wrapper with the reference to the.
			  * array description.
			  * 
			  * @param aClass - the reference to the objects class description
			  */
			ArrayObject(const Class& aClass) : ClassObject(aClass) {}

			/** Clones array object.
			  * 
			  * @return the created  object.
			  */
			Object* clone() const { return(new ArrayObject(*this)); }

			/** Add specified number of elements.
			  * 
			  * @param count - the number of elements.
			  */
			void addElements(int count)
			{
				Array& array = dynamic_cast<Array&>(type());
				array.addElements(count);
			}

			/** Return the end of array token.
			  * 
			  * @return the array token end token.
			  */
			int getEndToken() const { return(ARRAY_END); }

		protected:
		private:

			#ifdef iNxmDebug
				friend util::DebugClass<ArrayObject>;
			#endif	// iNxmDebug
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// iNexum_ArrayObject_h

