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
 * File:		ObjectCreators.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020615	nmv			create
 *----------------------------------------------------------------------------*/

#include <inexum/stl/Creator.h>
#include "Object.h"
#include "BuiltinObject.h"
#include "ClassObject.h"
#include "ArrayObject.h"
#include "StringObject.h"
#include <inexum/Types.h>

using namespace inexum;
using namespace inexum::stl;
using namespace inexum::OSP;

template Creator<char, 'B', Object, BuiltinObject<byte, JavaObjectParser::k_ReadByte> >;
template Creator<char, 'C', Object, BuiltinObject<char, JavaObjectParser::k_ReadChar> >;
template Creator<char, 'D', Object, BuiltinObject<double, JavaObjectParser::k_ReadDouble> >;
template Creator<char, 'F', Object, BuiltinObject<float, JavaObjectParser::k_ReadFloat> >;
template Creator<char, 'I', Object, BuiltinObject<int, JavaObjectParser::k_ReadInt> >;
template Creator<char, 'J', Object, BuiltinObject<JLong, JavaObjectParser::k_ReadLong> >;
template Creator<char, 'S', Object, BuiltinObject<short, JavaObjectParser::k_ReadShort> >;
template Creator<char, 'Z', Object, BuiltinObject<bool, JavaObjectParser::k_ReadBoolean> >;
template Creator<char, 'L', Object, ClassObject >;
template Creator<char, '[', Object, ArrayObject >;
template Creator<char, '"', Object, StringObject >;
