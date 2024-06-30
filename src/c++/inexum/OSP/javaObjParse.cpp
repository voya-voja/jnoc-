/* A Bison parser, made from C:\Documents and Settings\nvojinov.TSE\My Documents\working\jnoc++\src\c++\inexum\OSP\javaObjParse.y
   by GNU bison 1.35.  */

#include "inexum/definitions.h"
// disable warning 'argument': conversion from 'wchar_t' to '...', possible loss of data
#pragma warning (disable : 4244)


#define YYBISON 1  /* Identify Bison output.  */

# define	TC_NULL	257
# define	TC_REFERENCE	258
# define	TC_CLASSDESC	259
# define	TC_OBJECT	260
# define	TC_STRING	261
# define	TC_ARRAY	262
# define	TC_CLASS	263
# define	TC_BLOCKDATA	264
# define	TC_ENDBLOCKDATA	265
# define	TC_RESET	266
# define	TC_BLOCKDATALONG	267
# define	TC_EXCEPTION	268
# define	VALUE_END	269
# define	BYTES_END	270
# define	ARRAY_END	271
# define	OBJECT_ANNOTATION	272
# define	OBJECT_END	273
# define	NOWRCLASS	274
# define	WRCLASS	275
# define	EXTERNAL_CONTENTS	276
# define	OBJECT_ANNOTATIONS	277
# define	BOOLEAN	278
# define	SHORT	279
# define	INT	280
# define	LONG	281
# define	BYTE	282
# define	STRING	283
# define	CHAR	284
# define	FLOAT	285
# define	DOUBLE	286

#line 1 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"

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



