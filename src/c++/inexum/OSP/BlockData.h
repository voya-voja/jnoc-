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
 * File:		BlockData.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef inexum_OSP_BlockData_h
#define inexum_OSP_BlockData_h

#include "Object.h"
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
		/** Java object parser symbol encapsulates the manipulation of data block.
		  * Responsible to deserialize byte buffers and builtin type objects. 
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class BlockData : public Object 
		{
			byte*	mBlock;
			size_t	mFillSize;
			size_t	mSize;
			size_t	mInitializeFrom;
		public:
			/// Array symbol copy constructor
			BlockData(const BlockData& right);

			/** Construct the block data with the buffer of a specified size.
			  * 
			  * @param size - the block size
			  */
			BlockData(size_t size);

			/// Object symbol destructor
			~BlockData() { delete[] mBlock; };

			/** Object symbol clone method:
			  * 
			  * @return a cloned instance of the Object symbol
			  */
			Object* clone() const { return(new BlockData(*this)); };

			/** Add a byte to a data block.
			  * 
			  * @param aByte - the byte to be added
			  */
			void add(byte aByte) { mBlock[mFillSize++] = aByte; };

			/** Verify is block data buffer full.
			  *
			  * @return true if buffer is full, otherwise false.
			  */
			bool isFull() const 
			{ 
				return(mSize == mFillSize); 
			};

			/** Verify is block data buffer empty.
			  *
			  * @return true if buffer is empty, otherwise false.
			  */
			bool isEmpty() const 
			{ 
				return(mInitializeFrom >= mFillSize); 
			};

			/** Initialize the provided C++ object. The object's address 
			  * and the size of object's type are required to
			  * copy the required number of bytes at specified address.

			  * 
			  * @param address - the void pointer address of the object
			  * @param size - the object size
			  */
			void initialize(void* address, size_t size);

			/** Create and initialize a C++ object. The size of object's 
			  * type is required to copy the required number of bytes 
			  * into the created object..
			  * 
			  * @param size - the object size
			  * @return the void pointer address of the object
			  */
			void* instantiate(size_t size);

			/** Create byte buffer and load it with available data.
			  *
			  * @param size - the number of available bytes
			  * @param offset - the start of data offset.
			  * @param len - a maximum number of a bytes to be read. If -1,
			  *				read the block data buffer size from the stream.
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

			/// byte pointer operator
			operator byte*() { return(mBlock); };

			/// Set the BlockData oject in full buffer state.
			void full() { mFillSize = mSize; };

			/** BlockData size getter.
			  *
			  * @return the size of data block
			  */
			size_t size() const { return(mSize); };

			/// Reset the block data buffer.
			void reset() 
			{ 
				mFillSize = 0;
				mInitializeFrom = 0;
			};

		protected:
			/** Not applicable to a BlockData.
			  * 
			  * @return NULL
			  */
			void* instantiateObject() const;

			/** Not applicable to BlockData.
			  * 
			  * @param address - the void pointer address of the object
			  */
			void initializeObject(void* address) const ;
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// inexum_OSP_BlockData_h

