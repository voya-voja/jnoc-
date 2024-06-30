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
 * File:		Class.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef inexum_OSP_Class_h
#define inexum_OSP_Class_h

#include "Entity.h"

#include <map>
#include <vector>
#include <iostream>
#include <inexum/Types.h>
#include "javaObjParser.h"
#include <inexum/util/Debug.h>

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
		class Object;

		/** Symbol of a java object parser that encapsulates a class description.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class Class : public Entity
		{
			/// Map of member names to the class member symbols
			typedef std::map<std::string, Object*>	Objects;
			/// Pair of a member name and the class member symbol
			typedef Objects::value_type				ObjectPair;
		public:
			/// List of member object symbols
			typedef std::vector<Object*> 			ObjectList;
			/// Member object symbol list iterator
			typedef ObjectList::iterator			MemberIterator;
			/// Constant member object symbol list iterator
			typedef ObjectList::const_iterator		const_MemberIterator;

			/// Class symbol default constructor
			Class() 
				: m_membersCount(0), m_pSuperClass(NULL), m_currentMemberIndex(0) 
			{}

			/// Class symbol copy constructor
			Class( const Class& right );

			/** Overloaded Class symbol constructor:
			  *
			  * @param name - the class name string
			  */
			Class( const std::string& name ) 
				: Entity( name ), m_membersCount(0), m_pSuperClass(NULL)
			{}

			/// Class symbol destructor
			virtual ~Class();

			/** Class symbol clone method:
			  * 
			  * @return a cloned instance of the Class symbol
			  */
			virtual Class* clone() const { return( new Class( *this ) ); }

			/** Class Symbol's member count getter.
			  *
			  * @return the number of Class symbol members
			  */
			int membersCount() const { return( m_membersCount); }

			/** Class Symbol's member count setter.
			  *
			  * @param count - the number of Class symbol members
			  */
			void membersCount( int count ) { m_membersCount = count; }

			/** Super class symbol getter.
			  *
			  * @return a reference to a base class symbol
			  */
			Class& superClass() { return( *m_pSuperClass ); }

			/** Constant super class symbol getter.
			  *
			  * @return a constant reference to a base class symbol
			  */
			const Class& superClass() const { return( *m_pSuperClass ); }
			
			/** Super class symbol setter.
			  *
			  * @param aClass - a reference class symbol that represents a base class
			  */
			void superClass( Class& aClass ) 
			{ 
				m_pSuperClass = aClass.clone(); 
			}

			/** Check have been all class member symbols loaded to the class.
			  *
			  * @return true is all the symbols have been loaded, otherwise false.
			  */
			bool isComplete() const 
			{
				return( ( m_pSuperClass == NULL 
						|| m_pSuperClass->isComplete() ) 
								&& m_members.size() == m_membersCount ); 
			}

			/** Verify does the internal cursor points to the last member of the 
			  * class description.
			  *
			  * @return true if cursor is at last member, otherwise false.
			  */
			virtual bool isLastMember() const
			{
				return( ( m_pSuperClass == NULL 
						|| m_pSuperClass->isLastMember() ) 
								&& m_currentMemberIndex == m_membersCount ); 
			}

			/** Add a member's objet symbol reference to the class.
			  *
			  * @param member - the reference to a object symbol
			  */
			void add( Object& member );

			/** Member symbol iterator positioned to the beginning of the member list.
			  *
			  * @return	a constant member symbol iterator
			  */
			const_MemberIterator memberBegin() const { return( m_memberList.begin() ); }

			/** Member symbol iterator positioned to the beginning of the member list.
			  *
			  * @return	a member symbol iterator
			  */
			MemberIterator memberBegin() { return( m_memberList.begin() ); }

			/** Member symbol iterator positioned to the end of the member list.
			  *
			  * @return	a constant member symbol iterator
			  */
			const_MemberIterator memberEnd() const { return( m_memberList.end() ); }

			/** Member symbol iterator positioned to the end of the member list.
			  *
			  * @return	a member symbol iterator
			  */
			MemberIterator memberEnd() { return( m_memberList.end() ); }

			/** Sets Java class description flags for this class symbol.
			  * The flag values are:
			  *	
			  *		SC_SERIALIZABLE = 0x02		- Java Serializable class;
			  *
			  *		SC_EXTERNALIZABLE = 0x04	- Java External class description;
			  *
			  *		SC_WRITE_METHOD = 0x01		- Only with SC_SERIALIZABLE, if the
			  *									class description has been provided;
			  *
			  *		SC_BLOCK_DATA = 0x08		- Only with SC_EXTERNALIZABLE, if the
			  *									class description has been provided;
			  *
			  * @param flags - a byte code
			  */
			void classDescriptionFlags( byte flags ) { m_classDescriptionFlags = flags; }

			/** Converts Java class description flags to internal parser token.
			  *
			  * @return a token value
			  */
			virtual int classDescriptionFlag2Token() const;

			/** Sets the internal cursor to the specified class member symbol, where 
			  * the complete member list for a class is created as a concatenation of
			  * a class's member list to a super class's member list, e.g. the index 0
			  * would position the cursor to point to a member 0 in the base class if 
			  * such is available.
			  *
			  *	@param index - the member's index in the complete list of members
			  */
			void moveToMember( int index );

			/** Return the current member symbol and move to the next member in the 
			  * complete list of members for the class symbol, where 
			  * the complete member list for a class is created as a concatenation of
			  * a class's member list to a super class's member list, e.g. the index 0
			  * would position the cursor to point to a member 0 in the base class if 
			  * such is available.
			  *
			  *	@return a reference to an Object symbol instance representing the 
			  *			current member
			  */
			Object& nextMember();

			/** Create an C++ object of the C++ class described by this class symbol
			  * and initialize object values with values from this class symbol.
			  *
			  * @return the address of a created object as a void pointer, NULL if failed.
			  */
			virtual void* instantiate() const;

			/** Initialize an C++ object of the C++ class described by this class symbol
			  * with values from this class symbol.
			  *
			  * @param address - the void pointer address of the object to be 
								initialized.
			  */
			virtual void initialize( void* address ) const;

		protected:

		private:

			/// The number of members for the class
			int			m_membersCount;

			/// A cursor to the current member
			int			m_currentMemberIndex;

			/// The map of member names to the member symbols
			Objects		m_members;

			/// The list of member sysmbols
			ObjectList	m_memberList;

			/// An reference to the instance of a super class symbol
			Class*		m_pSuperClass;

			/// The class description flag
			byte		m_classDescriptionFlags;

			/** The class description flag values:
			  *	SC_SERIALIZABLE = 0x02		- Java Serializable class;
			  *	SC_EXTERNALIZABLE = 0x04	- Java External class description;
			  *	SC_WRITE_METHOD = 0x01		- Only with SC_SERIALIZABLE, if the
			  *								class description has been provided;
			  *	SC_BLOCK_DATA = 0x08		- Only with SC_EXTERNALIZABLE, if the
			  *								class description has been provided;
			  */
			static const byte SC_SERIALIZABLE;
			static const byte SC_EXTERNALIZABLE;
			static const byte SC_WRITE_METHOD;  /// if SC_SERIALIZABLE
			static const byte SC_BLOCK_DATA;    // if SC_EXTERNALIZABLE

			#ifdef iNxmDebug
				friend util::DebugClass<Class>;
			#endif	// iNxmDebug
		};
	}	// namespace OSP	
}	// namespace inexum

#endif	// inexum_OSP_Class_h

