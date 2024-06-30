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
 * File:		ClassObject.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020615	nmv			create
 *----------------------------------------------------------------------------*/

#include "ClassObject.h"

#include <iostream.h>
#include <inexum/util/Debug.h>

using namespace inexum::OSP;
using namespace inexum::util;

ClassObject::ClassObject(const ClassObject& right)
:Object(right), m_pClass(NULL), m_className(right.m_className)
{
	debug_method(DebugMethod(Debug::c_serialize, "ClassObject", "ClassObject", 
				"right: %D", &DebugClass<ClassObject>(right)));
	if(right.m_pClass != NULL)
		m_pClass = right.m_pClass->clone();
}

ClassObject::~ClassObject()
{
	debug_method(DebugMethod(Debug::c_serialize, "ClassObject", "~ClassObject"));
	if(m_pClass != NULL)
		delete m_pClass;
}
/*
// parse class name
void ClassObject::className(const std::string& name) 
{
	debug_method(DebugMethod(Debug::c_serialize, "ClassObject", "className", "name: %s", name.c_str()));
	size_t pos = 0;
	size_t size = name.size();
	if(name[ size - 1 ] == ';') // remove ; at the end
		size--;
	if(name[pos] == 'L') // remove L at the begining
	{
		pos++;
		size--;
	}
	m_className.assign(name, pos, size);
}
*/