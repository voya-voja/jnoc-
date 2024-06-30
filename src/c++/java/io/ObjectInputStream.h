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
 * File:		ObjectInputStream.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					021003	nmv			create
 *----------------------------------------------------------------------------*/
#pragma warning(disable:4786)

#ifndef java_io_ObjectInputStream_h
#define java_io_ObjectInputStream_h

#include <iostream.h>
#include <inexum/Types.h>
#include <typeinfo>

#include <inexum/definitions.h>

class DeclarationSpecifier istream;

namespace inexum { namespace OSP { class JavaObjectParser; } }

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
		/** An encapsulation of an object input stream.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier ObjectInputStream : public istream
		{
		public:
			/** Overloaded constructor:
			  *
			  * @param input - the object input stream
			  */
			ObjectInputStream(istream& input);

			/// Destructor
			~ObjectInputStream();

			/** Read an object from Java object stream.
			  *
			  * @return the address to the read object.
			  */
			void* readObject();

			/** Input operator initializes an object from Java object stream.
			  *
			  * @param object - the address of an object to be initialized.
			  * @return this object
			  */
			ObjectInputStream& operator>>(void* object);

			/** Input operator initializes an object from Java object stream.
			  *
			  * @param object - the address of an object to be initialized.
			  */
			void objectSize(size_t size) { mObjectSize = size; };

			/** Create byte buffer and load it with available data.
			  *
			  * @param size - the number of available bytes
			  * @param offset - the start of data offset.
			  * @param len - a maximum number of a bytes to be read.
			  * @return a pointer to a byte buffer.
			  */
			byte* read(size_t& size, int offset = 0, size_t len = -1);

			/** Load the buffer with available data.
			  *
			  * @param buffer - a byte buffer.
			  * @param maxSize - a size of a byte buffer.
			  * @return the number of available bytes
			  */
			size_t read(byte* buffer, size_t maxSize);

			/** Reset java object stream.
			  */
			void reset();

		protected:

		private:
			/// the Java object parser
			inexum::OSP::JavaObjectParser*	m_pObjectParser;
			size_t							mObjectSize;

		};

		/** Object input stream operator initialize an object.
		  *
		  * @param input - the input stream.
		  * @param object - the reference of an object to be initialized.
		  */
		template<class TYPE>
		ObjectInputStream& operator>>(ObjectInputStream& input, TYPE& object)
		{
			input.objectSize(sizeof(TYPE));
			return(input >> (void*)&object);
		}

		/** Read an object from Java object stream.
		  *
		  * @param input - the input stream.
		  * @return a read object.
		  */
		template<class TYPE>
		TYPE read(ObjectInputStream& input)
		{
			TYPE object;
			input >> object;
			return(object);
		}

		/** Read an object from Java object stream.
		  *
		  * @param input - the input stream.
		  * @return the pointer to the read object.
		  */
		template<class TYPE>
		TYPE* readPtr(ObjectInputStream& input)
		{
			input.objectSize(sizeof(TYPE));
			return((TYPE*)input.readObject());
		}
	}	// namespace io
}	// namespace java

#endif	// java_io_ObjectInputStream_h