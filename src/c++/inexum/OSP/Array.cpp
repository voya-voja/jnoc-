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
 * File:		Array.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020615	nmv			create
 *----------------------------------------------------------------------------*/

#include "inexum/definitions.h"
#include <inexum/stl/Factory.h>
#include "Object.h"
#include "Serializable.h"
#include <vector>
#include <cstdio>

#include "Array.h"
#include <inexum/util/Debug.h>

using namespace inexum::OSP;
using namespace inexum::stl;
using namespace inexum::util;

typedef Factory<char, Object> ObjectFactory;

// The array name can be "[I" for builtin types or "[Ljava.lang.Number;"
void Array::setName(const std::string& name)
{
	debug_method(DebugMethod(Debug::c_serialize, "Array", "setName", "name: %s", name.c_str()));
	if(name[1] == 'L' && name == "[Ljava.lang.String;")
		m_elementType = '"';
	else
		m_elementType = name[1];

	size_t pos = 0;
	size_t size = name.size();
	if(name[ size - 1 ] == ';')
		size--;
	if(name[0] == '[' || name[0] == 'L')
	{
		pos++;
		size--;
		if(name[1] == 'L')
		{
			pos++;
			size--;
		}
	}
	std::string elementType(name, pos, size);

	// register the internal array class name
	Class::setName(Serializable::ArrayCode() + elementType);
}

// Initialize the array with the specified number of elements
void Array::addElements(int count) 
{
	debug_method(DebugMethod(Debug::c_serialize, "Array", "addElements", "count: %d", count));
	// array is a class where the elements are members
	membersCount(count);
	int index = 0;
	while(!isComplete())
	{
		//create an element and add it to the list of members
		Object* pObject = ObjectFactory::Instance().create(m_elementType);
		char number[5];
		sprintf_s(number, "%d", index++);
		pObject->setName(std::string("element[") + number + "]");
		add(*pObject);
	}
}

// Parser's control function
int Array::classDescriptionFlag2Token() const
{
	int ret = JavaObjectParser::InsertNoToken();
	debug_method(DebugMethod(Debug::c_serialize, "Array", 
								"classDescriptionFlag2Token", "%x", &ret));
	return(ret);
}

void* Array::instantiate() const
{
	void* pObject = NULL;
	debug_method(DebugMethod(Debug::c_serialize, "Array", "instantiate", "%p", &pObject));
	try
	{
		/* use a serializable object wrapper that knows how to instantiate and 
		 * initialize the real object
		 */
		Serializable* pSerializableObject = 
							SerializableFactory::Instance().create(name());
		pSerializableObject->initialize(*this);
		pObject = pSerializableObject->object();
		delete pSerializableObject;
		return(pObject);
	}
	catch(...)
	{
		debug_line(DebugLine(Debug::c_serialize, "error S0003: Array '%s' is not serializable!", 
															name().data()));
		std::cerr << "error S0003: Array '" << name().data() << 
								"' is not serializable!" << std::endl;
	}
	return(pObject);
}

void Array::initialize(void* address) const
{
	debug_method(DebugMethod(Debug::c_serialize, "Array", "initialize", "address: %p", address));
	try
	{
		/* use a serializable object wrapper that knows how to
		 * initialize the real object at the specific address
		 */
		Serializable* pSerializableObject = 
							SerializableFactory::Instance().create(name());
		pSerializableObject->initialize(address, *this);
		delete pSerializableObject;
	}
	catch(...)
	{
		debug_line(DebugLine(Debug::c_serialize, "error S0007: Array '%s' is not serializable!", 
															name().data()));
		std::cerr << "error S0007: Array '" << name().data() << "' is not serializable!" << std::endl;
	}
}
