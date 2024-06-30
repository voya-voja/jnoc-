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
 * File:		BuiltinObject.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020615	nmv			create
 *----------------------------------------------------------------------------*/

#include "inexum/definitions.h"
#include "BuiltinObject.h"
#include <inexum/stl/Creator.h>
#include "StringObject.h"
#include "SerializableVoidPointerArray.h"
#include <inexum/java_serializable.h>
#include <inexum/Types.h>

using namespace inexum;
using namespace inexum::stl;
using namespace inexum::OSP;
using namespace inexum::util;

const std::string PrimitiveObject::c_primitiveTypes( "BCDFIJSZ" );

template Creator<char, 'B', Object, BuiltinObject<byte, JavaObjectParser::k_ReadByte> >;
template Creator<char, 'C', Object, BuiltinObject<char, JavaObjectParser::k_ReadChar> >;
template Creator<char, 'D', Object, BuiltinObject<double, JavaObjectParser::k_ReadDouble> >;
template Creator<char, 'F', Object, BuiltinObject<float, JavaObjectParser::k_ReadFloat> >;
template Creator<char, 'I', Object, BuiltinObject<int, JavaObjectParser::k_ReadInt> >;
template Creator<char, 'J', Object, BuiltinObject<JLong, JavaObjectParser::k_ReadLong> >;
template Creator<char, 'S', Object, BuiltinObject<short, JavaObjectParser::k_ReadShort> >;
template Creator<char, 'Z', Object, BuiltinObject<bool, JavaObjectParser::k_ReadBoolean> >;
template Creator<char, '"', Object, StringObject >;

inexum::OSP::Serializable::CppJavaNamesRegister g_byteRegister(typeid(byte).name(), "B");
inexum::OSP::Serializable::CppJavaNamesRegister g_charRegister(typeid(wchar_t).name(), "C");
inexum::OSP::Serializable::CppJavaNamesRegister g_doubleRegister("double", "D");
inexum::OSP::Serializable::CppJavaNamesRegister g_floatRegister("float", "F");
inexum::OSP::Serializable::CppJavaNamesRegister g_intRegister("int", "I");
inexum::OSP::Serializable::CppJavaNamesRegister g_longRegister(typeid(JLong).name(), "J");
inexum::OSP::Serializable::CppJavaNamesRegister g_shortRegister("short", "S");
inexum::OSP::Serializable::CppJavaNamesRegister g_boolRegister("bool", "Z");

/*-------------------------------------------------------------------------------
 *        Serialize arrays of Java built in types
 *-----------------------------------------------------------------------------*/
serialize_array("B",				byte,			0xACF317F8060854E0);
serialize_array("C",				wchar_t,		0xB02666B0E25D84AC);
serialize_array("D",				double,			0x3EA68C14AB635A1E);
serialize_array("F",				float,			0xB9C818922E00C42);
serialize_array("I",				int,			0x4DBA602676EAB2A5);
serialize_array("J",				JLong,			0x782004B512B17593);
serialize_array("S",				short,			0xEF832E06E55DB0FA); 
serialize_array("Z",				bool,			0x578F203914B85DE2);

/*-------------------------------------------------------------------------------
 *        Serialize array of references to java.lang.Object class
 *-----------------------------------------------------------------------------*/
template class inexum::stl::CreateWithStringLable<inexum::OSP::Serializable, 
													inexum::OSP::SerializableVoidPointerArray >;
inexum::stl::CreateWithStringLable<inexum::OSP::Serializable, 
									inexum::OSP::SerializableVoidPointerArray >
	inexum::stl::CreateWithStringLable<inexum::OSP::Serializable, 
									inexum::OSP::SerializableVoidPointerArray
								>::g_Creator(inexum::OSP::Serializable::ArrayCode() + 
												std::string("java.lang.Object"));
inexum::OSP::Serializable::CppJavaNamesRegister g_voidPtrRegister(
								typeid(std::vector<void*>).name() + 
									inexum::OSP::Serializable::ClassSize(), "[java.lang.Object");

