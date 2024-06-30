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
 * File:		Member.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef inexum_OSP_Member_h
#define inexum_OSP_Member_h

#include <inexum/Types.h>


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
		class Object;

		/** An encapsulation generic class member to be initialized.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier Member
		{
		public:
			/** Overloaded constructor:
			  *
			  * @param address - the void pointer address of a class member.
			  */
			Member( const std::string& type, const std::string& name, void* address );

			/// Member destructor
			virtual ~Member();

			/** The member type verification.
			  *
			  * @return true if it is pointer, otherwise false.
			  */
			virtual bool isPointer() const = 0;

			/** The member's address getter.
			  *
			  * @return the member's address as a void pointer.
			  */
			void* address() const;

			/** Serialize the member's description.
			  *
			  * @param serializer - a reference to an object serializer.
			  */
			void description( JavaObjectSerializer& serializer );

			/** Serialize the member's content.
			  *
			  * @param serializer - a reference to an object serializer.
			  */
			void serialize( JavaObjectSerializer& serializer );

			/** The member's name getter.
			  *
			  * @return the member's name.
			  */
			const std::string& name() const;

			/** Verify if the member is Java basic type.
			  *
			  * @return true if it is of basic type, otherwise false.
			  */
			bool isBasicType() const;

			/** Override to initialize an object.
			  *
			  * @param object - a wrapped object.
			  * @param classOwner - the name of a class that owns the member.
			  */
			virtual void initialize( Object& object, const std::string& classOwner ) = 0;

		protected:
		private:
			/** Serialize a class type description.
			  *
			  * @param serializer - a reference to an object serializer.
			  */
			void classTypeDescription( JavaObjectSerializer& serializer );

			/// The member's name
			std::string	m_name;

			/// It should be Type
			std::string	m_type;

			/// Member's address as a void pointer
			void*	m_address;
		};

		/** A specialization of the member for a pointer.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier PointerMember : public Member
		{
		public:
			/** Overloaded constructor:
			  *
			  * @param address - the void pointer address of a class pointer member.
			  */
			PointerMember( const std::string& type, const std::string& name, 
										void* address );

			/** The member type verification.
			  *
			  * @return true.
			  */
			bool isPointer() const { return( true ); }

			/** Instantiate an object using the object wrapper if the member
			  * address is different than NULL free the space and reference to 
			  *	a created object.
			  *
			  * @param object - a wrapped object address.
			  * @param classOwner - the name of a class that owns the member.
			  */
			void initialize( Object& object, const std::string& classOwner );
		};

		class DeclarationSpecifier ByValueMember : public Member
		{
		public:
			/** Overloaded constructor:
			  *
			  * @param address - the void pointer address of a by value member.
			  */
			ByValueMember( const std::string& type, const std::string& name, 
										void* address );

			/** The member type verification.
			  *
			  * @return false.
			  */
			bool isPointer() const { return( false ); }

			/** Initialize the wrapper by passing member's address.
			  *
			  * @param object - a wrapped object address.
			  * @param classOwner - the name of a class that owns the member.
			  */
			void initialize( Object& object, const std::string& classOwner );
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// inexum_OSP_Member_h

