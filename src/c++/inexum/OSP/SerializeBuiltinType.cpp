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
 * File:		SerializeBuiltinType.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#include "SerializeBuiltinType.h"
#include <inexum/stl/StringLableCreator.h>
#include "SerializeString.h"

using namespace inexum;
using namespace inexum::OSP;
using namespace inexum::stl;

template class inexum::stl::CreateWithStringLable<Serializable, SerializeBuiltinType<byte> >;
CreateWithStringLable<Serializable, SerializeBuiltinType<byte> >
		CreateWithStringLable<Serializable, SerializeBuiltinType<byte> >::g_Creator("B");

template class inexum::stl::CreateWithStringLable<Serializable, SerializeBuiltinType<wchar_t> >;
CreateWithStringLable<Serializable, SerializeBuiltinType<wchar_t> >
		CreateWithStringLable<Serializable, SerializeBuiltinType<wchar_t> >::g_Creator("C");

template class inexum::stl::CreateWithStringLable<Serializable, SerializeBuiltinType<double> >;
CreateWithStringLable<Serializable, SerializeBuiltinType<double> >
		CreateWithStringLable<Serializable, SerializeBuiltinType<double> >::g_Creator("D");

template class inexum::stl::CreateWithStringLable<Serializable, SerializeBuiltinType<float> >;
CreateWithStringLable<Serializable, SerializeBuiltinType<float> >
		CreateWithStringLable<Serializable, SerializeBuiltinType<float> >::g_Creator("F");

template class inexum::stl::CreateWithStringLable<Serializable, SerializeBuiltinType<int> >;
CreateWithStringLable<Serializable, SerializeBuiltinType<int> >
		CreateWithStringLable<Serializable, SerializeBuiltinType<int> >::g_Creator("I");

template class inexum::stl::CreateWithStringLable<Serializable, SerializeBuiltinType<JLong> >;
CreateWithStringLable<Serializable, SerializeBuiltinType<JLong> >
		CreateWithStringLable<Serializable, SerializeBuiltinType<JLong> >::g_Creator("J");

template class inexum::stl::CreateWithStringLable<Serializable, SerializeBuiltinType<short> >;
CreateWithStringLable<Serializable, SerializeBuiltinType<short> >
		CreateWithStringLable<Serializable, SerializeBuiltinType<short> >::g_Creator("S");

template class inexum::stl::CreateWithStringLable<Serializable, SerializeBuiltinType<bool> >;
CreateWithStringLable<Serializable, SerializeBuiltinType<bool> >
		CreateWithStringLable<Serializable, SerializeBuiltinType<bool> >::g_Creator("Z");

template class inexum::stl::CreateWithStringLable<Serializable, SerializeString>;
CreateWithStringLable<Serializable, SerializeString>
		CreateWithStringLable<Serializable, SerializeString>::g_Creator("java.lang.String");
