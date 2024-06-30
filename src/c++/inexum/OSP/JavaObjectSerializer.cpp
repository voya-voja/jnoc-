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
 * File:		JavaObjectSerialization.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#include "JavaObjectSerializer.h"
#include "Serializable.h"
#include <inexum/util/Debug.h>

using namespace inexum;
using namespace inexum::OSP;
using namespace inexum::util;

const unsigned short	JavaObjectSerializer::c_magic = 0xaced;
const unsigned short	JavaObjectSerializer::c_version = 0x0005;

const byte				JavaObjectSerializer::c_tcNull = 0x70;
const byte				JavaObjectSerializer::c_tcReference = 0x71;
const byte				JavaObjectSerializer::c_tcClassDesription = 0x72;
const byte				JavaObjectSerializer::c_tcObject = 0x73;
const byte				JavaObjectSerializer::c_tcString = 0x74;
const byte				JavaObjectSerializer::c_tcArray = 0x75;
const byte				JavaObjectSerializer::c_tcClass = 0x76;
const byte				JavaObjectSerializer::c_tcBlockData = 0x77;
const byte				JavaObjectSerializer::c_tcEndBlockData = 0x78;
const byte				JavaObjectSerializer::c_tcReset = 0x79;
const byte				JavaObjectSerializer::c_tcBlockDataLong = 0x7A;
const byte				JavaObjectSerializer::c_tcException = 0x7B;

const byte				JavaObjectSerializer::c_classDescriptionFlags = 0x02;


namespace inexum { 
	namespace OSP 
	{
		class JavaBuiltinObjectSerializer : public JavaObjectSerializer
		{
			// size of the buffer
			const static size_t c_BufferSize;

			// data buffer
			byte		m_Buffer[2048];

			// size of data in the buffer
			size_t	m_DataSize;
		public:
			/** Overloaded constructor:
			  *
			  * @param output - the output object stream
			  */
			JavaBuiltinObjectSerializer(ostream& output) : JavaObjectSerializer(output), m_DataSize(0) {};

			/** Write a byte array to the buffer.
			  * If buffer is full, flush it.
			  *
			  * @param bytes - the reference to a byte array
			  * @param size - the size of a byte array
			  */
			void write(const byte* bytes, int size);

			 /* Write a byte array in reveresed order to the buffer.
			  * If buffer is full, flush it.
			  *
			  * @param bytes - the reference to a byte array
			  * @param size - the size of a byte array
			  */
			virtual void writeReverse(const byte* bytes, int size);

			 /* Test the serializer content of data.
			  *
			  * @return true if the buffer is empty
			  */
			bool isEmpty() const { return(m_DataSize == 0); } ;

			// Flush the byte buffer to the object stream.
			void flush();
		};
	} 
}

byte JavaObjectSerializer::tcArray()
{
	return(c_tcArray);
}

JavaObjectSerializer::~JavaObjectSerializer()
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "~JavaObjectSerializer"));
	if(m_pBuiltinSerializer != NULL)
		delete m_pBuiltinSerializer;
}

JavaObjectSerializer::JavaObjectSerializer(ostream& output) 
: m_output(output), m_NextHandle(0), m_pBuiltinSerializer(NULL)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "JavaObjectSerializer", 
				"ostream& output"));
}

void JavaObjectSerializer::writeStreamHeader()
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "writeStreamHeader"));
	writeReverse((const byte*)&c_magic, sizeof(c_magic));
	writeReverse((const byte*)&c_version, sizeof(c_version));
	m_output.flush();
}

void JavaObjectSerializer::run(const std::string& className, const void* address)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "run", 
				"class: '%s', address: '%d'", className.c_str(), address));

	if(m_pBuiltinSerializer != NULL && !m_pBuiltinSerializer->isEmpty())
		m_pBuiltinSerializer->flush();

	if(address == NULL)
		writeReverse((const byte*)&c_tcNull, sizeof(c_tcNull));
	else try
	{
		Serializable* pSerializableObject = 
						SerializableFactory::Instance().create(className);
		pSerializableObject->serialize(address, *this);
		delete pSerializableObject;
	}
	catch(...)
	{
		debug_line(DebugLine(Debug::c_serialize, 
			"error S0009: Object of class '%s' cannot be serialized!", 
													className.data()));
		cerr << "error S0009: Object of class '" << className.data() 
									<< "' cannot be serialized!" <<endl;
	}
	m_output.flush();
}

void JavaObjectSerializer::writeReverse(const byte* bytes, int size)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "writeReverse",
		"bytes: '%s', size: '%d'", (hexadecimal(bytes, size)).c_str(), size));
	for(int count = 0; count < size; count++)
	{
		m_output.put(bytes[ size - count - 1 ]);
	}
}

