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
 * File:		javaObjLexer.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/
#pragma warning(disable:4786)

#include "javaObjParser.h"
#include "JavaObjectParser.h"

#include <inexum/util/Debug.h>

using namespace inexum::util;

namespace inexum
{
	namespace OSP
	{
		static int g_tokenCount = 0;

		inline UnsignedJLong get(istream& input, int charCount)
		{
			UnsignedJLong aULong = 0;
			while(charCount > 0)
			{
				byte aByte = (byte)input.get();
				aULong = aULong << 8 | aByte;
				charCount--;
			}
			return(aULong);
		}

		inline float getFloat(istream& input)
		{
			int charCount = 4;
			float aNumber = 0;
			unsigned long* pNumber = (unsigned long*)&aNumber;
			while(charCount > 0)
			{
				byte aByte = (byte)input.get();
				*pNumber = *pNumber << 8 | aByte;
				charCount--;
			}
			return(aNumber);
		}

		inline double getDouble(istream& input)
		{
			int charCount = 8;
			double aNumber = 0;
			UnsignedJLong* pNumber = (UnsignedJLong*)&aNumber;
			while(charCount > 0)
			{
				byte aByte = (byte)input.get();
				*pNumber = *pNumber << 8 | aByte;
				charCount--;
			}
			return(aNumber);
		}

		inline int convert(byte token)
		{
			const byte c_TCbegin = 0x70;
			const byte c_TCend = 0x7b;
 
			if(c_TCbegin <= token && token <= c_TCend)
			{
				return(TC_NULL + (token - c_TCbegin));
			}
			return(token);
		}

		int yylex (YYSTYPE* yylval, void* pParser)
		{
			JavaObjectParser& parser = *(JavaObjectParser*)pParser;
			
			int token = parser.insertToken();
			if(token != -1)
			{
				debug_line(DebugLine(Debug::c_serialize, "Inserted token: %d", token));
				return(token);
			}

			parser.incrementTokenCount();

			istream& input = parser.getStream();

			g_tokenCount = parser.tokenCount();

			switch(parser.state())
			{
			case JavaObjectParser::k_ReadBoolean:
				byte aBool;
				aBool = (byte)input.get();
				yylval->Boolean = aBool != '\0';
				token = BOOLEAN;

				debug_line(DebugLine(Debug::c_serialize, 
						"%d. token '%s' as %d", 
						g_tokenCount,
						hexadecimal((byte*)&aBool, 1).data(),
						parser.state()));
				break;
			case JavaObjectParser::k_ReadChar:
				yylval->Char = (char)get(input, 2);
				token = CHAR;

				debug_line(DebugLine(Debug::c_serialize, 
						"%d. token '%s' as %d", 
						g_tokenCount,
						hexadecimal((byte*)&yylval->Char, 2).data(),
						parser.state()));
				break;
			case JavaObjectParser::k_ReadByte:
				yylval->Byte = (byte)input.get();
				token = BYTE;

				debug_line(DebugLine(Debug::c_serialize, 
						"%d. token '%s' as %d", 
						g_tokenCount,
						hexadecimal((byte*)&yylval->Byte, 1).data(),
						parser.state()));
				break;
			case JavaObjectParser::k_ReadShort:
				yylval->Short = (short)get(input, 2);
				token = SHORT;

				debug_line(DebugLine(Debug::c_serialize, 
						"%d. token '%s' as %d", 
						g_tokenCount,
						hexadecimal((byte*)&yylval->Short, 2).c_str(),
						parser.state()));
				break;
			case JavaObjectParser::k_ReadInt:
				yylval->Int = (int)get(input, 4);
				token = INT;

				debug_line(DebugLine(Debug::c_serialize, 
						"%d. token '%s' as %d", 
						g_tokenCount,
						hexadecimal((byte*)&yylval->Int, 4).data(),
						parser.state()));
				break;
			case JavaObjectParser::k_ReadLong:
				yylval->Long = get(input, 8);
				token = LONG;

				debug_line(DebugLine(Debug::c_serialize, 
						"%d. token '%s' as %d", 
						g_tokenCount,
						hexadecimal((byte*)&yylval->Long, 8).data(),
						parser.state()));
				break;
			case JavaObjectParser::k_ReadFloat:
				yylval->Float = getFloat(input);
				token = FLOAT;

				debug_line(DebugLine(Debug::c_serialize, 
						"%d. token '%s' as %d", 
						g_tokenCount,
						hexadecimal((byte*)&yylval->Float, 4).data(),
						parser.state()));
				break;
			case JavaObjectParser::k_ReadDouble:
				yylval->Double = getDouble(input);
				token = DOUBLE;

				debug_line(DebugLine(Debug::c_serialize, 
						"%d. token '%s' as %d", 
						g_tokenCount,
						hexadecimal((byte*)&yylval->Double, 8).data(),
						parser.state()));
				break;
			case JavaObjectParser::k_ReadString:
				{
					int size = parser.getStringSize();
					yylval->String = new char[size + 1];
					input.get(yylval->String, size + 1);

					debug_line(DebugLine(Debug::c_serialize, 
						"%d. token '%s' as %d", 
						g_tokenCount,
						hexadecimal((byte*)&yylval->String, size, false).data(),
						parser.state()));
				}
				token = STRING;
				break;
			default:
				yylval->Byte = (byte)input.get();
				token = convert(yylval->Byte);

				debug_line(DebugLine(Debug::c_serialize, 
						"%d. token '%s' as %d", 
						g_tokenCount,
						hexadecimal((byte*)&yylval->Byte, 1).data(),
						parser.state()));
			}
			parser.state(JavaObjectParser::k_ReturnByte);
			return(token);
		}

		void yyerror(const char* msg)
		{
			debug_line(DebugLine(Debug::c_serialize, 
						"error S0012: token %d. %s", g_tokenCount, msg));
			cerr << "error S0012: token " << g_tokenCount << ". " << msg << endl;
		}
	}	// namespace OSP
}	// namespace inexum