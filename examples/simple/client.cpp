/*******************************************************************************
*  Copyright (C) 1997 - 2002 iNexum Systems Inc.
*  All Rights Reserved
*  This Module contains Proprietary Information of iNexum Systems Inc.,
*
*  The copyright notice above does not evidence any
*  actual or intended publication of such source code.
*******************************************************************************/
/*----------------------------------------------------------------------------*
 *                                                                            *
 * File:		client.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030915	nmv			create
 *----------------------------------------------------------------------------*/
#include "Simple.h"
#include "exmplsmpl.h"

#include <string.h>
#include <inexum/Types.h>
#include <inexum/stl/Vector.h>
#include <java/io/ObjectInputStream.h>
#include <java/lang/java_lang.h>
#include <java/lang/Exception.h>

#undef BYTE
#undef FLOAT
#undef INT
#undef CHAR
#undef SHORT
#undef LONG
#undef BOOLEAN
#undef DOUBLE
#include <java/net/Socket.h>

using namespace java::net;
using namespace java::io;
using namespace java::lang;
using namespace inexum;
using namespace inexum::OSP;

using namespace simple::java;

void readBytes(ObjectInputStream& input)
{
	debug_function(DebugFunction(Debug::c_app0, "readBytes"));
    byte byteBuf[6]; 
	int size = input.read(byteBuf, 5);
	byteBuf[5] = '\0';

	int value = (int)read<byte>(input);

	byte message1[18];
	size_t bytesSize = input.read(message1, 17);
	message1[17] = '\0';

	wchar_t* message2 = (wchar_t*)input.read(bytesSize, 0, 46);
	byte* msg2Buf = (byte*)message2;
	for(int bCount = 0; bCount < 45; bCount++)
		msg2Buf[bCount] = msg2Buf[bCount + 1];
	msg2Buf[bCount] = '\0';

    debug_line(DebugLine(Debug::c_app0, "byteBuf = '%s'", byteBuf));
    debug_line(DebugLine(Debug::c_app0, "value = %d", value));
	debug_line(DebugLine(Debug::c_app0, "message1 = '%s'", message1));
	debug_line(DebugLine(Debug::c_app0, "message2 = '%S'", message2));
	delete message2;
}

void readBuiltinTypes(ObjectInputStream& input)
{
	debug_function(DebugFunction(Debug::c_app0, "readBuiltinTypes"));
	bool aBoolean;
	byte aByte;
	wchar_t aChar;
	double aDouble;
    input >> aBoolean >> aByte >> aChar >> aDouble;

	float aFloat(read<float>(input));
	int aInt = read<int>(input);

	JLong aLong;
	input >> aLong;

	short* pShort = readPtr<short>(input);

    debug_line(DebugLine(Debug::c_app0, "%D, %d, %c, %20.9f",
							&DebugClass<bool>(aBoolean), (int)aByte, aChar,
							aDouble));
    debug_line(DebugLine(Debug::c_app0, "%10.5f, %d, %D, %2d",
							aFloat, aInt, &DebugClass<inexum::JLong>(aLong), (int)*pShort));
	delete pShort;
}

void readBuiltinArrays(ObjectInputStream& input)
{
	debug_function(DebugFunction(Debug::c_app0, "readBuiltinArrays"));
	std::vector<bool> bools;
	std::vector<byte> bytes;
	std::vector<wchar_t> chars;
	std::vector<double> doubles;
	std::vector<float> floats;
	std::vector<int> ints;
	std::vector<JLong> longs;
	std::vector<short> shorts;

	input >> bools;
	input >> bytes;
	input >> chars;
	input >> doubles;
	input >> floats;
	input >> ints;
	input >> longs;
	input >> shorts;

	debug_line(DebugLine(Debug::c_app0, "bools = %D", &DebugClass<std::vector<bool> >(bools)));
	debug_line(DebugLine(Debug::c_app0, "bytes = %D", &DebugClass<std::vector<byte> >(bytes)));
	debug_line(DebugLine(Debug::c_app0, "chars = %D", &DebugClass<std::vector<wchar_t> >(chars)));
	debug_line(DebugLine(Debug::c_app0, "doubles = %D", &DebugClass<std::vector<double> >(doubles)));
	debug_line(DebugLine(Debug::c_app0, "floats = %D", &DebugClass<std::vector<float> >(floats)));
	debug_line(DebugLine(Debug::c_app0, "ints = %D", &DebugClass<std::vector<int> >(ints)));
	debug_line(DebugLine(Debug::c_app0, "longs = %D", &DebugClass<std::vector<JLong> >(longs)));
	debug_line(DebugLine(Debug::c_app0, "shorts = %D", &DebugClass<std::vector<short> >(shorts)));
}

void readObjects(ObjectInputStream& input)
{
	debug_function(DebugFunction(Debug::c_app0, "readObjects"));
    Boolean boolObj(read<Boolean>(input));

    Byte* pByteObj= readPtr<Byte>(input);

    Character charObj = read<Character>(input);
    Double doubleObj;
    Float floatObj;
    Integer intObj;
    Long longObj;
    Short shortObj;
	String aString;

	input >> doubleObj >> floatObj >> intObj ;
	input >> longObj >> shortObj >> aString;

    debug_line(DebugLine(Debug::c_app0, "%D, %D, %D, %D",
							&DebugClass<Boolean>(boolObj), 
							&DebugClass<Byte>(*pByteObj),
							&DebugClass<Character>(charObj),
							&DebugClass<Double>(doubleObj)));
    debug_line(DebugLine(Debug::c_app0, "%D, %D, %D, %D",
							&DebugClass<Float>(floatObj), 
							&DebugClass<Integer>(intObj),
							&DebugClass<Long>(longObj),
							&DebugClass<Short>(shortObj)));
    debug_line(DebugLine(Debug::c_app0, "'%s'", aString.c_str()));
	delete pByteObj;
}

