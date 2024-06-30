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
 * File:		Class.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020615	nmv			create
 *----------------------------------------------------------------------------*/

#include "Object.h"
#include "Serializable.h"
#include <iostream.h>

#include "Class.h"
#include <inexum/util/Debug.h>

using namespace inexum::OSP;
using namespace inexum::util;

const byte Class::SC_SERIALIZABLE = 0x02;
const byte Class::SC_EXTERNALIZABLE = 0x04;
const byte Class::SC_WRITE_METHOD = 0x01;
const byte Class::SC_BLOCK_DATA = 0x08;

// create a copy Class symbol
Class::Class(const Class& right) 
	:Entity(right), m_membersCount(right.m_membersCount), 
		m_pSuperClass(NULL),
		m_classDescriptionFlags(right.m_classDescriptionFlags),
		m_currentMemberIndex(0)
{
	debug_method(DebugMethod(Debug::c_serialize, "Class", "Class", "right: %D", &DebugClass<Class>(right)));
	if(right.m_pSuperClass != NULL)	// clone a superclass
		m_pSuperClass = right.m_pSuperClass->clone();

	// clone all the class members
	ObjectList::const_iterator end = right.m_memberList.end();
	for(ObjectList::const_iterator at = right.m_memberList.begin(); at != end; at++)
	{
		Object* pMember = (*at)->clone();
		m_memberList.push_back(pMember);
		m_members.insert(ObjectPair(pMember->name(), pMember));
	}
}

// remove a class symbol
Class::~Class()
{
	debug_method(DebugMethod(Debug::c_serialize, "Class", "~Class",
													"destruct: %s", name().c_str()));
	// remove members.
	ObjectList::const_iterator end = m_memberList.end();
	for(ObjectList::const_iterator at = m_memberList.begin(); at != end; at++)
	{
		delete *at;
	}
	if(m_pSuperClass != NULL) // remove a superclass
		delete m_pSuperClass;
}

// position at a indexed member
void Class::moveToMember(int index)
{
	debug_method(DebugMethod(Debug::c_serialize, "Class", "moveToMember", "index: %d", index));
	if(m_pSuperClass != NULL)
	{
		// if superclass present position supeclass at specified index
		m_pSuperClass->moveToMember(index);
		m_currentMemberIndex = 0;
	}
	else
		m_currentMemberIndex = index;
}

Object& Class::nextMember()
{
	Object* pObject = NULL;
	debug_method(DebugMethod(Debug::c_serialize, "Class", "nextMember", "%D", &DebugClass<Object>(*pObject)));

	// if superclass is present and has more members to iterate through
	if(m_pSuperClass != NULL && !m_pSuperClass->isLastMember())
		pObject = &m_pSuperClass->nextMember();
	else // return a current memebr and move to the next
		pObject = m_memberList[m_currentMemberIndex++];

	return(*pObject);
}

void Class::add(Object& member)
{
	debug_method(DebugMethod(Debug::c_serialize, "Class", "add", "member: %D", &DebugClass<Object>(member)));
	// maintan the map of member names and member reference
	m_members.insert(ObjectPair(member.name(), &member));

	// maintain the ordered list of the members
	m_memberList.push_back(&member);
}

// parsing control method
int Class::classDescriptionFlag2Token() const
{
	int ret = JavaObjectParser::InsertNoToken();
	debug_method(DebugMethod(Debug::c_serialize, "Class", "classDescriptionFlag2Token", "%x", &ret));
	// class description flag difines the parsing mode
	switch(m_classDescriptionFlags)
	{
	case SC_SERIALIZABLE:
		ret = NOWRCLASS;
		break;
	case SC_EXTERNALIZABLE:
		ret = WRCLASS;
		break;
	case SC_WRITE_METHOD:
		ret = EXTERNAL_CONTENTS;
		break;
	case SC_BLOCK_DATA:
		ret = OBJECT_ANNOTATIONS;
		break;
	}
	return(ret);
}

// instantiate and initialize a C++ object
void* Class::instantiate() const
{
	void* pObject = NULL;
	debug_method(DebugMethod(Debug::c_serialize, "Class", "instantiate", "%p", &pObject));
	try
	{
		// create the objects serialization wrapper to perform the instantiation
		Serializable* pSerializableObject = 
							SerializableFactory::Instance().create(name());
		pSerializableObject->initialize(*this);
		pObject = pSerializableObject->object();
		if(m_pSuperClass != NULL) // initialize object's superclass part
		{
			m_pSuperClass->initialize(pObject);
		}
		delete pSerializableObject;
		return(pObject);
	}
	catch(...)
	{
		debug_line(DebugLine(Debug::c_serialize, "error S0002: Class '%s' is not serializable!", 
															name().data()));
		cerr << "error S0002: Class '" << name().data() << 
								"' is not serializable!" << endl;
	}
	return(pObject);
}

// initialize a C++ object starting @ specified address
void Class::initialize(void* address) const
{
	debug_method(DebugMethod(Debug::c_serialize, "Class", "initialize", "address: %p", address));
	try
	{
		// create the objects serialization wrapper to perform the initialization
		// at the specified address
		Serializable* pSerializableObject = 
							SerializableFactory::Instance().create(name());
		pSerializableObject->initialize(address, *this);
		if(m_pSuperClass != NULL) // initialize object's superclass part
		{
			m_pSuperClass->initialize(address);
		}
		delete pSerializableObject;
	}
	catch(...)
	{
		debug_line(DebugLine(Debug::c_serialize, "error S0008: Class '%s' is not serializable!", 
															name().data()));
		cerr << "error S0008: Class '" << name().data() << 
								"' is not serializable!" << endl;
	}
}

#ifdef iNxmDebug
	// A debug method that dumps the Class content
	template<> void DebugClass<Class>::print()
	{
		if(&object() == NULL)
		{
			output(std::string("NULL Object"));
			return;
		}
		// first print superclass content
		if(object().m_pSuperClass != NULL)
		{
			DebugClass<Class>(Debug::c_serialize, *object().m_pSuperClass).print();
		}
		output(object().name() + ": START");
		increaseIndent();
		Class::ObjectList::const_iterator end = object().m_memberList.end();
		for(OSP::Class::ObjectList::const_iterator at = object().m_memberList.begin(); at != end; at++)
		{
			DebugClass<Object>(Debug::c_serialize, **at).print();
		}
		decreaseIndent();
		output(object().name() + " END");
	}

	// A debug method that dumps the Object content
	template<> void inexum::util::DebugClass<Object>::print()
	{
		if(object().m_pReferencedObject == NULL)
		{
			DebugClass<Entity>(Debug::c_serialize, object()).print();
			output() << "[" << object().m_address  << "]";
		}
		else
			DebugClass<Object>(Debug::c_serialize, 
								*object().m_pReferencedObject).print();
	}
#endif	// iNxmDebug