#ifdef iNxmDebug

	template<> void DebugClass<bool>::print()
	{
		if(object())
			output() << "true";
		else
			output() << "false";
	}

	template<> void DebugClass<inexum::JLong>::print()
	{
		if(object())
			output() << object();
	}

	template<> void DebugClass<std::vector<bool> >::print()
	{
		std::vector<bool>::const_iterator end = object().end();
		std::vector<bool>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
		{
			DebugClass<bool>(*at).print();
			output() << ", ";
		}
		output() << "}" << endl;
	}

	template<> void DebugClass<std::vector<byte> >::print()
	{
		std::vector<byte>::const_iterator end = object().end();
		std::vector<byte>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
			output() << (short)*at << ", ";
		output() << "}" << endl;
	}

	template<> void DebugClass<std::vector<wchar_t> >::print()
	{
		std::vector<wchar_t>::const_iterator end = object().end();
		std::vector<wchar_t>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
			output() << (char)*at << ", ";
		output() << "}" << endl;
	}

	template<> void DebugClass<std::vector<double> >::print()
	{
		std::vector<double>::const_iterator end = object().end();
		std::vector<double>::const_iterator at = object().begin();
		output() << " { ";
		char* number = new char[21];
		for(; at != end; at++)
		{
			sprintf(number, "%20.9f", *at);
			output() << number << ", ";
		}
		delete number;
		output() << "}" << endl;
	}

	template<> void DebugClass<std::vector<float> >::print()
	{
		std::vector<float>::const_iterator end = object().end();
		std::vector<float>::const_iterator at = object().begin();
		output() << " { ";
		char* number = new char[13];
		for(; at != end; at++)
		{
			sprintf(number, "%12.5f", *at);
			output() << number << ", ";
		}
		delete number;
		output() << "}" << endl;
	}

	template<> void DebugClass<std::vector<int> >::print()
	{
		std::vector<int>::const_iterator end = object().end();
		std::vector<int>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
			output() << *at << ", ";
		output() << "}" << endl;
	}

	template<> void DebugClass<std::vector<JLong> >::print()
	{
		std::vector<JLong>::const_iterator end = object().end();
		std::vector<JLong>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
			output() << *at << ", ";
		output() << "}" << endl;
	}

	template<> void DebugClass<std::vector<short> >::print()
	{
		std::vector<short>::const_iterator end = object().end();
		std::vector<short>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
			output() << *at << ", ";
		output() << "}" << endl;
	}

	template<> void DebugClass<std::vector<std::string> >::print()
	{
		std::vector<std::string>::const_iterator end = object().end();
		std::vector<std::string>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
			output() << "'" << (*at).c_str() << "', ";
		output() << "}" << endl;
	}

	template<> DebugClass<VectorPtr<std::string> >;

	template<> void DebugClass<VectorPtr<std::string> >::print()
	{
		VectorPtr<std::string>::const_iterator end = object().end();
		VectorPtr<std::string>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
			output() << "'" << (*at)->c_str() << "', ";
		output() << "}" << endl;
	}

	template<> DebugClass<VectorPtr<std::string> >;
	// A debug method that dumps the Object content
	template<> void util::DebugClass<OSP::BuiltinObject<byte, JavaObjectParser::k_ReadByte> >::print()
	{
		output() << indent() << object().m_value;
	}

	// A debug method that dumps the Object content
	template<> void util::DebugClass<OSP::BuiltinObject<char, JavaObjectParser::k_ReadChar> >::print()
	{
		output() << indent() << object().m_value;
	}

	// A debug method that dumps the Object content
	template<> void util::DebugClass<OSP::BuiltinObject<double, JavaObjectParser::k_ReadDouble> >::print()
	{
		output() << indent() << object().m_value;
	}

	// A debug method that dumps the Object content
	template<> void util::DebugClass<OSP::BuiltinObject<float, JavaObjectParser::k_ReadFloat> >::print()
	{
		output() << indent() << object().m_value;
	}

	// A debug method that dumps the Object content
	template<> void util::DebugClass<OSP::BuiltinObject<int, JavaObjectParser::k_ReadInt> >::print()
	{
		output() << indent() << object().m_value;
	}

	// A debug method that dumps the Object content
	template<> void util::DebugClass<OSP::BuiltinObject<JLong, JavaObjectParser::k_ReadLong> >::print()
	{
		output() << indent() << object().m_value;
	}

	// A debug method that dumps the Object content
	template<> void util::DebugClass<OSP::BuiltinObject<short, JavaObjectParser::k_ReadShort> >::print()
	{
		output() << indent() << object().m_value;
	}

	// A debug method that dumps the Object content
	template<> void util::DebugClass<OSP::BuiltinObject<bool, JavaObjectParser::k_ReadBoolean> >::print()
	{
		output() << indent() << object().m_value;
	}

	// A debug method that dumps the Object content
	template<> void util::DebugClass<OSP::StringObject>::print()
	{
		output() << indent() << "'" << object().m_value << "'";
	}
#endif	// iNxmDebug
