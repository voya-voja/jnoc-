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
 * File:		BlockData.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#include "BlockData.h"
#include "inexum/util/Debug.h"

using namespace inexum::OSP;
using namespace inexum::util;

BlockData::BlockData(size_t size) 
	:Object("inexum::OSP::BlockData"), mBlock(new byte[size]), 
		mSize(size), mFillSize(0), mInitializeFrom(0)
{}

BlockData::BlockData(const BlockData& right) 
	:Object(right), mBlock(new byte[right.mSize]), mSize(right.mSize), 
		mFillSize(0), mInitializeFrom(right.mInitializeFrom)
{
	for(; mFillSize < right.mFillSize; mFillSize++)
		mBlock[mFillSize] = right.mBlock[mFillSize];
}

void BlockData::initialize(void* address, size_t size)  
{
	byte* object = (byte*)address;
	for(int i = 0; i < size; i++) 
		object[size - i - 1] = mBlock[mInitializeFrom + i];
	mInitializeFrom += size;
}

void* BlockData::instantiate(size_t size) 
{ 
	void* object = new byte[size];
	initialize(object, size);
	return(object); 
};

void* BlockData::instantiateObject() const 
{ 
	return(NULL); 
}

void BlockData::initializeObject(void* address) const 
{
}

byte* BlockData::read(size_t& size, int offset, size_t len)
{
	byte* buffer = NULL;
	debug_method(DebugMethod(Debug::c_serialize, "BlockData", "read", 
				"%d buffer: '%d', offset: %d, len: '%d'", 
				&size, (void*)buffer, offset, size));
	size = mFillSize - mInitializeFrom;
	if(len != -1 && len <= size) 
		size = len;

	mInitializeFrom += offset;
	if(size != 0)
	{
		buffer = new byte[size];
		read(buffer, size);
	}

	return(buffer);
}

size_t BlockData::read(byte* buffer, size_t maxSize)
{
	size_t size = mFillSize - mInitializeFrom;
	debug_method(DebugMethod(Debug::c_serialize, "BlockData", "read", 
				"%d buffer: '%d', maxSize: '%d'", &size, (void*)buffer, maxSize));
	if(size > maxSize) 
		size = maxSize;

	if(size != 0)
	{
		for(int i = 0; i < size; i++) 
			buffer[i] = mBlock[mInitializeFrom + i];
		mInitializeFrom += size;
	}

	return(size);
}
