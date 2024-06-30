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
 * File:		java_lang.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/
#pragma warning(disable:4661)

#include "java_lang.h"

#include <inexum/stl/StringLableCreator.h>

using namespace inexum;
using namespace inexum::util;
using namespace inexum::stl;
using namespace java::lang;

/*-------------------------------------------------------------------------------
 *        Serialize java.lang package classes
 *-----------------------------------------------------------------------------*/
serialize_begin("java.lang.Number", java::lang::Number, "", 0x86AC951D0B94E08B)
	debug_line(DebugLine(Debug::c_serialize, "java.lang.Number{} serialized"));
serialize_end

serialize_begin("java.lang.Byte", java::lang::JavaLangType<byte>, 
					"java.lang.Number", 0x9C4E6084EE50F51C)
	serialize_by_value("B", "value", value);
	debug_line(DebugLine(Debug::c_serialize, "java.byte.Byte{%D} serialized",
					&DebugClass<Byte>(obj)));
serialize_end

serialize_begin("java.lang.Character", java::lang::JavaLangType<wchar_t>, 
					"java.lang.Number", 0x348B47D96B1A2678)
	serialize_by_value("C", "value", value);
	debug_line(DebugLine(Debug::c_serialize, "java.byte.Character{%D} serialized",
					&DebugClass<Character>(obj)));
serialize_end

serialize_begin("java.lang.Double", java::lang::JavaLangType<double>, 
					"java.lang.Number", 0x80B3C24A296BFB04)
	serialize_by_value("D", "value", value);
	debug_line(DebugLine(Debug::c_serialize, "java.byte.Double{%D} serialized",
					&DebugClass<Double>(obj)));
serialize_end

serialize_begin("java.lang.Float", java::lang::JavaLangType<float>, 
					"java.lang.Number", 0xDAEDC9A2DB3CF0EC)
	serialize_by_value("F", "value", value);
	debug_line(DebugLine(Debug::c_serialize, "java.byte.Float{%D} serialized",
					&DebugClass<Float>(obj)));
serialize_end

serialize_begin("java.lang.Integer", java::lang::JavaLangType<int>,
					"java.lang.Number", 0x12E2A0A4F7818738)
	serialize_by_value("I", "value", value);
	debug_line(DebugLine(Debug::c_serialize, "java.byte.Integer{%D} serialized",
					&DebugClass<Integer>(obj)));
serialize_end

serialize_begin("java.lang.Long", java::lang::JavaLangType<JLong>,
					"java.lang.Number", 0x3B8BE490CC8F23DF)
	serialize_by_value("J", "value", value);
	debug_line(DebugLine(Debug::c_serialize, "java.byte.Long{%D} serialized",
					&DebugClass<Long>(obj)));
serialize_end

serialize_begin("java.lang.Short", java::lang::JavaLangType<short>,
					"java.lang.Number", 0x684D37133460DA52)
	serialize_by_value("S", "value", value);
	debug_line(DebugLine(Debug::c_serialize, "java.byte.Short{%D} serialized",
					&DebugClass<Short>(obj)));
serialize_end

serialize_begin("java.lang.Boolean", java::lang::JavaLangType<bool>, "", 0xCD207280D59CFAEE)
	serialize_by_value("Z", "value", value);
	debug_line(DebugLine(Debug::c_serialize, "java.byte.Boolean{%D} serialized",
					&DebugClass<Boolean>(obj)));
serialize_end


/*-------------------------------------------------------------------------------
 *        Serialize arrays of references to java.lang package classes
 *-----------------------------------------------------------------------------*/
serialize_pointer_array("java.lang.Number",		java::lang::Number,		0x8D4686CC5CE1152C);
serialize_pointer_array("java.lang.Boolean",	java::lang::Boolean,	0x47D5250f96D2C3D1);
serialize_pointer_array("java.lang.Byte",		java::lang::Byte,		0x94106C2f84688B6E);
serialize_pointer_array("java.lang.Character",	java::lang::Character,	0x30556B9D7F899E70);
serialize_pointer_array("java.lang.Double",		java::lang::Double,		0xE112AD8900A656A6);
serialize_pointer_array("java.lang.Float",		java::lang::Float,		0x5B428953F19BAFEB);
serialize_pointer_array("java.lang.Integer",	java::lang::Integer,	0xFE97ADA00183E21B);
serialize_pointer_array("java.lang.Long",		java::lang::Long,		0x7DE10AB2BBBC632B);
serialize_pointer_array("java.lang.Short",		java::lang::Short,		0xA6BCEA37405CC749);
serialize_pointer_array("java.lang.String",		java::lang::String,		0xADD256E7E91D7B47);

