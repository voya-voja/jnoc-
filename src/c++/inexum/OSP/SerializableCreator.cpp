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
 * File:		SerializableCreator.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#include "SerializableCreator.h"
#include <inexum/definitions.h>
#include <inexum/stl/Factory.h>
#include <inexum/stl/Vector.h>
#include "Serializable.h"
#include <inexum/Types.h>
#include "SerializableCreator.h"


using namespace inexum::stl;
using namespace inexum::OSP;

namespace inexum
{
	/** Object Serializable Protocol namespace.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
	namespace OSP
	{
		class SerializableMethod : public stl::Method<std::string, Serializable>
		{
		public:
			static void RegisterMethod(const std::string& javaClassName, 
										SerializableCreator& creator)
			{
				SerializableMethodsSingleton::Instance().serializableMethods()->push_back(new SerializableMethod(javaClassName, creator));
			}

			Serializable* operator()() const { return(m_creator.create()); }

		protected:
			stl::Method<std::string, Serializable>* clone() const
			{
				return(new SerializableMethod(*this));
			}

		private:
			SerializableMethod(const std::string& javaClassName, SerializableCreator& creator)
				:stl::Method<std::string, Serializable>(javaClassName),
				m_creator(creator)
			{
			}

			SerializableMethod(const SerializableMethod& right)
				: stl::Method<std::string, Serializable>(right),
					m_creator(right.m_creator)
			{
			}

			SerializableCreator&	m_creator;

			// Provides a registry destruction
			class SerializableMethodsSingleton : public inexum::stl::Singleton<SerializableMethodsSingleton>
			{
			public:
				~SerializableMethodsSingleton();
				stl::VectorPtr<SerializableMethod>* serializableMethods();
			private:
				static stl::VectorPtr<SerializableMethod>*	g_pSerializableMethods;
			};
		};
	}	// namespace OSP
}	// namespace inexum

inexum::stl::VectorPtr<SerializableMethod>*	
		SerializableMethod::SerializableMethodsSingleton::g_pSerializableMethods = NULL;

SerializableMethod::SerializableMethodsSingleton::~SerializableMethodsSingleton()
{
	if(g_pSerializableMethods != NULL)
	{
		delete g_pSerializableMethods;
	}
}

inexum::stl::VectorPtr<SerializableMethod>* 
		SerializableMethod::SerializableMethodsSingleton::serializableMethods()
{ 
	if(g_pSerializableMethods == NULL)
	{
		g_pSerializableMethods = new inexum::stl::VectorPtr<SerializableMethod>;
	}
	return(g_pSerializableMethods); 
}


SerializableCreator::SerializableCreator(const std::string& javaClassName)
:m_javaClassName(javaClassName)
{
	SerializableMethod::RegisterMethod(javaClassName, *this);
}
