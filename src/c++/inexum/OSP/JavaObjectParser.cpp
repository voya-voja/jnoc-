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
 * File:		JavaObjectParser.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020615	nmv			create
 *----------------------------------------------------------------------------*/
#include "JavaObjectParser.h"

#include "javaObjParser.h"
#include <inexum/util/Debug.h>

#include "Entity.h"
#include "Class.h"
#include "Array.h"
#include "Object.h"
#include "BuiltinObject.h"
#include "ClassObject.h"
#include "ArrayObject.h"
#include "StringObject.h"
#include "PrimitiveValue.h"
#include "BlockData.h"
#include <inexum/stl/Factory.h>

using namespace inexum;
using namespace inexum::OSP;
using namespace inexum::util;

typedef stl::Factory<char, Object> ObjectFactory;

const unsigned JavaObjectParser::c_baseWireHandle = 0x7E0000;
const int JavaObjectParser::g_insertNoToken = -1;

#ifdef YYiNexumDebug
	namespace inexum { namespace OSP { extern int yydebug; } }
#endif

JavaObjectParser::JavaObjectParser(istream& input)
:m_input(input), 
	m_pFirstObject(NULL),
	m_tokenCount(0),
	m_state(k_ReadShort),
	m_stringSize(-1), 
	m_tokenCount2string(-1),
	m_magic(0), 
	m_version(-1),
	m_serialVersionUID(-1), 
	m_handle(c_baseWireHandle) 
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "JavaObjectParser", 
				"istream& input"));
#ifdef YYiNexumDebug
	yydebug = 1;
#endif
}

JavaObjectParser::~JavaObjectParser()
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "~JavaObjectParser"));
	if(m_pFirstObject != NULL)
	{
		debug_line(DebugLine(Debug::c_serialize|Debug::c_net, "Parsed Object: %D", &DebugClass<Object>(*m_pFirstObject)));
		delete m_pFirstObject;
	}
	int count = 0;
	EntityVector::const_iterator theEnd = m_referencedEntities.end();
	for(EntityVector::iterator at = m_referencedEntities.begin(); 
															at < theEnd; at++)
	{
		count++;
		try
		{
			delete *at;
		}
		catch(...) 
		{}
	}
}


void JavaObjectParser::run() 
{ 
	debug_method(DebugMethod(Debug::c_serialize|Debug::c_net, "JavaObjectParser", "run"));
	resetParserVariables();
	yyparse((void*)this);
}

inline void JavaObjectParser::resetParserVariables()
{
	debug_method(DebugMethod(Debug::c_serialize|Debug::c_net, "JavaObjectParser", 
																"resetParserVariables"));
	BlockData* pBlockData = dynamic_cast<BlockData*>(m_pFirstObject);
	if(pBlockData != 0)
		delete pBlockData;
	m_pFirstObject =		NULL;
	m_tokenCount =			0;
	m_state =				k_ReturnByte;
	m_stringSize =			-1;
	m_tokenCount2string =	-1;
	m_magic =				0;
	m_version =				-1;
	m_serialVersionUID =	-1;
	Entity* entity = NULL;
	while(!m_parsingEntities.empty())
	{
		debug_line(DebugLine(Debug::c_serialize, "stack top: %s", 
									m_parsingEntities.top()->name().c_str()));
		m_parsingEntities.pop();
	}
}

void JavaObjectParser::reset()
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "reset"));
	m_referencedEntities.clear();
	m_handle =				c_baseWireHandle;
	resetParserVariables();
}

int JavaObjectParser::insertToken() 
{
	int token = getInsertedToken();
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "insertToken", "%d", &token));

	if(m_tokenCount2string == 0)
	{
		debug_line(DebugLine(Debug::c_serialize, "'Read string' state."));
		state(k_ReadString);
	}
	if(m_tokenCount2string >= 0)
	{
		m_tokenCount2string--;
	}
	return(token); 
}

void JavaObjectParser::addClassDescription(const std::string& name, JLong uid, int handle)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "addClassDescription", 
				"name: %s, uid: %D, handle: %d", name.c_str(), 
					&DebugClass<JLong>(uid), 
					handle - c_baseWireHandle));
	Class* pClass = NULL;
	if(name[0] == '[')
	{
		pClass = new Array;
	}
	else
	{
		pClass = new Class;
	}
	pClass->setName(name); 
	m_referencedEntities.push_back(pClass);
	m_parsingEntities.push(pClass);
}

void JavaObjectParser::classDescriptionFlags(byte flags)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "classDescriptionFlags", 
								"flags: %x", flags));
	Class& aClass = *dynamic_cast<Class*>(m_parsingEntities.top());
	aClass.classDescriptionFlags(flags);
}

void JavaObjectParser::superClass(Class* pClass)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "superClass", 
						"class: %D", &DebugClass<Class>(*pClass)));
	if(pClass == NULL) return;

	Class& aClass = *dynamic_cast<Class*>(m_parsingEntities.top());
	aClass.superClass(*pClass);
	getInsertedToken();
}

