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

#include "Serializable.h"

#include "JavaObjectSerializer.h"
#include <inexum/stl/StringLableCreator.h>
#include <inexum/util/Debug.h>
#include <iostream.h>

using namespace inexum;
using namespace inexum::OSP;
using namespace inexum::util;

const char		Serializable::c_ArrayCode = '[';
const size_t	Serializable::c_classSize = 6;

const char Serializable::ArrayCode() { return(c_ArrayCode); }

const size_t Serializable::ClassSize() { return(c_classSize); }

Serializable::CppJavaNamesRegister::CppJavaNamesMap*	
		Serializable::CppJavaNamesRegister::CppJavaNamesSingleton::gm_pCppJavaNamesMap = NULL;

Serializable::CppJavaNamesRegister::CppJavaNamesSingleton::~CppJavaNamesSingleton()
{
	if(gm_pCppJavaNamesMap == NULL)
	{
		delete gm_pCppJavaNamesMap;
	}
}

Serializable::CppJavaNamesRegister::CppJavaNamesMap* 
		Serializable::CppJavaNamesRegister::CppJavaNamesSingleton::cppJavaNamesMap()
{ 
	if(gm_pCppJavaNamesMap == NULL)
	{
		gm_pCppJavaNamesMap = new CppJavaNamesMap;
	}
	return(gm_pCppJavaNamesMap); 
}

Serializable::CppJavaNamesRegister::CppJavaNamesRegister(const std::string& cppName, const std::string& javaName)
{
	std::string subStr = cppName.substr(0, Serializable::ClassSize());
	if(subStr == "[class")
	{
		subStr = cppName.substr(Serializable::ClassSize());
		CppJavaNamesSingleton::Instance().cppJavaNamesMap()->insert(CppJavaNamesPair(subStr, javaName));
	}
	else
		CppJavaNamesSingleton::Instance().cppJavaNamesMap()->insert(CppJavaNamesPair(cppName, javaName));
}

const std::string& Serializable::CppJavaNamesRegister::javaName(const std::string& cppName)
{
	CppJavaNamesMap::const_iterator end = CppJavaNamesSingleton::Instance().cppJavaNamesMap()->end();
	CppJavaNamesMap::const_iterator at = CppJavaNamesSingleton::Instance().cppJavaNamesMap()->find(cppName);
	if(at == end)
	{
		std::string name("[");
		if(cppName.substr(5,6) == "vector")
		{
			size_t offset = 12;
			if(cppName.substr(offset, Serializable::ClassSize()) == "class ")
				offset += Serializable::ClassSize();

			size_t typeEnd = cppName.find(',', offset);
			name += cppName.substr(offset, typeEnd - offset);
		}
		else if(cppName.substr(13,9) == "VectorPtr")
		{
			size_t offset = 23 + Serializable::ClassSize();
			name += cppName.substr(offset, cppName.size() - (offset + 2));
		}
		else if(cppName.substr(13,6) == "Vector")
		{
			size_t offset = 20;
			if(cppName.substr(offset, Serializable::ClassSize()) == "class ")
				offset += Serializable::ClassSize();

			name += cppName.substr(offset, cppName.size() - (offset + 1));
		}
		else
			throw JavaObjectSerializer::SerializerException();
		at = CppJavaNamesSingleton::Instance().cppJavaNamesMap()->find(name);
	}
	return(at->second);
}

Serializable::ObjectHandler::~ObjectHandler()
{
	if(m_Address != NULL)
	{
		m_pSerializer->remove(m_Address);
	}
}

byte Serializable::objectTypeCode() const
{ 
	return(JavaObjectSerializer::c_tcObject);
}