void JavaObjectSerializer::writeString(const std::string& str)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "writeString", 
				"str: '%s'", str.c_str()));
	if(str.size() == 0)
	{
		writeReverse((const byte*)&c_tcNull, sizeof(c_tcNull));
		return;
	}
	try
	{
		unsigned reference = handle(str);
		writeReverse((const byte*)&c_tcReference, sizeof(c_tcReference));
		writeReverse((const byte*)&reference, sizeof(reference));
		newHandle(str);
		return;
	}
	catch(...)
	{
	}

	writeReverse((const byte*)&JavaObjectSerializer::c_tcString, 
									sizeof(JavaObjectSerializer::c_tcString));
	newHandle(str);
	unsigned short strSize = (unsigned short) str.size();
	writeReverse((const byte*)&strSize, sizeof(strSize));
	write((const byte*)str.data(), strSize);
}


bool JavaObjectSerializer::referenced(const void* address)
{
	bool ret(false);
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "referenced", 
				"%d address: '%d'", &ret, address));
	try
	{
		unsigned reference = handle((unsigned)address);
		writeReverse((const byte*)&c_tcReference, sizeof(c_tcReference));
		writeReverse((const byte*)&reference, sizeof(reference));
		newHandle((unsigned)address);
		ret = true;
	}
	catch(...)
	{
		ret = false;
	}
	return(ret);
}

bool JavaObjectSerializer::referenced(const std::string& name)
{
	bool ret(false);
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "referenced", 
				"%d name: '%s'", &ret, name.c_str()));
	try
	{
		unsigned reference = handle("!class%" + name);
		writeReverse((const byte*)&c_tcReference, sizeof(c_tcReference));
		writeReverse((const byte*)&reference, sizeof(reference));
		newHandle("!class%" + name);
		ret = true;
	}
	catch(...)
	{
		ret = false;
	}
	return(ret);
}

void JavaObjectSerializer::remove(const void* address)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "remove", 
				"address: '%d'", address));
	static char addressStr[2*sizeof(unsigned) + 1];
	sprintf(addressStr, "%d", (int)address);
	m_handleMap.erase(std::string("!object@") + addressStr);
}

void JavaObjectSerializer::writeClassDescription(const std::string& name, 
												 unsigned short memberSize, 
												 JLong serialVersionUID)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "writeClassDescription", 
				"name: '%s', memberSize: '%d%', serialVersionUID: '%d%'", name.c_str(),
				memberSize, serialVersionUID));
	writeReverse((const byte*)&c_tcClassDesription, 
								sizeof(c_tcClassDesription));

	unsigned short nameSize = (unsigned short)name.size();
	writeReverse((const byte*)&nameSize, sizeof(nameSize));
	write((const byte*)name.data(), nameSize);

	writeReverse((const byte*)&serialVersionUID, sizeof(serialVersionUID));

	newHandle("!class%" + name);

	writeReverse((const byte*)&c_classDescriptionFlags, 
								sizeof(c_classDescriptionFlags));

	writeReverse((const byte*)&memberSize, sizeof(memberSize));
}


void JavaObjectSerializer::writeClassDescriptionEnd(const void* address, 
												 const std::string& superClassName)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "writeClassDescriptionEnd", 
				"address: '%d%', superClassName: '%s'", address, superClassName.c_str()));
	writeReverse((const byte*)&c_tcEndBlockData, sizeof(c_tcEndBlockData));
	if(superClassName.size() > 0)
	{
		Serializable* pSuperClass = 
					SerializableFactory::Instance().create(superClassName);
		pSuperClass->superClass();
		pSuperClass->serialize(address, *this);
		delete pSuperClass;
	}
	else
	{
		writeReverse((const byte*)&c_tcNull, sizeof(c_tcNull));
	}
	newHandle((unsigned)address);
}

void JavaObjectSerializer::writeMember(const void* address, 
										 const std::string& type)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "writeMember", 
				"address: '%d%', type: '%s'", address, type.c_str()));

	Serializable* pObject = SerializableFactory::Instance().create(type);
	pObject->serialize(address, *this);
	delete pObject;
}

void JavaObjectSerializer::writeNull()
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "writeNull"));
	writeReverse((const byte*)&c_tcNull, sizeof(c_tcNull));
}

unsigned JavaObjectSerializer::handle(const std::string& entityName)
{
	unsigned entityReference = (unsigned)-1;
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "handle", 
				"%d entityName: '%s'", &entityReference, entityName.c_str()));

	if(m_handleMap.find(entityName) == m_handleMap.end())
		throw SerializerException();
	entityReference = m_handleMap[ entityName ];
	return(JavaObjectParser::c_baseWireHandle + entityReference);
}