Class* JavaObjectParser::classDescriptionEnd()
{
	Class* pClass = NULL;
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "classDescriptionEnd", 
						"%D", &DebugClass<Class>(*pClass)));
	pClass = dynamic_cast<Class*>(m_parsingEntities.top());
	m_parsingEntities.pop();
	setInsertToken(pClass->classDescriptionFlag2Token());
	return(pClass);
}

void JavaObjectParser::newObject(Class* pClass, int handle)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "newObject", 
						"class: %D, handle: %d", 
						&DebugClass<Class>(*pClass), 
						handle - c_baseWireHandle));
	ClassObject* pObject = NULL;
	if(m_pFirstObject == NULL)
	{
		pObject = new ClassObject(*pClass) ;
		pObject->setName("object");
		m_pFirstObject = pObject;
		m_parsingEntities.push(pObject);
		debug_line(DebugLine(Debug::c_serialize, "push[%D]", 
					&DebugClass<ClassObject>(*pObject)));
	}
	else
	{
		pObject = dynamic_cast<ClassObject*>(m_parsingEntities.top());
		pObject->setClass(pClass);
	}
	m_referencedEntities.push_back(pObject);

	pClass->moveToMember(0);
	if(pClass->isLastMember())
	{
		int token = getInsertedToken();
		setInsertToken(pObject->getEndToken());
		setInsertToken(token);
	}
	else
		valueStart();
}

void JavaObjectParser::newArray(Class* pClass, int handle)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "newArray", 
						"class: %D, handle: %d", 
						&DebugClass<Class>(*pClass), 
						handle - c_baseWireHandle));
	if(m_pFirstObject == NULL)
	{
		m_pFirstObject = new ArrayObject(*pClass);
		m_pFirstObject->setName("object");
		m_parsingEntities.push(m_pFirstObject);
		m_referencedEntities.push_back(m_pFirstObject);
		debug_line(DebugLine(Debug::c_serialize, "push[%D]", 
					&DebugClass<ArrayObject>(*(ArrayObject*)m_pFirstObject)));
	}
	else
	{
		ArrayObject& object = *dynamic_cast<ArrayObject*>(m_parsingEntities.top());
		m_referencedEntities.push_back(&object);
		object.setClass(pClass);
		state(k_ReadInt);
	}
}

void JavaObjectParser::newString(const std::string& str, int handle)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "newString", 
						"str: %s, handle: %d", 
						str.c_str(), 
						handle - c_baseWireHandle));
	StringObject* pObject = new StringObject(str, str);
	if(m_pFirstObject == NULL && m_parsingEntities.size() == 0)
	{
		m_parsingEntities.push(pObject);
		m_pFirstObject = pObject;
	}

	m_referencedEntities.push_back(pObject);
}

void JavaObjectParser::newString(const std::string& newString)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "newString", 
						"str: %s", newString .c_str()));
	StringObject& object = 
				*dynamic_cast<StringObject*>(m_parsingEntities.top() );
	object.value(newString);
	debug_line(DebugLine(Debug::c_serialize, "string object: %D", &DebugClass<StringObject>(object)));
}

int JavaObjectParser::newHandle()
{
	int handle = m_handle;
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "newHandle", 
						"handle: %d", handle - c_baseWireHandle));
	m_handle++;
	return(handle);
}

void JavaObjectParser::addMembers(int count)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "addMembers", 
						"memberCount: %d", count));
	Class& aClass = *dynamic_cast<Class*>(m_parsingEntities.top());
	aClass.membersCount(count);
}

void JavaObjectParser::addMember(char type, const std::string& name)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "addMember", 
						"type: %c, name: %s", type, name.c_str()));
	Object* pMember = ObjectFactory::Instance().create(type);
	pMember->setName(name);
	Class& aClass = *dynamic_cast<Class*>(m_parsingEntities.top());
	aClass.add(*pMember);
}

void JavaObjectParser::addMember(char type, const std::string& name, const std::string& typeName)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "addMember", 
						"type: %s <%c>, name: %s", 
						typeName.c_str(), type, name.c_str()));
	Object* pMember = NULL;
	if(type == '[')
		pMember = new ArrayObject(name);
	else if(typeName == "Ljava/lang/String;")
		pMember = new StringObject(name);
	else if(type == 'L')
		pMember = new ClassObject(name);

	Class& aClass = *dynamic_cast<Class*>(m_parsingEntities.top());
	aClass.add(*pMember);
}

void JavaObjectParser::classDataListStart()
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "classDataListStart"));
	ClassObject& object = *dynamic_cast<ClassObject*>(m_parsingEntities.top());
	object.moveToMember(0);
	debug_line(DebugLine(Debug::c_serialize, "object: %D", &DebugClass<ClassObject>(object)));
	if(object.isLastMember())
	{
		setInsertToken(object.getEndToken());
	}
}

void JavaObjectParser::arrayStart()
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "arrayStart"));
}

