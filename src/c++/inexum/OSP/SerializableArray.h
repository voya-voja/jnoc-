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
 * File:		SerializableArray.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef iNexum_SeralizableArray_h
#define iNexum_SeralizableArray_h

#include "Serializable.h"
#include "Class.h"
#include "JavaObjectSerializer.h"

#include <vector>
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
		/** Specialization of Serializable class that provides means to define
		  * a C++ serializable array. The class uses std::vector class to 
		  * provide the support of a Java array.
		  *
		  * @see	inexum::SerializablePointerArray
		  * @see	serialize_array
		  *
		  * @param TYPE - A type of array's elements.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template< class TYPE >
		class SerializableArray : public Serializable
		{
		public:
			/** Overloaded constructor creates a serializable wrapper for an array.
			  * The class name is expected to be in format '['<element type>.
			  * 
			  * @param className - the Java object stream array name.
			  */
			SerializableArray(const std::string& className) 
				: Serializable(className), m_elementType(className.substr(1))
			{}

			/** Specialize for diferent instantiation of SerializableArray.
			  * 
			  * @return a serializable version unique identifier.
			  */
			JLong serialVersionUID() const;

		protected:

			/** Instantiate an object of serializable array.
			  * 
			  * @return the void pointer address of a serializable object.
			  */
			void* instantiateObject() { return(new std::vector<TYPE>); }

			/** Override to initialize a serializable array object.
			  * 
			  * @param pObject - the address of an array object to be initialized.
			  * @param aClass - the array description corresponding to the object.
			  */	
			void initializeObject(void* pObject, const Class& aClass)
			{
				std::vector<TYPE>& array = *(std::vector<TYPE>*)pObject;
				Class::const_MemberIterator end = aClass.memberEnd();
				for(Class::const_MemberIterator at = aClass.memberBegin(); at != end; at++)
				{
					std::string name = (*at)->name();
					try
					{
						array.push_back((TYPE)0);
						auto objectLast = array[array.size() - 1];
						(*at)->initialize((void*)&objectLast);
					}
					catch(...)
					{
						debug_line(DebugLine(Debug::c_serialize, 
							"error S0005: Element '%s' is not serializable!", 
																	aClass.name().data()));
						std::cerr << "error S0005: Element '" << aClass.name().data() << "."
												<< name.data() << "' is not serializable!" << std::endl;
					}
				}
			}

			/** Serialize the C++ serializable array object using the provided Java
			  * object serializer.
			  *
			  * @param address - the object address 
			  *	@param serializer - Java object serializer.
			  */
			void serialize(const void* address, JavaObjectSerializer& serializer) 
			{
				const byte c_tcArray = JavaObjectSerializer::tcArray();
				serializer.writeReverse(&c_tcArray, sizeof(c_tcArray));

				if(serializer.referenced(address)) 
					return;

				std::string name = className();
				if(name.size() > 2)
				{
					name = "[L";
					name += std::string(className().data() + 1) + ";";
				}

				if(!serializer.referenced(name))
				{
					serializer.writeClassDescription(name, 0, serialVersionUID());

					serializer.writeClassDescriptionEnd(address, "");
				}

				std::vector<TYPE>& array = *(std::vector<TYPE>*)address;
				unsigned int size = (unsigned short)array.size();
				serializer.writeReverse((const byte*)&size, sizeof(size));

				if(size > 0)
				{
					unsigned count = 0;
					auto end = array.cend();
					Serializable* pObj = SerializableFactory::Instance().create(m_elementType);
					for(auto at = array.begin(); at != end; at++)
					{
						try
						{
							auto objectAt = *at;
							pObj->serialize((const void*)&objectAt, serializer);
						}
						catch(...)
						{
							debug_line(DebugLine(Debug::c_serialize, 
								"error S0010: Element[%d] of type '%s' cannot be serialized!", 
															count, m_elementType.data()));
							std::cerr << "error S0010: Element[" << count << "] of type '"
									<< m_elementType.data() << "' cannot be serialized!" << std::endl;
						}
						count++;
					}
					delete pObj;
				}
				serializer.remove(address);
			}

		private:
			/// the array element type 
			std::string	m_elementType;

			static Serializable::CppJavaNamesRegister gm_namesRegister;
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// iNexum_SeralizableArray_h

