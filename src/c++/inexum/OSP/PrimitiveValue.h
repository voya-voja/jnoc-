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
 * File:		PrimitiveValue.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef inexum_OSP_PrimitiveValue_h
#define inexum_OSP_PrimitiveValue_h

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
		/** Encapsulates the description of Java builtin value.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class Value
		{
		public:
			/// Value desturctor
			virtual ~Value() {}

			virtual void print(ostream& out) const = 0;

		protected:
		private:
		};

		/** Specialization that provides the description for Java bultin values.
		  *
		  * @param TYPE - the builtin type
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template<class TYPE>
		class PrimitiveValue : public Value 
		{
		public:
			/** Overloaded constructor
			  *
			  * @param value - the reference to the value
			  */
			PrimitiveValue(const TYPE& value) 
				: m_value(value) 
			{
			}

			/** The value getter.
			  *
			  * @return the constant reference to the contained value
			  */
			const TYPE& get() const { return(m_value); };

			void print(ostream& out) const { out << m_value; };

		protected:
		private:
			/// The builtin value
			TYPE	m_value;
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// inexum_OSP_PrimitiveValue_h
