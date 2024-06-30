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
 * File:		ArrayObject.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020615	nmv			create
 *----------------------------------------------------------------------------*/

#include "ArrayObject.h"
#include "BuiltinObject.h"
#include <inexum/util/Debug.h>

using namespace inexum::OSP;
using namespace inexum::util;
/*
void ArrayObject::className(const std::string& name) 
{
	debug_method(DebugMethod(Debug::c_serialize, "ArrayObject", "className", "name: %s", name.c_str()));
	size_t pos = 0;
	size_t size = name.size();
	if(name[pos] == '[')
	{
		pos++;
		size--;
	}
	if(size > 1 && PrimitiveObject::Types().find(name[0]) == std::string::npos)
	{
		ClassObject::className(std::string(name, pos, size));
	}
}
*/