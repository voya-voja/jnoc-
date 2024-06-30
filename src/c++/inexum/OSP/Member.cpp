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
 * File:		Serializable.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#include "Member.h"
#include "Serializable.h"
#include "JavaObjectSerializer.h"
#include "Object.h"
#include <inexum/util/Debug.h>

using namespace inexum::OSP;
using namespace inexum::util;

Member::Member(const std::string& type, const std::string& name, void* address)
	: m_address(address), m_name(name), m_type(type) 
{
}

Member::~Member() 
{
}

void* Member::address() const 
{ 
	return(m_address); 
}

void Member::description(JavaObjectSerializer& serializer)
{
	char typeCode = m_type[0];
	if(m_type.size() > 1)
	{
		if(m_type[0] != Serializable::ArrayCode())
			typeCode = 'L';
	}

	serializer.write((const byte*)&typeCode, sizeof(typeCode));

	unsigned short nameSize = (unsigned short) m_name.size();
	serializer.writeReverse((const byte*)&nameSize, sizeof(nameSize));
	serializer.write((const byte*)m_name.data(), nameSize);

	if(m_type.size() > 1)
		classTypeDescription(serializer);
}

void Member::serialize(JavaObjectSerializer& serializer) 
{
	if(m_address == NULL 
		|| isPointer() &&  *(int*)m_address == NULL)
	{
		serializer.writeNull();
	}
	else try
	{
		void* address = m_address;
		if(isPointer())
			address = (void*)*(int*)address;
		serializer.writeMember(address, m_type);
	}
	catch(...)
	{
		debug_line(DebugLine(Debug::c_serialize, "error S0004: Type '%s' cannot be serialized!", 
												m_type.data()));
		cerr << "error S0004: Type '" << m_type.data() 
								<< "' cannot be serialized!" << endl;
	}
}

const std::string& Member::name() const 
{
	return(m_name); 
}

bool Member::isBasicType() const
{
	return(m_type.size() < 2);
}

void Member::classTypeDescription(JavaObjectSerializer& serializer)
{
	std::string type(m_type);
	if(type.size() > 2)
	{
		bool isArray = false;
		if(type[0] == '[')
		{
			type = type.substr(1);
			isArray = true;
		}

		size_t a = type.find('.');
		while(std::string::npos != a )
		{
			type = type.replace(a, 1, "/");
			a = type.find('.');
		}
		type = "L" + type + ";";
		if(isArray)
			type = "[" +type;
	}

	serializer.writeString(type);
}

PointerMember::PointerMember(const std::string& type, const std::string& name, void* address) 
	: Member(type, name, address) 
{}

void PointerMember::initialize(Object& object, const std::string& classOwner)
{
	void* pObject = object.instantiate();
	void* memberAddress = address();
	if(*(int*)memberAddress != NULL)
		try
		{
			free((void*)(*(int*)memberAddress));
		}
		catch(...)
		{
			cerr << "warning S0001: Pointer to a member '" 
				<< classOwner.data() << "." << object.name().data() 
				<< "' sould be initialized in a '" << classOwner.data() 
				<< "' default constructor!" <<endl;
		}
	*(int*)(address()) = int(pObject);
}

ByValueMember::ByValueMember(const std::string& type, const std::string& name, void* address) 
	: Member(type, name, address) 
{}

void ByValueMember::initialize(Object& object, const std::string& classOwner)
{
	object.initialize(address());
}