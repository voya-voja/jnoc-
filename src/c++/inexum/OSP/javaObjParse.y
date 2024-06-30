%{
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
 * File:		javaObjParse.y
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/
#pragma warning(disable:4786)

// disable warning '<letter>' : unrecognized character escape sequence
#pragma warning (disable : 4129)


#include "JavaObjectParser.h"
#include <inexum/Types.h>

#include "Class.h"
#include "PrimitiveValue.h"

#include <stdio.h>

using namespace inexum::util;

namespace inexum { namespace OSP {

#define PARSER			(*(JavaObjectParser*)parser)

#define __EXTERN_C__	1

#define YYPURE			1
#define YYLEX_PARAM		parser
#define YYPARSE_PARAM	parser

#ifdef YYiNexumDebug
	/** Debug yack statement. At the place of instance creation prints
	  * free fromat debug statement.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	 */
	class DebugYY : public Debug
	{
	public:
		DebugYY(FILE* errFile, const char* formatMsg, ...) 
		:Debug(Debug::c_serialize)
		{ 
			va_list argList;
			va_start(argList, formatMsg);

			print(formatMsg, argList);
			va_end(argList);
		}
	};
	#define YYFPRINTF DebugYY
	#define YYPRINT(stream, c, v) DebugYY(stream, "%c: '%d'", c, v)

	#define YYDEBUG 1

#endif	// YYiNexumDebug


%}

%union{
	bool					Boolean;
	wchar_t					Char;
	short					Short;
	int						Int;
	inexum::JLong			Long;
	float					Float;
	double					Double;
	char*					String;
	long double				LongDouble;
	byte					Byte;
	unsigned				Unsigned;
	inexum::UnsignedJLong	UnsignedLong;
	inexum::OSP::Class*		ClassPtr;
}
	
%{
#include "javaObjParser.h"
%}

%token

/* The following symbols in java.io.ObjectStreamConstants define the terminal
	and constant values expected in a stream. */
TC_NULL		/* final static byte TC_NULL = (byte)0x70; */
TC_REFERENCE	/* final static byte TC_REFERENCE = (byte)0x71; */
TC_CLASSDESC	/* final static byte TC_CLASSDESC = (byte)0x72; */
TC_OBJECT		/* final static byte TC_OBJECT = (byte)0x73; */
TC_STRING		/* final static byte TC_STRING = (byte)0x74; */
TC_ARRAY		/* final static byte TC_ARRAY = (byte)0x75; */
TC_CLASS		/* final static byte TC_CLASS = (byte)0x76; */
TC_BLOCKDATA	/* final static byte TC_BLOCKDATA = (byte)0x77; */
TC_ENDBLOCKDATA	/* final static byte TC_ENDBLOCKDATA = (byte)0x78; */
TC_RESET		/* final static byte TC_RESET = (byte)0x79; */
TC_BLOCKDATALONG	/* final static byte TC_BLOCKDATALONG = (byte)0x7A; */
TC_EXCEPTION	/* final static byte TC_EXCEPTION = (byte)0x7B; */

VALUE_END
BYTES_END
ARRAY_END
OBJECT_ANNOTATION
OBJECT_END
NOWRCLASS
WRCLASS
EXTERNAL_CONTENTS
OBJECT_ANNOTATIONS

%token <Boolean>	BOOLEAN
%token <Short>	SHORT
%token <Int>	INT
%token <Long>	LONG
%token <Byte>	BYTE
%token <String>	STRING
%token <Char>	CHAR
%token <Float>	FLOAT
%token <Double>	DOUBLE

%type <String>	utf className fieldName className1 newString
%type <Int>		size prevObject objectHandle newHandle
%type <Long>	serialVersionUID
%type <Char>	prim_typecode obj_typecode
%type <ClassPtr>	classDesc superClassDesc newClassDesc

%start startContent

%%
/*
stream:
	  magic  	{ PARSER.state(JavaObjectParser::k_ReadShort); } 
		version contents
	|
	;

magic: 
	  SHORT		{ PARSER.magic($1); } 
	;

version: 
	  SHORT	 { PARSER.version($1); } 
	;
*/

startContent: 
	  content 	{ PARSER.endTest(yystate); }
	;

contents: 
	  content
	| contents content
	;

content: 
	  object
	| blockdata
	;

object: 
	  newObject
	| newClass
	| newArray
	| newString		{ PARSER.newString($1); delete $1; }
	| newClassDesc	{ PARSER.objectNewClassDescription($1); }
	| prevObject	{ PARSER.objectReference($1); }
	| nullReference	{ PARSER.object(NULL); };
	| exception
	| reset 
	;

newClass: 
	  TC_CLASS classDesc newHandle	{ PARSER.addClass($2); }
	;

classDesc: 
	  newClassDesc	{ $$ = $1; }
	| nullReference	{ $$ = NULL; }
	| prevObject	{ $$ = PARSER.classDescReference($1); }
				/* (ClassDesc)prevObject: an object required to be of type ClassDesc */
	;

superClassDesc: 
	  classDesc		{ $$ = $1; }
	;

newClassDesc: 
	  TC_CLASSDESC 				{ PARSER.state(JavaObjectParser::k_ReadShort); } 
		className				{ PARSER.state(JavaObjectParser::k_ReadLong); } 
		serialVersionUID newHandle	{ 
								PARSER.addClassDescription($3, $5, $6);
								delete $3; 
								PARSER.state(JavaObjectParser::k_ReadByte); 
							} 
		classDescInfo 			{ $$ = PARSER.classDescriptionEnd(); } 
	;

className:
	  utf		{ $$ = $1; }
	;

serialVersionUID:	/* (long) */
	  LONG		{ $$ = $1; }	
	;

classDescInfo: 
	  classDescFlags				{ PARSER.state(JavaObjectParser::k_ReadShort); } 
		fields classAnnotation 
		superClassDesc			{ PARSER.superClass($5); }
	;

classDescFlags: /* (byte) Defined in Terminal Symbols and Constants */
			/* SC_WRITE_METHOD, SC_BLOCK_DATA, SC_SERIALIZABLE, SC_EXTERNALIZABLE */
	  BYTE	{ PARSER.classDescriptionFlags($1); }
	;

fields: /* (short)<count> fieldDesc[count] */
	  SHORT			{ PARSER.addMembers($1); }
		fieldDescs
	| SHORT			{ PARSER.addMembers($1); }
	;

fieldDescs:				/* fieldDesc[count] */
	  fieldDesc
	| fieldDescs fieldDesc
	;

fieldDesc: 
	  primitiveDesc
	| objectDesc 
	;

primitiveDesc: 
	  prim_typecode { PARSER.state(JavaObjectParser::k_ReadShort); } 
		fieldName	{ PARSER.addMember($1, $3); delete $3; }
	;

objectDesc: 
	  obj_typecode			{ PARSER.state(JavaObjectParser::k_ReadShort); } 
		fieldName className1	{ PARSER.addMember($1, $3, $4); delete $3; delete $4; }
	;

fieldName:
	  utf		{ $$ = $1; }
	;

className1:	/* (String)object: String contains field type */
	  newString			{ $$ = $1; }
	| prevObject		{ $$ = PARSER.stringReference($1); }
	;

classAnnotation: 
	  endBlockData
	| contents endBlockData /* contents written by annotateClass */
	;

prim_typecode: 
	  'B'				{ $$ = 'B'; }	/* byte */
	| 'C'				{ $$ = 'C'; } 	/* char */
	| 'D'				{ $$ = 'D'; } 	/* double */
	| 'F'				{ $$ = 'F'; }	/* float */
	| 'I'				{ $$ = 'I'; } 	/* integer */
	| 'J'				{ $$ = 'J'; } 	/* long */
	| 'S'				{ $$ = 'S'; } 	/* short */
	| 'Z'				{ $$ = 'Z'; } 	/* boolean */
	;

obj_typecode: 
	  '['				{ $$ = '['; } 	/* array */
	| 'L'				{ $$ = 'L'; } 	/* object */
	;


newArray: 
	  TC_ARRAY classDesc newHandle	{ PARSER.newArray($2, $3); PARSER.state(JavaObjectParser::k_ReadInt); }
		elementArray ARRAY_END
	;

newObject: 
	  TC_OBJECT classDesc newHandle	{ PARSER.newObject($2, $3); }
		classdataList OBJECT_END
	;

classdataList: 
						/* no members */
	| nowrclassList			/* SC_SERIALIZABLE & classDescFlag && !(SC_WRITE_METHOD & classDescFlags) */
	| wrclassList 			/* SC_SERIALIZABLE & classDescFlag && SC_WRITE_METHOD & classDescFlags */
	| externalContentList		/* SC_EXTERNALIZABLE & classDescFlag && !(SC_BLOCKDATA & classDescFlags */
	| objectAnnotationList		/* SC_EXTERNALIZABLE & classDescFlag && SC_BLOCKDATA & classDescFlags */
	;

nowrclassList:
	  NOWRCLASS values
	| NOWRCLASS 
	;

wrclassList:
	  WRCLASS wrclasses
	;

wrclasses:
	  wrclass
	| wrclasses wrclass
	;

wrclass: 
	  value objectAnnotation
	;

externalContentList:
	  EXTERNAL_CONTENTS externalContents
	;

externalContents:	// externalContent written by writeExternal in PROTOCOL_VERSION_1. //
	  externalContent
	| externalContents externalContent
	;

externalContent:	// Only parseable by readExternal primitive data //
	  bytes	// (bytes)object //
	;

objectAnnotationList:
	  OBJECT_ANNOTATIONS objectAnnotations
	;

objectAnnotations:
	  objectAnnotation
	| objectAnnotations objectAnnotation
	;

objectAnnotation: /* contents written by writeObject or writeExternal PROTOCOL_VERSION_2. */
	  endBlockData
	| contents endBlockData
	; 

blockdata: 
	  blockdatashort
	| blockdatalong 
	;

blockdatashort: 
	  TC_BLOCKDATA	{ PARSER.state(JavaObjectParser::k_ReadByte); } 
		size		{ PARSER.newBlockData($3);
						PARSER.state(JavaObjectParser::k_ReadByte); }
		bytes 
	;

size:
	  BYTE  	{ $$ = $1; } /* (unsigned byte)<size> */ 
	| INT		{ $$ = $1; } /* (int)<size> */
	;

utf:	/* (utf) */ 
	  SHORT 	{ PARSER.readString($1); } 	
		STRING	{ $$ = $3; }
	;
	  
bytes:	/* (byte)[size] */
	  BYTES_END			
	| BYTE 			{ PARSER.state(JavaObjectParser::k_ReadByte);  
		 				 PARSER.addByte($1); }
		bytes
	;

blockdatalong: 
	  TC_BLOCKDATALONG	{ PARSER.state(JavaObjectParser::k_ReadInt); } 
		size bytes 
	;

endBlockData: 
	  TC_ENDBLOCKDATA
	;

newString: 
	  TC_STRING newHandle 	{ PARSER.state(JavaObjectParser::k_ReadShort); }
		utf 				{ PARSER.newString($4, $2); $$ = $4; }
	;

prevObject: 
	  TC_REFERENCE 		{ PARSER.state(JavaObjectParser::k_ReadInt); } 
		objectHandle	{ $$ = $3; }
	;

objectHandle:	/* (int)handle */
	  INT		{ $$ = $1; }
	;

nullReference: 
	  TC_NULL
	;

exception: /* (Throwable)object */
	  TC_EXCEPTION reset object reset 
	;

elementArray: /* (int)<size> value[size] */
	  INT			{ PARSER.elementArrayStart($1); }
		elements
	;

elements:
				/* no elements */
	| values
	;

values:	/* The size and types are described by the classDesc for the  current object */
	  value			{ PARSER.valueEnd(); } 
		VALUE_END	{ PARSER.valueStart(); }
	| values
		value		{ PARSER.valueEnd(); } 
		VALUE_END	{ PARSER.valueStart(); }
	;

value:
	  BOOLEAN	{ PARSER.add(new PrimitiveValue<bool>($1)); }
	| CHAR		{ PARSER.add(new PrimitiveValue<char>($1)); }
	| BYTE		{ PARSER.add(new PrimitiveValue<byte>($1)); }
	| SHORT		{ PARSER.add(new PrimitiveValue<short>($1)); }
	| INT		{ PARSER.add(new PrimitiveValue<int>($1)); }
	| LONG		{ PARSER.add(new PrimitiveValue<JLong>($1)); }
	| FLOAT		{ PARSER.add(new PrimitiveValue<float>($1)); }
	| DOUBLE	{ PARSER.add(new PrimitiveValue<double>($1)); }
	| object
	; 

newHandle:	/* The next number in sequence is assigned
				to the object being serialized or deserialized  */
	  		{ $$ = PARSER.newHandle(); }
	;

reset:	/* The set of known objects is discarded so the objects of the 
			exception do not overlap with the previously sent objects or
            with objects that may be sent after the exception */
	  TC_RESET { PARSER.reset(); }
	;
%%

		int JavaObjectParser::finalState()
		{
			return(YYFINAL);
		}

	}	// namespace OSP
}	// namespace inexum