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
 * File:		Entity.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef inexum_OSP_Entity_h
#define inexum_OSP_Entity_h

#include <iostream.h>
#include <inexum/Types.h>
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
		/** 
		  * @memo	A general encapsulation of an element for the table of symbols of 
		  *			a Java object parser.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class /*DeclarationSpecifier*/ Entity
		{
		public:
			/// Default constructor
			Entity() {}

			/// Copy constructor
			Entity( const Entity& right ) : m_name( right.m_name ) {}

			/** Overloaded constructor:
			  *
			  * @param	name - the entity name
			  */
			Entity( const std::string& name ) : m_name( name ) {}

			/// Virtual Destructor
			virtual ~Entity() {}

			/** The entity name getter
			  *
			  * @return a name string
			  */
			virtual const std::string& name() const { return( m_name ); }

			/** The entity name setter
			  *
			  * @param name - a string name of the entity
			  */
			virtual void setName( const std::string& name ) { m_name = name; }

		protected:
		private:
			/// The entity name string
			std::string		m_name;

			#ifdef iNxmDebug
				friend util::DebugClass<Entity>;
			#endif	// iNxmDebug
		};
	}	// namespace OSP

	#ifdef iNxmDebug
		/// A debug method that dumps the Object content
		template<> void util::DebugClass<OSP::Entity>::print()
		{
			output() << indent() << object().name().data() << " = ";
		}
	#endif	// iNxmDebug

}	// namespace inexum

#endif	// iNexum_Entity_h

