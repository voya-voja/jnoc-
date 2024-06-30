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
 * File:		ObjectOutputStream.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					021003	nmv			create
 *----------------------------------------------------------------------------*/
#pragma warning(disable:4786)

#ifndef java_io_ObjectOutputStream_h
#define java_io_ObjectOutputStream_h

#include <iostream.h>
#include <inexum/Types.h>
#include <typeinfo.h>
#include <string>
#include <inexum/OSP/Serializable.h>

#include <inexum/definitions.h>

class DeclarationSpecifier ostream;

namespace inexum { namespace OSP { class JavaObjectSerializer; } }

/** iNexum's java classes implemented in C++.
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
namespace java
{
	/** iNexum's java.io classes implemented in C++.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
	namespace io
	{
		/** An encapsulation of an object output stream.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier ObjectOutputStream : public ostream
		{
		public:
			/** Overloaded constructor:
			  *
			  * @param input - the object output stream
			  */
			ObjectOutputStream(ostream& Output);

			/// Destructor
			~ObjectOutputStream();

			/** Write an object to Java object stream.
			  *
			  * param object - the address of the object.
			  * param className - the string name of the object's class.
			  */
			void writeObject(const void* object, const std::string& className);

			/** Write a builtin object to Java object stream.
			  *
			  * param object - the address of the object.
			  * param typeName - the string name of the object's class.
			  */
			void writeBuiltinObject(const void* object, const std::string& typeName);

			/** Write bytes from a byte buffer until 0 byte to the Java object stream.
			  *
			  * param buffer - the byte buffer.
			  */
			void write(const byte* buffer);

			/** Write first len bytes from a byte buffer to the Java object stream.
			  *
			  * param buffer - the byte buffer.
			  * param len - the length og bytes to be writen.
			  */
			void write(const byte* buffer, size_t len);

			/** Write first len bytes from a byte buffer starting with the offset byte 
			  * to the Java object stream.
			  *
			  * param buffer - the byte buffer.
			  * param offset - the offset of bytes to start from.
			  * param len - the length og bytes to be writen.
			  */
			void write(const byte* buffer, size_t offset, size_t len);

			/** Write bytes from a wchar_t buffer until '0' wchar_t to the Java object stream.
			  *
			  * param buffer - the wchar_t buffer.
			  */
			void writeChars(const wchar_t* buffer);

			/// Reset java object stream.
			void reset();

		protected:

		private:
			/// the Java object serializer
			inexum::OSP::JavaObjectSerializer*	m_pObjectSerializer;
		};

		/** Write an object to Java object stream.
		  *
		  * @param output - the output stream.
		  * @param object - the reference to the object.
		  */
		template<class TYPE>
		void write(ObjectOutputStream& output, const TYPE& object)
		{
			const char* typeName = typeid(object).name();
			const size_t c_classWordSize = inexum::OSP::Serializable::ClassSize();
			if(typeName[c_classWordSize - 1] == ' ')
				output.writeObject((const void*)&object, typeName + c_classWordSize);
			else
				output.writeBuiltinObject((const void*)&object, typeName);
		}

		/** Write an object to Java object stream.
		  *
		  * @param output - the output stream.
		  * @param pObject - the pointer to the object.
		  */
		template<class TYPE>
		void writePtr(ObjectOutputStream& output, const TYPE* pObject)
		{
			write<TYPE>(output, *pObject);
		}

		/** Object output stream operator serializes an object.
		  *
		  * @param output - the output stream.
		  * @param object - the reference of an object to be serialized.
		  */
		template<class TYPE>
		ObjectOutputStream& operator<<(ObjectOutputStream& output, const TYPE& object)
		{
			write<TYPE>(output, object);
			return(output);
		}
	}	// namespace io
}	// namespace java

#endif	// java_io_ObjectOutputStream_h