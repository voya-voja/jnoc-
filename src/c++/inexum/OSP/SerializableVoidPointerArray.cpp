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
 * File:		SerializableVoidPointerArray.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/
#pragma warning(disable:4661)

#include "SerializableVoidPointerArray.h"

using namespace inexum::OSP;

SerializableVoidPointerArray::ObjectTypeMap SerializableVoidPointerArray::g_ObjectTypeMap;

SerializableVoidPointerArray::SerializableVoidPointerArray( const std::string& type ) 
	: SerializablePointerArray<void>( type )
{}

std::string SerializableVoidPointerArray::elementType( void* address ) const
{
	return( Serializable::CppJavaNamesRegister::javaName( 
				(*g_ObjectTypeMap.find( (unsigned)address)).second ) );
}

void SerializableVoidPointerArray::AddObjectType::insert( unsigned address, 
														 const std::string& type )
{
	g_ObjectTypeMap.insert( ObjectTypePair( address, type ) );
}