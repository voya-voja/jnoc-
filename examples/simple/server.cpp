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
 * File:		server.cpp
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
#include <java/io/ObjectOutputStream.h>
#include <java/lang/java_lang.h>
#include <java/lang/Exception.h>

#include <inexum/util/Debug.h>

#undef BYTE
#undef FLOAT
#undef INT
#undef CHAR
#undef SHORT
#undef LONG
#undef BOOLEAN
#undef DOUBLE
#include <java/net/ServerSocket.h>
#include <java/net/Socket.h>

using namespace java::net;
using namespace java::io;
using namespace java::lang;
using namespace inexum;
using namespace inexum::OSP;

using namespace simple::java;


void writeBytes(ObjectOutputStream& output)
{
    byte message[] = "C++ message"; 
	output.write(message, 7);		// write the message bytes
	output.write(message, 1, 4);	// write '++ m' bytes

	write<byte>(output, 13);		// write # 13 as byte

	output.write(message);			// write a byte message

	wchar_t* message2 = (wchar_t*)"\0\62\0n\0d\0 \0m\0e\0s\0s\0a\0g\0e\0 \0f\0r\0o\0m\0 \0C\0+\0+\0";
	output.writeChars(message2);	// write a character array
}

void writeBuiltinTypes(ObjectOutputStream& output)
{
	bool aBoolean = false;
	const char* name = typeid(aBoolean).name();
	byte aByte = '\112';
	wchar_t aChar = 'C';
	double aDouble = 987654321.0123456789;
    output << aBoolean << aByte << aChar << aDouble;

	write<float>(output, float(-1234.56789));
	write<int>(output, -101);

	output << JLong(-1L);

	short* pShort = new short(12);
	writePtr<short>(output, pShort);
	delete pShort;
}

void writeBuiltinArrays(ObjectOutputStream& output)
{
	std::vector<bool> bools;
	bools.push_back(false); bools.push_back(true); bools.push_back(true);

	std::vector<byte> bytes;

	std::vector<wchar_t> chars;
	chars.push_back('c'); chars.push_back('+'); chars.push_back('+');

	std::vector<double> doubles;
	doubles.push_back(0); doubles.push_back(1.000000001);

	std::vector<float> floats;
	floats.push_back(0); floats.push_back(1.00001);

	std::vector<int> ints;
	ints.push_back(-1); ints.push_back(0x10000000); ints.push_back(0x80000000);

	std::vector<JLong> longs;
	longs.push_back(0); longs.push_back(0x8000000000000000);

	std::vector<short> shorts;
	shorts.push_back(-2); shorts.push_back(-1); shorts.push_back(0); shorts.push_back(1);

	output << bools << bytes << chars << doubles << floats;
	output << ints;
	output << longs;
	write<std::vector<short> >(output, shorts);
}

void writeObjects(ObjectOutputStream& output)
{
    Boolean boolObj(false);
	output << boolObj;

    write<Byte>(output, '\111');	// create and instance of Byte and write it

	Character* pCharObj = new Character('X');
    writePtr<Character>(output, pCharObj);
	delete pCharObj;

    Double doubleObj(1234567890.0987654321);
    Float floatObj(98765.01234);
    Integer intObj(121);
    Long longObj(1);
    Short shortObj(4);
	String aString("C++ string");

	output << doubleObj << floatObj << intObj ;
	output << longObj << shortObj << aString;

}

void writeObjectArrays(ObjectOutputStream& output)
{
	inexum::stl::VectorPtr<Boolean> bools;
	bools.push_back(new Boolean(true));

	inexum::stl::VectorPtr<Byte> bytes;
	bytes.push_back(new Byte(-1)); bytes.push_back(new Byte('0'));

	inexum::stl::VectorPtr<Character> chars;
	chars.push_back(new Character('c')); 
	chars.push_back(new Character('p')); 
	chars.push_back(new Character('p'));

	inexum::stl::VectorPtr<Double> doubles;
	doubles.push_back(new Double(-1)); 
	doubles.push_back(new Double(0)); 
	doubles.push_back(new Double(1));

	inexum::stl::VectorPtr<Float> floats;
	floats.push_back(new Float(-1)); 
	floats.push_back(new Float(0)); 
	floats.push_back(new Float(1));

	inexum::stl::VectorPtr<Integer> ints;
	ints.push_back(new Integer(-1)); 
	ints.push_back(new Integer(0)); 
	ints.push_back(new Integer(1));

	inexum::stl::VectorPtr<Long> longs;
	longs.push_back(new Long(-1)); 
	longs.push_back(new Long(0)); 
	longs.push_back(new Long(1));

	inexum::stl::VectorPtr<Short> shorts;
	shorts.push_back(new Short(-1)); 
	shorts.push_back(new Short(0)); 
	shorts.push_back(new Short(1));

	inexum::stl::VectorPtr<String> strings;
	strings.push_back(new String("Welcome")); 
	strings.push_back(new String("C++")); 
	strings.push_back(new String());


	output << bools << bytes;

	output << chars
			<< doubles;

	write<inexum::stl::VectorPtr<Float> >(output, floats);

	output << ints
			<< longs
			<< shorts
			<< strings;

}

void doServer()
{
    try
    {
        ServerSocket serverSocket(21212);
        Socket* socket = serverSocket.accept();
        ObjectOutputStream output(socket->getOutputStream()); 

        writeBytes(output);
        writeBuiltinTypes(output);
        writeBuiltinArrays(output);
        writeObjects(output);
        writeObjectArrays(output);

		Byte b((byte)0);
		Character c('M');
		Double d(0);
		Integer i(0);
		Boolean* pB = new Boolean(true);
        std::vector<void*> objectArray;
			PushBack<Number> numberLoader(objectArray);
			numberLoader(&b);
			numberLoader(&c);
			numberLoader(&d);
			numberLoader(&i);
			PushBack<Boolean> boolLoader(objectArray);
			boolLoader(pB);

        output << objectArray;
		delete pB;

        Simple aSimple(2);
        output << aSimple;

		socket->close();
		delete socket;
    }
    catch(Exception& e)
    {
		debug_line(DebugLine(Debug::c_app0, "Exception in doServer()"));
    }
	catch(...)
	{
		debug_line(DebugLine(Debug::c_app0, "Error in doServer()"));
    }
}