#line 76 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
#ifndef YYSTYPE
typedef union{
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
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#line 92 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"

#include "javaObjParser.h"
#ifndef YYDEBUG
# define YYDEBUG 1
#endif



#define	YYFINAL		160
#define	YYFLAG		-32768
#define	YYNTBASE	43

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 286 ? yytranslate[x] : 115)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    33,    34,    35,     2,
      36,     2,     2,    37,    38,     2,    42,     2,     2,     2,
       2,     2,     2,    39,     2,     2,     2,     2,     2,     2,
      40,    41,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     4,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    33,    35,    37,    39,
      41,    42,    43,    44,    53,    55,    57,    58,    64,    66,
      67,    71,    73,    75,    78,    80,    82,    83,    87,    88,
      93,    95,    97,    99,   101,   104,   106,   108,   110,   112,
     114,   116,   118,   120,   122,   124,   125,   132,   133,   140,
     141,   143,   145,   147,   149,   152,   154,   157,   159,   162,
     165,   168,   170,   173,   175,   178,   180,   183,   185,   188,
     190,   192,   193,   194,   200,   202,   204,   205,   209,   211,
     212,   216,   217,   222,   224,   225,   230,   231,   235,   237,
     239,   244,   245,   249,   250,   252,   253,   257,   258,   263,
     265,   267,   269,   271,   273,   275,   277,   279,   281,   282
};
static const short yyrhs[] =
{
      45,     0,    45,     0,    44,    45,     0,    46,     0,    87,
       0,    74,     0,    47,     0,    72,     0,    99,     0,    50,
       0,   101,     0,   104,     0,   105,     0,   114,     0,     9,
      48,   113,     0,    50,     0,   104,     0,   101,     0,    48,
       0,     0,     0,     0,     5,    51,    54,    52,    55,   113,
      53,    56,     0,    92,     0,    27,     0,     0,    58,    57,
      59,    69,    49,     0,    28,     0,     0,    25,    60,    61,
       0,    25,     0,    62,     0,    61,    62,     0,    63,     0,
      65,     0,     0,    70,    64,    67,     0,     0,    71,    66,
      67,    68,     0,    92,     0,    99,     0,   101,     0,    98,
       0,    44,    98,     0,    33,     0,    34,     0,    35,     0,
      36,     0,    37,     0,    38,     0,    39,     0,    40,     0,
      41,     0,    42,     0,     0,     8,    48,   113,    73,   106,
      17,     0,     0,     6,    48,   113,    75,    76,    19,     0,
       0,    77,     0,    78,     0,    81,     0,    84,     0,    20,
     109,     0,    20,     0,    21,    79,     0,    80,     0,    79,
      80,     0,   112,    86,     0,    22,    82,     0,    83,     0,
      82,    83,     0,    94,     0,    23,    85,     0,    86,     0,
      85,    86,     0,    98,     0,    44,    98,     0,    88,     0,
      96,     0,     0,     0,    10,    89,    91,    90,    94,     0,
      28,     0,    26,     0,     0,    25,    93,    29,     0,    16,
       0,     0,    28,    95,    94,     0,     0,    13,    97,    91,
      94,     0,    11,     0,     0,     7,   113,   100,    92,     0,
       0,     4,   102,   103,     0,    26,     0,     3,     0,    14,
     114,    46,   114,     0,     0,    26,   107,   108,     0,     0,
     109,     0,     0,   112,   110,    15,     0,     0,   109,   112,
     111,    15,     0,    24,     0,    30,     0,    28,     0,    25,
       0,    26,     0,    27,     0,    31,     0,    32,     0,    46,
       0,     0,    12,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   158,   162,   164,   167,   169,   172,   174,   175,   176,
     177,   178,   179,   180,   181,   184,   188,   190,   191,   195,
     199,   199,   199,   199,   210,   214,   218,   218,   224,   229,
     229,   232,   235,   237,   240,   242,   245,   245,   250,   250,
     255,   259,   261,   264,   266,   269,   271,   272,   273,   274,
     275,   276,   277,   280,   282,   286,   286,   291,   291,   296,
     298,   299,   300,   301,   304,   306,   309,   313,   315,   318,
     322,   326,   328,   331,   335,   339,   341,   344,   346,   349,
     351,   354,   354,   354,   361,   363,   366,   366,   371,   373,
     373,   378,   378,   383,   387,   387,   392,   392,   397,   401,
     405,   409,   409,   414,   416,   419,   419,   422,   422,   427,
     429,   430,   431,   432,   433,   434,   435,   436,   439,   444
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "TC_NULL", "TC_REFERENCE", "TC_CLASSDESC", 
  "TC_OBJECT", "TC_STRING", "TC_ARRAY", "TC_CLASS", "TC_BLOCKDATA", 
  "TC_ENDBLOCKDATA", "TC_RESET", "TC_BLOCKDATALONG", "TC_EXCEPTION", 
  "VALUE_END", "BYTES_END", "ARRAY_END", "OBJECT_ANNOTATION", 
  "OBJECT_END", "NOWRCLASS", "WRCLASS", "EXTERNAL_CONTENTS", 
  "OBJECT_ANNOTATIONS", "BOOLEAN", "SHORT", "INT", "LONG", "BYTE", 
  "STRING", "CHAR", "FLOAT", "DOUBLE", "'B'", "'C'", "'D'", "'F'", "'I'", 
  "'J'", "'S'", "'Z'", "'['", "'L'", "startContent", "contents", 
  "content", "object", "newClass", "classDesc", "superClassDesc", 
  "newClassDesc", "@1", "@2", "@3", "className", "serialVersionUID", 
  "classDescInfo", "@4", "classDescFlags", "fields", "@5", "fieldDescs", 
  "fieldDesc", "primitiveDesc", "@6", "objectDesc", "@7", "fieldName", 
  "className1", "classAnnotation", "prim_typecode", "obj_typecode", 
  "newArray", "@8", "newObject", "@9", "classdataList", "nowrclassList", 
  "wrclassList", "wrclasses", "wrclass", "externalContentList", 
  "externalContents", "externalContent", "objectAnnotationList", 
  "objectAnnotations", "objectAnnotation", "blockdata", "blockdatashort", 
  "@10", "@11", "size", "utf", "@12", "bytes", "@13", "blockdatalong", 
  "@14", "endBlockData", "newString", "@15", "prevObject", "@16", 
  "objectHandle", "nullReference", "exception", "elementArray", "@17", 
  "elements", "values", "@18", "@19", "value", "newHandle", "reset", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    43,    44,    44,    45,    45,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    47,    48,    48,    48,    49,
      51,    52,    53,    50,    54,    55,    57,    56,    58,    60,
      59,    59,    61,    61,    62,    62,    64,    63,    66,    65,
      67,    68,    68,    69,    69,    70,    70,    70,    70,    70,
      70,    70,    70,    71,    71,    73,    72,    75,    74,    76,
      76,    76,    76,    76,    77,    77,    78,    79,    79,    80,
      81,    82,    82,    83,    84,    85,    85,    86,    86,    87,
      87,    89,    90,    88,    91,    91,    93,    92,    94,    95,
      94,    97,    96,    98,   100,    99,   102,   101,   103,   104,
     105,   107,   106,   108,   108,   110,   109,   111,   109,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   113,   114
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       0,     0,     0,     8,     1,     1,     0,     5,     1,     0,
       3,     1,     1,     2,     1,     1,     0,     3,     0,     4,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     6,     0,
       1,     1,     1,     1,     2,     1,     2,     1,     2,     2,
       2,     1,     2,     1,     2,     1,     2,     1,     2,     1,
       1,     0,     0,     5,     1,     1,     0,     3,     1,     0,
       3,     0,     4,     1,     0,     4,     0,     3,     1,     1,
       4,     0,     3,     0,     1,     0,     3,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,    99,    96,    20,     0,   118,     0,     0,    81,   119,
      91,     0,     1,     4,     7,    10,     8,     6,     5,    79,
      80,     9,    11,    12,    13,    14,     0,     0,   118,    16,
      18,    17,    94,   118,   118,     0,     0,     0,    98,    97,
      86,    21,    24,    57,     0,    55,    15,    85,    84,    82,
       0,     0,     0,     0,    59,    95,     0,     0,    88,    89,
      92,   100,    87,    25,   118,    65,     0,     0,     0,     0,
      60,    61,    62,    63,   101,     0,    83,     0,    22,   109,
     112,   113,   114,   111,   110,   115,   116,   117,    64,   105,
      66,    67,     0,    70,    71,    73,    93,     0,     2,    74,
      75,    77,    58,   103,    56,    90,     0,   107,     0,    68,
      69,    72,     3,    78,    76,   102,   104,    28,    23,    26,
       0,   106,     0,   108,    31,     0,     0,     0,     0,    43,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      30,    32,    34,    35,    36,    38,    44,    19,    27,    33,
       0,     0,    37,    40,     0,    39,    41,    42,     0,     0,
       0
};