unsigned JavaObjectSerializer::handle(unsigned entityAddress)
{
	unsigned aHandle = 0;
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "handle", 
				"%d entityAddress: '%d%'", &aHandle, entityAddress));

	static char addressStr[2*sizeof(unsigned) + 1];
	sprintf(addressStr, "%d", (int)entityAddress);
	aHandle = handle(std::string("!object@") + addressStr);
	return(aHandle);
}

void JavaObjectSerializer::newHandle(const std::string& entityName)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "newHandle", 
				"entityName: '%s'", entityName.c_str()));

	if(isSerialized(entityName))
		return;

	debug_line(DebugLine(Debug::c_serialize, "handle: '%d'", m_NextHandle));

	m_handleMap.insert(HandlePair(entityName, m_NextHandle++));
}

void JavaObjectSerializer::newHandle(unsigned entityAddress)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "newHandle", 
				"entityAddress: '%d%'", entityAddress));
	static char addressStr[2*sizeof(unsigned) + 1];
	sprintf(addressStr, "%d", (int)entityAddress);
	newHandle(std::string("!object@") + addressStr);
}

inline bool JavaObjectSerializer::isSerialized(const std::string& entityName) const
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "isSerialized", 
				"entityName: '%s'", entityName.c_str()));
	return(m_handleMap.find(entityName) != m_handleMap.end());
}

void JavaObjectSerializer::write(const byte* bytes, int size) 
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "write",
		"bytes: '%s', size: '%d'", (hexadecimal(bytes, size, false)).c_str(), size));
	m_output.write((const char*)bytes, size); 
}

void JavaObjectSerializer::writeBuiltinObject(const std::string& typeName, const void* address)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "writeBuiltinObject", 
				"type: '%s', address: '%d'", typeName.c_str(), address));

	if(address == NULL)
		return;
	else try
	{
		Serializable* pSerializableObject = 
						SerializableFactory::Instance().create(typeName);
		pSerializableObject->serialize(address, builtinObjectSerializer());
		delete pSerializableObject;
	}
	catch(...)
	{
		debug_line(DebugLine(Debug::c_serialize, 
			"error S0010: Object of type '%s' cannot be serialized!", 
													typeName.data()));
		cerr << "error S0010: Object of type '" << typeName.data() 
									<< "' cannot be serialized!" <<endl;
	}
	m_output.flush();
}

void JavaObjectSerializer::reset()
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaObjectSerializer", "reset"));
	writeReverse((const byte*)&c_tcReset, sizeof(c_tcReset));
	m_handleMap.clear();
	m_NextHandle = 0;
}

JavaObjectSerializer& JavaObjectSerializer::builtinObjectSerializer() 
{ 
	if(m_pBuiltinSerializer == NULL)
		m_pBuiltinSerializer = new JavaBuiltinObjectSerializer(m_output);
	return(*m_pBuiltinSerializer); 
}

const size_t JavaBuiltinObjectSerializer::c_BufferSize(2048);

void JavaBuiltinObjectSerializer::write(const byte* bytes, int size)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaBuiltinObjectSerializer", "write",
		"bytes: '%s', size: '%d'", (hexadecimal(bytes, size, false)).c_str(), size));

	if(m_DataSize + size > c_BufferSize)
		flush();

	for(int count = 0; count < size; count++)
	{
		m_Buffer[m_DataSize++] = bytes[count];
	}
}

void JavaBuiltinObjectSerializer::writeReverse(const byte* bytes, int size)
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaBuiltinObjectSerializer", "writeReverse",
		"bytes: '%s', size: '%d'", (hexadecimal(bytes, size)).c_str(), size));

	if(m_DataSize + size > c_BufferSize)
		flush();

	for(int count = 0; count < size; count++)
	{
		m_Buffer[m_DataSize++] = bytes[ size - count - 1 ];
	}
}

void JavaBuiltinObjectSerializer::flush()
{
	debug_method(DebugMethod(Debug::c_serialize, "JavaBuiltinObjectSerializer", "flush",
		"bytes: '%s', size: '%d'", (hexadecimal(m_Buffer, m_DataSize, false)).c_str(), m_DataSize));

	if(m_DataSize < 256)
	{
		JavaObjectSerializer::write((const byte*)&JavaObjectSerializer::c_tcBlockData,
												sizeof(JavaObjectSerializer::c_tcBlockData));
		byte size = m_DataSize;
		JavaObjectSerializer::write((const byte*)&size, sizeof(byte));
	}
	else
	{
		JavaObjectSerializer::write((const byte*)&JavaObjectSerializer::c_tcBlockDataLong, 
												sizeof(JavaObjectSerializer::c_tcBlockDataLong));
		JavaObjectSerializer::writeReverse((const byte*)&m_DataSize, sizeof(m_DataSize));
	}
	JavaObjectSerializer::write(m_Buffer, m_DataSize);
	m_DataSize = 0;
	output().flush();
}
