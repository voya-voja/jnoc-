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
 * File:		Serialize.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef iNexum_Seralize_h
#define iNexum_Seralize_h

#include "Serializable.h"
#include "Class.h"
#include "JavaObjectSerializer.h"
#include "Member.h"
#include <inexum/Types.h>
#include <inexum/stl/Map.h>

/** iNexum classes.
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
namespace inexum
{
	/** Object Serializable Protocol namespace.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
	namespace OSP
	{
		class JavaObjectSerializer;
		class Member;

		/** Specialization of Serializable class that provides means to define
		  * a C++ class a serializable.
		  *
		  * @see	serialize
		  * @see	serialize_begin
		  * @see	serialize_by_value
		  * @see	serialize_pointer
		  * @see	serialize_end
		  *
		  * @param TYPE - A C++ serializable class .
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template<class TYPE>
		class Serialize : public Serializable
		{
		public:
			/** Default constructor. Creates a new instance of class TYPE and loads 
			  *the members map.
			  */
			Serialize(const std::string& className) : Serializable(className) {}

			~Serialize() 
			{
			};

			/** Provide the address of a specified member .
			  *
			  * @param name - the member name.
			  * @return void pointer address of the specified member.
			  */
			void* addressOf(const std::string& name) { return(m_members.find(name)->second); }

			JLong serialVersionUID() const;

		protected:
			/// The map of member names to member pointers
			typedef inexum::stl::MapPtr<std::string, Member>	MembersMap;

			/// The map's pair of member name and member pointer
			typedef MembersMap::value_type			MemberPair;

			/// The list of member names
			typedef std::vector<std::string>		MembersList;

			/** Provide the members map for the serializable object.
			  * 
			  * @return the map of members.
			  */
			MembersMap& members() { return(m_members); }

			/** Add a member of the C++ serializable object to the list of 
			  * serializables.
			  *
			  * @param name - a member name.
			  * @param pObject - a member pointer.
			  */
			void addMember(const char* name, Member* pMember);

			/** Instantiate an object of serializable class TYPE.
			  * 
			  * @return the void pointer address of a serializable object.
			  */
			void* instantiateObject()
			{
				return((void*)new TYPE);
			}

			/** Load the object's map of members. The method body is not provided.
			  * It is expected that any instantiation of the class would provide
			  * specific implementation of this method.
			  */
			void load(TYPE& obj);

			/** Initialize a serializable object of type TYPE.
			  * 
			  * @param pObject - the address of an object to be initialized.
			  * @param aClass - the class description corresponding to the object.
			  */	
			void initializeObject(void* pObject, const Class& aClass);

			/** Serialize the C++ serializable object of type TYPE using the
			  * provided Java object serializer.
			  *
			  * @param address - the object address 
			  *	@param serializer - Java object serializer.
			  */
			void serialize(const void* address, JavaObjectSerializer& serializer);

			/** The setter of super class name (Java class name format).
			  *
			  * @param name - the super class name 
			  */
			void superClass(const std::string& name) { m_superClassName = name; }

		private:
			/// The super class name of the serializable object
			std::string m_superClassName;

			/// The map of members of C++ serializable object
			MembersMap	m_members;

			MembersList	m_membersList;
		};

		template<class TYPE>
		void Serialize<TYPE>::addMember(const char* name, Member* pMember)
		{
			debug_method(inexum::util::DebugMethod(
						inexum::util::Debug::c_serialize, "Serialize<>", "addMember", 
						"name: '%s', class: '%d'", name, (void*)pMember));
			if(pMember->isBasicType())
				m_membersList.insert(m_membersList.begin(), name);
			else
				m_membersList.push_back(name);
			m_members.insert(MemberPair(name, pMember));
		}

		template<class TYPE>
		void Serialize<TYPE>::initializeObject(void* pObject, const Class& aClass)
		{
			debug_method(inexum::util::DebugMethod(
						inexum::util::Debug::c_serialize, "Serialize<>", "initializeObject", 
						"address: '%d', class: '%s'", pObject, aClass.name().c_str()));
			load(*(TYPE*)pObject);
			Class::const_MemberIterator end = aClass.memberEnd();
			for(Class::const_MemberIterator at = aClass.memberBegin(); at != end; at++)
			{
				std::string name = (*at)->name();
				try
				{
					Member* pMember = m_members[ (*at)->name() ];
					pMember->initialize(*(*at), aClass.name());
				}
				catch(...)
				{
					debug_line(inexum::util::DebugLine(
						inexum::util::Debug::c_serialize, 
						"error S0010: Member '%s' is not serializable!", 
															aClass.name().data()));
					cerr << "error S0001: Member '" << aClass.name().data() << "." 
											<< name.data() << "' is not serializable!" <<endl;
				}
			}
		}

		template<class TYPE>
		void Serialize<TYPE>::serialize(const void* address, JavaObjectSerializer& serializer)
		{
			debug_method(inexum::util::DebugMethod(
						inexum::util::Debug::c_serialize, "Serialize<>", "serialize", 
						"address: '%d%'", address));
			if(!isSuperClass())
			{
				byte objectTC = objectTypeCode();
				serializer.writeReverse((const byte*)&objectTC, sizeof(objectTC));
			}

			if(serializer.referenced(address)) 
				return;

			TYPE& obj = *(TYPE*)address;
			obj.m_SerialObjectHandler.setObject(address, serializer);
			load(obj);

			std::string name = className();

			if(!serializer.referenced(name))
			{
				serializer.writeClassDescription(name, m_members.size(), serialVersionUID());

				MembersList::iterator end = m_membersList.end();
				for(MembersList::iterator at = m_membersList.begin(); at != end; at++)
				{
					const std::string& name = *at;
					m_members.find(name)->second->description(serializer);
				}
				serializer.writeClassDescriptionEnd(address, m_superClassName);
			}
			else
			{
				serializer.newHandle((unsigned)address);
			}

			MembersList::iterator end = m_membersList.end();
			for(MembersList::iterator at = m_membersList.begin(); at != end; at++)
			{
				const std::string& name = *at;
				m_members.find(name)->second->serialize(serializer);
			}
		}
	}	// namespace OSP
}	// namespace inexum

#endif	// iNexum_Serialize_h

