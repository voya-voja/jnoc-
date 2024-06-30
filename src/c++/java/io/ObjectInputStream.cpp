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
 * File:		ObjectInputStream.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					021003	nmv			create
 *----------------------------------------------------------------------------*/


#include "ObjectInputStream.h"

#include <inexum/OSP/JavaObjectParser.h>
#include <inexum/OSP/JavaObjectSerializer.h>
#include <inexum/OSP/Object.h>
#include <inexum/OSP/BlockData.h>
#include <inexum/util/Debug.h>

using namespace inexum::OSP;
using namespace inexum::util;
using namespace java::io;

ObjectInputStream::ObjectInputStream(istream& input) 
	:istream(input.rdbuf()), m_pObjectParser(NULL)
{
	debug_method(DebugMethod(Debug::c_net, "ObjectInputStream", "ObjectInputStream", 
				"istream& input"));
	m_pObjectParser = new JavaObjectParser(input);
	unsigned short magic = 0;
	unsigned short version = 0;
	byte aByte = (byte)input.get();
	magic = magic << 8 | aByte;
	aByte = (byte)input.get();
	magic = magic << 8 | aByte;
	if(magic != JavaObjectSerializer::c_magic)
		throw 22;
	aByte = (byte)input.get();
	version = version << 8 | aByte;
	aByte = (byte)input.get();
	version = version << 8 | aByte;
	if(version != JavaObjectSerializer::c_version)
		throw 23;
}

ObjectInputStream::~ObjectInputStream()
{
	debug_method(DebugMethod(Debug::c_net, "ObjectInputStream", "~ObjectInputStream"));
	delete m_pObjectParser;
}

void* ObjectInputStream::readObject()
{
	void*	object;
	debug_method(DebugMethod(Debug::c_net, "ObjectInputStream", "readObject", "%d", &object));

	Object* pParsedObject = m_pObjectParser->object();
	BlockData* pBlockData = dynamic_cast<BlockData*>(pParsedObject);

	bool parse = pParsedObject == NULL || pBlockData == NULL || pBlockData->isEmpty();
	if(parse)
	{
		m_pObjectParser->run();
		pParsedObject = m_pObjectParser->object();
		pBlockData = dynamic_cast<BlockData*>(pParsedObject);
	}
	
	if(pBlockData == NULL)
	{
		object = pParsedObject->instantiate();
	}
	else
	{
		object = pBlockData->instantiate(mObjectSize);
	}
	return(object);
}

ObjectInputStream& ObjectInputStream::operator>>(void* object)
{
	debug_method(DebugMethod(Debug::c_net, "ObjectInputStream", "operator>>", 
				"object: '%d'", object));
	Object* pParsedObject = m_pObjectParser->object();
	BlockData* pBlockData = dynamic_cast<BlockData*>(pParsedObject);

	bool parse = pParsedObject == NULL || pBlockData == NULL || pBlockData->isEmpty();
	if(parse)
	{
		m_pObjectParser->run();
		pParsedObject = m_pObjectParser->object();
		pBlockData = dynamic_cast<BlockData*>(pParsedObject);
	}
	
	if(pBlockData == NULL)
	{
		pParsedObject->initialize(object);
	}
	else
	{
		pBlockData->initialize(object, mObjectSize);
	}
	return(*this);
}

byte* ObjectInputStream::read(size_t& size, int offset, size_t len)
{
	byte* buffer = NULL;
	size = 0;
	debug_method(DebugMethod(Debug::c_net, "ObjectInputStream", "read", 
				"%d buffer: '%d', offset: %d, len: '%d'", 
				&size, (void*)buffer, offset, size));
	Object* pParsedObject = m_pObjectParser->object();
	BlockData* pBlockData = dynamic_cast<BlockData*>(pParsedObject);

	bool parse = pParsedObject == NULL || pBlockData == NULL || pBlockData->isEmpty();
	if(parse)
	{
		m_pObjectParser->run();
		pParsedObject = m_pObjectParser->object();
		pBlockData = dynamic_cast<BlockData*>(pParsedObject);
	}
	
	if(pBlockData != NULL)
	{
		buffer = pBlockData->read(size, offset, len);
	}
	return(buffer);
}

size_t ObjectInputStream::read(byte* buffer, size_t maxSize)
{
	int size = 0;
	debug_method(DebugMethod(Debug::c_net, "ObjectInputStream", "read", 
				"%d buffer: '%d', maxSize: '%d'", 
				&size, (void*)buffer, maxSize));
	Object* pParsedObject = m_pObjectParser->object();
	BlockData* pBlockData = dynamic_cast<BlockData*>(pParsedObject);

	bool parse = pParsedObject == NULL || pBlockData == NULL || pBlockData->isEmpty();
	if(parse)
	{
		m_pObjectParser->run();
		pParsedObject = m_pObjectParser->object();
		pBlockData = dynamic_cast<BlockData*>(pParsedObject);
	}
	
	if(pBlockData != NULL)
	{
		size = pBlockData->read(buffer, maxSize);
	}
	return(size);
}

void ObjectInputStream::reset()
{
	m_pObjectParser->reset();
}