static const short yydefgoto[] =
{
     158,    97,    98,    13,    14,    28,   148,    15,    27,    53,
     106,    41,    64,   118,   122,   119,   125,   126,   140,   141,
     142,   150,   143,   151,   152,   155,   128,   144,   145,    16,
      56,    17,    54,    69,    70,    71,    90,    91,    72,    93,
      94,    73,    99,   100,    18,    19,    35,    57,    49,   153,
      52,    95,    77,    20,    36,   101,    21,    44,    22,    26,
      39,    23,    24,    75,   103,   115,    88,   108,   120,    89,
      32,    25
};

static const short yypact[] =
{
     108,-32768,-32768,-32768,    27,-32768,    27,    27,-32768,-32768,
  -32768,    12,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,    22,     3,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,    21,    21,   132,-32768,-32768,
  -32768,-32768,-32768,-32768,     3,-32768,-32768,-32768,-32768,-32768,
       5,    12,     9,    25,    20,-32768,    28,     5,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,    63,    63,     5,    96,     8,
  -32768,-32768,-32768,-32768,-32768,    36,-32768,     5,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    63,-32768,
      63,-32768,    96,     5,-32768,-32768,-32768,    96,-32768,    96,
  -32768,-32768,-32768,    63,-32768,-32768,    29,-32768,    40,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,    63,-32768,-32768,-32768,
      41,-32768,    34,-32768,   118,    96,   128,    96,    27,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
     128,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
       3,     3,-32768,-32768,    19,-32768,-32768,-32768,    61,    62,
  -32768
};

static const short yypgoto[] =
{
  -32768,   -62,     1,   -30,-32768,    -2,-32768,     2,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   -76,
  -32768,-32768,-32768,-32768,   -77,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,   -12,-32768,-32768,
     -17,-32768,-32768,   -70,-32768,-32768,-32768,-32768,    43,   -10,
  -32768,   -32,-32768,-32768,-32768,   -81,   -74,-32768,    -4,-32768,
  -32768,     6,-32768,-32768,-32768,-32768,   -22,-32768,-32768,   -51,
     -14,     0
};


#define	YYLAST		170


static const short yytable[] =
{
      30,    12,    30,    30,    33,    34,    29,    51,    29,    29,
      31,    37,    31,    31,    43,    92,   113,    42,    60,    45,
      46,    58,   110,     2,     9,    76,     5,   102,    40,   114,
       1,     2,     3,    59,    55,    87,    87,   107,    62,    92,
      65,    66,    67,    68,   129,   105,   146,    47,    38,    48,
      78,    61,    63,   104,    74,   121,   123,   117,    87,   124,
      87,   159,   160,   127,   149,   107,     1,     2,     3,     4,
       5,     6,     7,    87,   154,     9,   111,    11,   109,    50,
     156,   116,     0,     0,     0,     0,    87,    79,    80,    81,
      82,    83,     0,    84,    85,    86,     0,     0,   112,     1,
       2,     3,     4,     5,     6,     7,     8,    96,     9,    10,
      11,     1,     2,     3,     4,     5,     6,     7,     8,     0,
       9,    10,    11,     0,    30,     0,   147,     0,   112,     0,
      29,     0,     0,     0,    31,     1,     2,     3,     4,     5,
       6,     7,     0,     0,     9,     0,    11,     0,     0,     0,
     157,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
     -29,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139
};

