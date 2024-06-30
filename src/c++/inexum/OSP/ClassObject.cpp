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
 * File:		ClassObject.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020615	nmv			create
 *----------------------------------------------------------------------------*/

#include "ClassObject.h"
#include <inexum/stl/Creator.h>
#include "ArrayObject.h"

#include <iostream.h>
#include <inexum/util/Debug.h>

using namespace inexum;
using namespace inexum::stl;
using namespace inexum::OSP;
using namespace inexum::util;

ClassObject::ClassObject(const ClassObject& right)
:Object(right), m_pClass(NULL)
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

template Creator<char, 'L', Object, ClassObject >;
template Creator<char, '[', Object, ArrayObject >;

#ifdef iNxmDebug
	// A debug method that dumps the Object content
	template<> void inexum::util::DebugClass<ClassObject>::print()
	{
		DebugClass<Object>(Debug::c_serialize, object()).print();
		if(object().m_pClass != NULL)
			DebugClass<Class>(Debug::c_serialize, *object().m_pClass).print();
		else
			output() << "null" << endl;
	}

		// A debug method that dumps the Object content
		template<> void util::DebugClass<OSP::ArrayObject>::print()
		{
			DebugClass<OSP::ClassObject>(object()).print();
		}
#endif	// iNxmDebug
