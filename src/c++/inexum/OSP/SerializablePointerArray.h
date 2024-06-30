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
 * File:		SerializablePointerArray.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef iNexum_SerializablePointerArray_h
#define iNexum_SerializablePointerArray_h

#include "Serializable.h"
#include <inexum/Types.h>

#include <string.h>
#include "Class.h"
#include "Object.h"
#include "JavaObjectSerializer.h"


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
		  * a C++ serializable array of pointers. The class uses inexum::VectorPtr 
		  * provide the support of a Java array and garbage collection of contained
		  * objects.
		  *
		  * @see	inexum::Serialize
		  * @see	inexum::SerializablePointerArray
		  * @see	serialize_array
		  *
		  * @param TYPE - A type of array's elements.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template< class TYPE >
		class SerializablePointerArray : public Serializable
		{
		public:
			/** Overloaded constructor creates a serializable wrapper for an array
			  * of pointers. The class name is expected to be in format 
			  *	'['<base element type>.
			  * 
			  * @param className - the Java object serialization array name.
			  */
			SerializablePointerArray(const std::string& className) 
				: Serializable(className), m_elementType(className.substr(1))
			{}

		protected:

			/** Instantiate an object of serializable array.
			  * 
			  * @return the void pointer address of a serializable object.
			  */
			void* instantiateObject() { return(new stl::VectorPtr<TYPE>); }


			/** Override to initialize a serializable array object.
			  * 
			  * @param pObject - the address of an array object to be initialized.
			  * @param aClass - the array description corresponding to the object.
			  */	
			void initializeObject(void* pObject, const Class& aClass);

			/** Serialize the C++ serializable array object using the provided Java
			  * object serializer.
			  *
			  * @param address - the object address 
			  *	@param serializer - Java object serializer.
			  */
			void serialize(const void* address, JavaObjectSerializer& serializer);

			/** Override to provide the type of an element at the specified address.
			  *
			  * @param address - the object address 
			  *	@return the element type.
			  */
			virtual std::string elementType(void* address) const = 0;

			static Serializable::CppJavaNamesRegister gm_namesRegister;

		private:
			/// The base element type
			std::string	m_elementType;
		};


		template< class TYPE >
		void SerializablePointerArray<TYPE>::initializeObject(void* pObject, 
															const Class& aClass)
		{
			stl::VectorPtr<TYPE>& array = *(stl::VectorPtr<TYPE>*)object();
			Class::const_MemberIterator end = aClass.memberEnd();
			for(Class::const_MemberIterator at = aClass.memberBegin(); at != end; at++)
			{
				std::string name = (*at)->name();
				try
				{
					void* pElement = (*at)->instantiate();
					array.push_back((TYPE*)pElement);
				}
				catch(...)
				{
					debug_line(util::DebugLine(util::Debug::c_serialize, 
							"error S0006: Element '%s' is not serializable!", 
																	aClass.name().data()));
					cerr << "error S0006: Element '" << aClass.name().data() << "." 
											<< name.data() << "' is not serializable!" << endl;
				}
			}
		}

		template< class TYPE >
		void SerializablePointerArray<TYPE>::serialize(const void* address, 
													JavaObjectSerializer& serializer) 
		{
			const byte c_tcArray = JavaObjectSerializer::tcArray();
			serializer.writeReverse(&c_tcArray, sizeof(c_tcArray));

			if(serializer.referenced(address)) 
				return;

			std::string name("[L");
			name += std::string(className().data() + 1) + ";";

			if(!serializer.referenced(name))
			{
				serializer.writeClassDescription(name, 0, serialVersionUID());

				serializer.writeClassDescriptionEnd(address, "");
			}

			stl::VectorPtr<TYPE>& array = *(stl::VectorPtr<TYPE>*)address;
			unsigned int size = (unsigned short)array.size();
			serializer.writeReverse((const byte*)&size, sizeof(size));

			if(size > 0)
			{
				stl::VectorPtr<TYPE>::const_iterator end = array.end();

				unsigned count = 0;
				for(stl::VectorPtr<TYPE>::iterator at = array.begin(); at != end; at++)
				{
					if((*at) == NULL) 
						serializer.writeNull();
					else try
					{
						Serializable* pObj = 
							SerializableFactory::Instance().create(elementType((void*)(*at)));
						pObj->serialize((const void*)(*at), serializer);
						delete pObj;
					}
					catch(...)
					{
						debug_line(util::DebugLine(util::Debug::c_serialize, 
							"error S0011: Element[%d] of type '%s' cannot be serialized!", 
														count, m_elementType.data()));
						cerr << "error S0011: Element[" << count << "] of type '"
								<< m_elementType.data() << "' cannot be serialized!" <<endl;
					}
					count++;
				}
			}
			serializer.remove(address);
		}
	}	// namsespace OSP
}	// namespace inexum

#endif	// iNexum_SerializablePointerArray_h