static const short yycheck[] =
{
       4,     0,     6,     7,     6,     7,     4,    37,     6,     7,
       4,    11,     6,     7,    28,    66,    97,    27,    50,    33,
      34,    16,    92,     4,    12,    57,     7,    19,    25,    99,
       3,     4,     5,    28,    44,    65,    66,    88,    29,    90,
      20,    21,    22,    23,   125,    77,   127,    26,    26,    28,
      64,    51,    27,    17,    26,    15,    15,    28,    88,    25,
      90,     0,     0,   125,   140,   116,     3,     4,     5,     6,
       7,     8,     9,   103,   151,    12,    93,    14,    90,    36,
     154,   103,    -1,    -1,    -1,    -1,   116,    24,    25,    26,
      27,    28,    -1,    30,    31,    32,    -1,    -1,    97,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      12,    13,    14,    -1,   128,    -1,   128,    -1,   127,    -1,
     128,    -1,    -1,    -1,   128,     3,     4,     5,     6,     7,
       8,     9,    -1,    -1,    12,    -1,    14,    -1,    -1,    -1,
     154,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\bison-1.35\\bin\\bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\bison-1.35\\bin\\bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 159 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.endTest(yystate); ;
    break;}
case 9:
#line 176 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.newString(yyvsp[0].String); delete yyvsp[0].String; ;
    break;}
case 10:
#line 177 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.objectNewClassDescription(yyvsp[0].ClassPtr); ;
    break;}
case 11:
#line 178 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.objectReference(yyvsp[0].Int); ;
    break;}
case 12:
#line 179 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.object(NULL); ;
    break;}
case 15:
#line 185 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.addClass(yyvsp[-1].ClassPtr); ;
    break;}
case 16:
#line 189 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.ClassPtr = yyvsp[0].ClassPtr; ;
    break;}
case 17:
#line 190 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.ClassPtr = NULL; ;
    break;}
case 18:
#line 191 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.ClassPtr = PARSER.classDescReference(yyvsp[0].Int); ;
    break;}
case 19:
#line 196 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.ClassPtr = yyvsp[0].ClassPtr; ;
    break;}
case 20:
#line 200 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.state(JavaObjectParser::k_ReadShort); ;
    break;}
case 21:
#line 201 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.state(JavaObjectParser::k_ReadLong); ;
    break;}
case 22:
#line 202 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ 
								PARSER.addClassDescription(yyvsp[-3].String, yyvsp[-1].Long, yyvsp[0].Int);
								delete yyvsp[-3].String; 
								PARSER.state(JavaObjectParser::k_ReadByte); 
							;
    break;}
case 23:
#line 207 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.ClassPtr = PARSER.classDescriptionEnd(); ;
    break;}
case 24:
#line 211 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.String = yyvsp[0].String; ;
    break;}
case 25:
#line 215 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Long = yyvsp[0].Long; ;
    break;}
case 26:
#line 219 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.state(JavaObjectParser::k_ReadShort); ;
    break;}
case 27:
#line 221 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.superClass(yyvsp[0].ClassPtr); ;
    break;}
case 28:
#line 226 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.classDescriptionFlags(yyvsp[0].Byte); ;
    break;}
case 29:
#line 230 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.addMembers(yyvsp[0].Short); ;
    break;}
case 31:
#line 232 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.addMembers(yyvsp[0].Short); ;
    break;}
case 36:
#line 246 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.state(JavaObjectParser::k_ReadShort); ;
    break;}
case 37:
#line 247 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.addMember(yyvsp[-2].Char, yyvsp[0].String); delete yyvsp[0].String; ;
    break;}
case 38:
#line 251 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.state(JavaObjectParser::k_ReadShort); ;
    break;}
case 39:
#line 252 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.addMember(yyvsp[-3].Char, yyvsp[-1].String, yyvsp[0].String); delete yyvsp[-1].String; delete yyvsp[0].String; ;
    break;}