void readObjectArrays(ObjectInputStream& input)
{
	debug_function(DebugFunction(Debug::c_app0, "readObjectArrays"));

	inexum::stl::VectorPtr<Boolean> bools;
	inexum::stl::VectorPtr<Byte> bytes;
	inexum::stl::VectorPtr<Character> chars;
	inexum::stl::VectorPtr<Double> doubles;
	inexum::stl::VectorPtr<Float> floats;
	inexum::stl::VectorPtr<Integer> ints;
	inexum::stl::VectorPtr<Long> longs;
	inexum::stl::VectorPtr<Short> shorts;
	inexum::stl::VectorPtr<String> strings;

	input >> bools;
	debug_line(DebugLine(Debug::c_app0, "bools = %D", &DebugClass<inexum::stl::VectorPtr<Boolean> >(bools)));
	input >> bytes;
	debug_line(DebugLine(Debug::c_app0, "bytes = %D", &DebugClass<inexum::stl::VectorPtr<Byte> >(bytes)));
	input >> chars;
	debug_line(DebugLine(Debug::c_app0, "chars = %D", &DebugClass<inexum::stl::VectorPtr<Character> >(chars)));
	input >> doubles;
	debug_line(DebugLine(Debug::c_app0, "doubles = %D", &DebugClass<inexum::stl::VectorPtr<Double> >(doubles)));
	input >> floats;
	debug_line(DebugLine(Debug::c_app0, "floats = %D", &DebugClass<inexum::stl::VectorPtr<Float> >(floats)));
	input >> ints;
	debug_line(DebugLine(Debug::c_app0, "ints = %D", &DebugClass<inexum::stl::VectorPtr<Integer> >(ints)));
	input >> longs;
	debug_line(DebugLine(Debug::c_app0, "longs = %D", &DebugClass<inexum::stl::VectorPtr<Long> >(longs)));
	input >> shorts;
	debug_line(DebugLine(Debug::c_app0, "shorts = %D", &DebugClass<inexum::stl::VectorPtr<Short> >(shorts)));
	input >> strings;
	debug_line(DebugLine(Debug::c_app0, "strings = %D", &DebugClass<inexum::stl::VectorPtr<String> >(strings)));
}

void doClient()
{
	debug_function(DebugFunction(Debug::c_app0, "doClient"));
    try
    {
		Socket socket;
		while(!socket.isConnected())
		{
			try
			{
				Yield();
				socket.connect(SocketAddress("127.0.0.1", 21211));
			}
			catch(...)
			{
				Sleep(5000);
			}
		}

        ObjectInputStream input(socket.getInputStream()); 


        readBytes(input);
        readBuiltinTypes(input);
        readBuiltinArrays(input);
        readObjects(input);
        readObjectArrays(input);

        std::vector<void*> objectArray;
		input >> objectArray;
        
        Simple* pSimple = readPtr<Simple>(input);

        debug_line(DebugLine(Debug::c_app0, "objectArray[0] = %D",
								&DebugClass<Boolean>(*(Boolean*)objectArray[0])));
        debug_line(DebugLine(Debug::c_app0, "objectArray[1] = %D",
								&DebugClass<Byte>(*(Byte*)objectArray[1])));
        debug_line(DebugLine(Debug::c_app0, "objectArray[2] = %D",
								&DebugClass<Character>(*(Character*)objectArray[2])));
        debug_line(DebugLine(Debug::c_app0, "objectArray[3] = %D",
								&DebugClass<Double>(*(Double*)objectArray[3])));
        debug_line(DebugLine(Debug::c_app0, "objectArray[4] = %D",
								&DebugClass<Integer>(*(Integer*)objectArray[4])));
        debug_line(DebugLine(Debug::c_app0, "simple = %D",
								&DebugClass<Simple>(*pSimple)));
		delete (Boolean*)objectArray[0];
		delete (Byte*)objectArray[1];
		delete (Character*)objectArray[2];
		delete (Double*)objectArray[3];
		delete (Integer*)objectArray[4];
		delete pSimple;

		socket.close();
    }
    catch(Exception e)
    {
		debug_line(DebugLine(Debug::c_app0, "Exception in doClient()"));
    }
	catch(...)
	{
		debug_line(DebugLine(Debug::c_app0, "Error in doClient()"));
    }
}

#ifdef iNxmDebug
	template<> void inexum::util::DebugClass<simple::java::Simple>::print()
	{
		output() << "[" << (void*)&object() << "]" << "{" << endl
			<< indent() << "mNo = " << object().mNo  << ";" << endl;
		output() << indent() << "mpInstance = ";
		if(object().mpInstance != NULL)
		{
			DebugClass<simple::java::Simple>(*object().mpInstance).print();
		}
		else
			output() << "[" << (void*)NULL << "]";
		output() << endl << indent() << "}" << endl;
	} 
#endif