void JavaObjectParser::elementArrayStart(int count)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "elementArrayStart", 
						"elementCount: %d", count));
	ArrayObject& array = *dynamic_cast<ArrayObject*>(m_parsingEntities.top());
	array.addElements(count);
	if(count == 0)
		setInsertToken(array.getEndToken());
	else
		valueStart();
}

void JavaObjectParser::add(Value* pValue)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "add", 
						"value: %D", &DebugClass<Value>(*pValue)));
	PrimitiveObject& object = *dynamic_cast<PrimitiveObject*>(m_parsingEntities.top());
	object.setValue(pValue );
}

void JavaObjectParser::valueStart()
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "valueStart"));
	ClassObject& object = *dynamic_cast<ClassObject*>(m_parsingEntities.top());
	if(!object.isLastMember())
	{
		Object& aNextMember = object.nextMember();
		m_parsingEntities.push(&aNextMember);
		state(aNextMember.getState());
		debug_line(DebugLine(Debug::c_serialize, "push[%D]", &DebugClass<Object>(aNextMember)));
	}
}

void JavaObjectParser::valueEnd()
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "valueEnd"));
	debug_line(DebugLine(Debug::c_serialize, "pop[%D]", &DebugClass<Entity>(*m_parsingEntities.top())));

	m_parsingEntities.pop();
	ClassObject& object = *dynamic_cast<ClassObject*>(m_parsingEntities.top());
	if(object.isLastMember())
	{
		setInsertToken(object.getEndToken());
	}
	setInsertToken(VALUE_END);
}

void JavaObjectParser::objectNewClassDescription(Class* pClass)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "objectNewClassDescription", 
						"class: %D", &DebugClass<Class>(*pClass)));
	debug_line(DebugLine(Debug::c_net, "JavaObjectParser::objectNewClassDescription(Class*) NOT SUPPORTED!"));
}

void JavaObjectParser::object(Entity* pEntity)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "object", 
						"entity: %p", pEntity));
#ifdef iNxmDebug
	if(pEntity != NULL)
		debug_line(DebugLine(Debug::c_serialize, "entity: %D", &DebugClass<Entity>(*pEntity)));
#endif	// iNxmDebug
}

void JavaObjectParser::addClass(Class* pClass)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "addClass", 
						"class: %D", &DebugClass<Class>(*pClass)));
	debug_line(DebugLine(Debug::c_basic, "JavaObjectParser::addClass(Class*) NOT SUPPORTED!"));
}

Class* JavaObjectParser::classDescReference(int handle)
{
	int ref = handle - c_baseWireHandle;
	Class* pClass = NULL;
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "classDescReference", 
						"%D handle : %d", &DebugClass<Class>(*pClass), ref));
	int size = m_referencedEntities.size();
	pClass = dynamic_cast<Class*>(m_referencedEntities[ ref ]);
	setInsertToken(pClass->classDescriptionFlag2Token());
	return(pClass);
}

char* JavaObjectParser::stringReference(int handle) const
{
	int ref = handle - c_baseWireHandle;
	char* str = NULL;
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "stringReference", 
						"%s handle : %d", &str, ref));
	StringObject& object = 
		*dynamic_cast<StringObject*>(m_referencedEntities[ ref ]);
	const std::string& value = object.value();
	str = new char[ value.size() + 1 ];
	strcpy(str, value.data());
	return(str);
}

Entity* JavaObjectParser::objectReference(int handle)
{
	int ref = handle - c_baseWireHandle;
	Object* pObject = NULL;
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "objectReference", 
						"%D handle : %d", &DebugClass<Object>(*pObject), ref));
	pObject = dynamic_cast<Object*>(m_referencedEntities[ ref ]);
	Object& objectReference = *dynamic_cast<Object*>(m_parsingEntities.top());
	objectReference.reference(*pObject);

	return(pObject);
}

void JavaObjectParser::newBlockData(int size)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "newBlockData", 
						"size: %d", size));
	BlockData* pBlockData = dynamic_cast<BlockData*>(m_pFirstObject);
	if(pBlockData != 0 && pBlockData->size() >= size)
		pBlockData->reset();
	else
		pBlockData = new BlockData(size);

	byte* buffer = *pBlockData;
	for(size_t cBytes = 0; cBytes < size; cBytes++)
		buffer[cBytes] = (byte)m_input.get();
	pBlockData->full();

	if(m_pFirstObject == NULL)
	{
		m_pFirstObject = pBlockData;
	}
	else
	m_parsingEntities.push(pBlockData);
	setInsertToken(BYTES_END);
	state(k_ReturnByte);
}

void JavaObjectParser::addByte(byte aByte)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectParser", "add", 
						"byte: %c", aByte));
	BlockData& object = *dynamic_cast<BlockData*>(m_parsingEntities.top());
	object.add(aByte);
	if(object.isFull())
	{
		setInsertToken(BYTES_END);
		state(k_ReturnByte);
	}
}

void JavaObjectParser::endTest(int yystate)
{
//	if(yystate == finalState() - 2)
		setInsertToken(0);
}

#ifdef iNxmDebug
	template <> void DebugClass<Value>::print()
	{
		object().print(output());
	}
#endif	// iNxmDebug


