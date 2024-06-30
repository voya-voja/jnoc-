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
 * File:		ObjectOutputStream.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					021003	nmv			create
 *----------------------------------------------------------------------------*/
#include "inexum/definitions.h"


#include "ObjectOutputStream.h"

#include <inexum/OSP/JavaObjectSerializer.h>
#include <inexum/OSP/Serializable.h>
#include <inexum/util/Debug.h>
#include <string.h>

using namespace std;
using namespace inexum::OSP;
using namespace inexum::util;
using namespace java::io;

ObjectOutputStream::ObjectOutputStream(std::ostream& output) 
	:std::ostream(output.rdbuf()), m_pObjectSerializer(new JavaObjectSerializer(output))
{
	debug_method(DebugMethod(Debug::c_net, "ObjectOutputStream", "ObjectOutputStream", 
				"ostream& output"));
	m_pObjectSerializer->writeStreamHeader(); 
}

ObjectOutputStream::~ObjectOutputStream()
{
	debug_method(DebugMethod(Debug::c_net, "ObjectOutputStream", "~ObjectOutputStream")); 
	delete m_pObjectSerializer;
}

void ObjectOutputStream::writeObject(const void* object, const std::string& className)
{
	debug_method(DebugMethod(Debug::c_net, "ObjectOutputStream", "writeObject", 
				"object: '%d', class: '%s'", object, className.c_str()));

	std::string javaClassName = Serializable::CppJavaNamesRegister::javaName(className);
	m_pObjectSerializer->run(javaClassName, object);
}

void ObjectOutputStream::writeBuiltinObject(const void* object, const std::string& typeName)
{
	debug_method(DebugMethod(Debug::c_net, "ObjectOutputStream", "writeBuiltinObject", 
				"object: '%d', type: '%s'", object, typeName.c_str()));

	std::string javaTypeName = Serializable::CppJavaNamesRegister::javaName(typeName);
	m_pObjectSerializer->writeBuiltinObject(javaTypeName, object);
}

void ObjectOutputStream::write(const byte* buffer)
{
	m_pObjectSerializer->builtinObjectSerializer().write(buffer, strlen((const char*)buffer));
}

void ObjectOutputStream::write(const byte* buffer, size_t len)
{
	m_pObjectSerializer->builtinObjectSerializer().write(buffer, len);
}

void ObjectOutputStream::write(const byte* buffer, size_t offset, size_t len)
{
	m_pObjectSerializer->builtinObjectSerializer().write(buffer + offset, len);
}

void ObjectOutputStream::writeChars(const wchar_t* buffer)
{
	size_t len = wcslen(buffer);
	JavaObjectSerializer& serializer = m_pObjectSerializer->builtinObjectSerializer();
	const size_t cCharSize = sizeof(wchar_t);
	for(size_t cCount = 0; cCount < len; cCount++)
		serializer.write((const byte*)&buffer[cCount], cCharSize);
}

void ObjectOutputStream::reset()
{
	m_pObjectSerializer->reset();
}