case 40:
#line 256 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.String = yyvsp[0].String; ;
    break;}
case 41:
#line 260 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.String = yyvsp[0].String; ;
    break;}
case 42:
#line 261 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.String = PARSER.stringReference(yyvsp[0].Int); ;
    break;}
case 45:
#line 270 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Char = 'B'; ;
    break;}
case 46:
#line 271 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Char = 'C'; ;
    break;}
case 47:
#line 272 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Char = 'D'; ;
    break;}
case 48:
#line 273 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Char = 'F'; ;
    break;}
case 49:
#line 274 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Char = 'I'; ;
    break;}
case 50:
#line 275 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Char = 'J'; ;
    break;}
case 51:
#line 276 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Char = 'S'; ;
    break;}
case 52:
#line 277 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Char = 'Z'; ;
    break;}
case 53:
#line 281 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Char = '['; ;
    break;}
case 54:
#line 282 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Char = 'L'; ;
    break;}
case 55:
#line 287 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.newArray(yyvsp[-1].ClassPtr, yyvsp[0].Int); PARSER.state(JavaObjectParser::k_ReadInt); ;
    break;}
case 57:
#line 292 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.newObject(yyvsp[-1].ClassPtr, yyvsp[0].Int); ;
    break;}
case 81:
#line 355 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.state(JavaObjectParser::k_ReadByte); ;
    break;}
case 82:
#line 356 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.newBlockData(yyvsp[0].Int);
						PARSER.state(JavaObjectParser::k_ReadByte); ;
    break;}
case 84:
#line 362 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Int = yyvsp[0].Byte; ;
    break;}
case 85:
#line 363 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Int = yyvsp[0].Int; ;
    break;}
case 86:
#line 367 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.readString(yyvsp[0].Short); ;
    break;}
case 87:
#line 368 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.String = yyvsp[0].String; ;
    break;}
case 89:
#line 373 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.state(JavaObjectParser::k_ReadByte);  
		 				 PARSER.addByte(yyvsp[0].Byte); ;
    break;}
case 91:
#line 379 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.state(JavaObjectParser::k_ReadInt); ;
    break;}
case 94:
#line 388 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.state(JavaObjectParser::k_ReadShort); ;
    break;}
case 95:
#line 389 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.newString(yyvsp[0].String, yyvsp[-2].Int); yyval.String = yyvsp[0].String; ;
    break;}
case 96:
#line 393 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.state(JavaObjectParser::k_ReadInt); ;
    break;}
case 97:
#line 394 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Int = yyvsp[0].Int; ;
    break;}
case 98:
#line 398 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Int = yyvsp[0].Int; ;
    break;}
case 101:
#line 410 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.elementArrayStart(yyvsp[0].Int); ;
    break;}
case 105:
#line 420 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.valueEnd(); ;
    break;}
case 106:
#line 421 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.valueStart(); ;
    break;}
case 107:
#line 423 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.valueEnd(); ;
    break;}
case 108:
#line 424 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.valueStart(); ;
    break;}
case 109:
#line 428 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.add(new PrimitiveValue<bool>(yyvsp[0].Boolean)); ;
    break;}
case 110:
#line 429 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.add(new PrimitiveValue<char>(yyvsp[0].Char)); ;
    break;}
case 111:
#line 430 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.add(new PrimitiveValue<byte>(yyvsp[0].Byte)); ;
    break;}
case 112:
#line 431 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.add(new PrimitiveValue<short>(yyvsp[0].Short)); ;
    break;}
case 113:
#line 432 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.add(new PrimitiveValue<int>(yyvsp[0].Int)); ;
    break;}
case 114:
#line 433 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.add(new PrimitiveValue<JLong>(yyvsp[0].Long)); ;
    break;}
case 115:
#line 434 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.add(new PrimitiveValue<float>(yyvsp[0].Float)); ;
    break;}
case 116:
#line 435 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.add(new PrimitiveValue<double>(yyvsp[0].Double)); ;
    break;}
case 118:
#line 441 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ yyval.Int = PARSER.newHandle(); ;
    break;}
case 119:
#line 447 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"
{ PARSER.reset(); ;
    break;}
}

#line 705 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\bison-1.35\\bin\\bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 449 "C:\\Documents and Settings\\nvojinov.TSE\\My Documents\\working\\jnoc++\\src\\c++\\inexum\\OSP\\javaObjParse.y"


		int JavaObjectParser::finalState()
		{
			return(YYFINAL);
		}

	}	// namespace OSP
}	// namespace inexum