#ifdef iNxmDebug
	template<> void DebugClass<Boolean>::print()
	{
		DebugClass<bool>(object().value).print(); 
	}

	template<> void DebugClass<Byte>::print()
	{
		output() << (short)object().value; 
	}

	template<> void DebugClass<Character>::print()
	{
		output() << (char)object().value; 
	}

	template<> void DebugClass<Double>::print()
	{
		char* number = new char[21];
		sprintf(number, "%20.9f", object().value);
		output() << number; 
		delete number;
	}

	template<> void DebugClass<Float>::print()
	{
		char* number = new char[13];
		sprintf(number, "%12.5f", object().value);
		output() << number; 
		delete number;
	}

	template<> void DebugClass<Integer>::print()
	{
		output() << object().value; 
	}

	template<> void DebugClass<Long>::print()
	{
		output() << object().value; 
	}

	template<> void DebugClass<Short>::print()
	{
		output() << object().value; 
	}

	template<> void DebugClass<VectorPtr<Boolean> >::print()
	{
		VectorPtr<Boolean>::const_iterator end = object().end();
		VectorPtr<Boolean>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
		{
			DebugClass<Boolean>(*(*at)).print();
			output() << ", ";
		}
		output() << "}" << endl;
	}

	template<> DebugClass<VectorPtr<Boolean> >;

	template<> void DebugClass<VectorPtr<Byte> >::print()
	{
		VectorPtr<Byte>::const_iterator end = object().end();
		VectorPtr<Byte>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
		{
			DebugClass<Byte>(*(*at)).print();
			output() << ", ";
		}
		output() << "}" << endl;
	}

	template<> DebugClass<VectorPtr<Byte> >;

	template<> void DebugClass<VectorPtr<Character> >::print()
	{
		VectorPtr<Character>::const_iterator end = object().end();
		VectorPtr<Character>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
		{
			DebugClass<Character>(*(*at)).print();
			output() << ", ";
		}
		output() << "}" << endl;
	}

	template<> DebugClass<VectorPtr<Character> >;

	template<> void DebugClass<VectorPtr<Double> >::print()
	{
		VectorPtr<Double>::const_iterator end = object().end();
		VectorPtr<Double>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
		{
			DebugClass<Double>(*(*at)).print();
			output() << ", ";
		}
		output() << "}" << endl;
	}

	template<> DebugClass<VectorPtr<Double> >;

	template<> void DebugClass<VectorPtr<Float> >::print()
	{
		VectorPtr<Float>::const_iterator end = object().end();
		VectorPtr<Float>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
		{
			DebugClass<Float>(*(*at)).print();
			output() << ", ";
		}
		output() << "}" << endl;
	}

	template<> DebugClass<VectorPtr<Float> >;

	template<> void DebugClass<VectorPtr<Integer> >::print()
	{
		VectorPtr<Integer>::const_iterator end = object().end();
		VectorPtr<Integer>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
		{
			DebugClass<Integer>(*(*at)).print();
			output() << ", ";
		}
		output() << "}" << endl;
	}

	template<> DebugClass<VectorPtr<Integer> >;

	template<> void DebugClass<VectorPtr<Long> >::print()
	{
		VectorPtr<Long>::const_iterator end = object().end();
		VectorPtr<Long>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
		{
			DebugClass<Long>(*(*at)).print();
			output() << ", ";
		}
		output() << "}" << endl;
	}

	template<> DebugClass<VectorPtr<Long> >;

	template<> void DebugClass<VectorPtr<Short> >::print()
	{
		VectorPtr<Short>::const_iterator end = object().end();
		VectorPtr<Short>::const_iterator at = object().begin();
		output() << " { ";
		for(; at != end; at++)
		{
			DebugClass<Short>(*(*at)).print();
			output() << ", ";
		}
		output() << "}" << endl;
	}

	template<> DebugClass<VectorPtr<Short> >;
#endif	// iNxmDebug
