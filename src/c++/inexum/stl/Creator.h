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
 * File:		Creator.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					980715	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef inexum_stl_Creator_h
#define inexum_stl_Creator_h

#include "Factory.h"

/** iNexum classes.
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
namespace inexum
{
	/** Standard Template Library extensions.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
	namespace stl
	{
		/** A labeled factory method creates a product specialized from a base product
		  * using product's default constructor. Once Creator temlate is instantiated 
		  * it will register it self into the factory instantiated for the same lable 
		  * type and base product. The same instance of the Creator will be used to 
		  * create instances of the product that would be returned by the factory as a 
		  * pointer to a base product.
		  *
		  * NOTE:	Make an instance of this class in a cpp file, e.g. if 
		  *		MyBaseProductClass is a base class of ProductClass0, then:
		  *	
		  *			template Creator< int, 0, MyBaseProductClass, ProductClass0>;
		  *
		  *
		  * @param LABEL_TYPE - allows for any C++ builtin type to be used as a lable
		  *						of a creator in a factory
		  * @param LABEL - is the lable associated with a creator of a PRODUCT
		  * @param BASE_PRODUCT - a base class of a PRODUCT used to represent different
		  *						  products in a factory
		  * @param PRODUCT - the class for which the objects would be generated, it is
		  *					 defaulted to a BASE_PRODUCT.
		  *
		  * @see		inexum::Factory
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template< class LABEL_TYPE, LABEL_TYPE LABEL, class BASE_PRODUCT, 
					class PRODUCT = BASE_PRODUCT >
		class Creator : public Method<LABEL_TYPE, BASE_PRODUCT>
		{
		public:
			/// The default constructor
			Creator();

			/// The Creator's destructor
			virtual ~Creator() {};

			/** Creates an instance of a PRODUCT using the PRODUCT's default 
			  * constructor.
			  *
			  * @return a created instance as a BSAE_PRODUCT pointer.
			  */
			virtual BASE_PRODUCT* operator()() const;

		protected:
			// Visual C++ 5.0 do not initialize a static instance when parameterized class
			// is instantiated. Therefore, instantiated class should initialize it again.
		#if !defined(WIN32)
		private:
		#endif	// WIN32
			/// Creator copy constructor
			Creator( const 
					Creator<LABEL_TYPE, LABEL, BASE_PRODUCT, 
									PRODUCT>& right)
					: Method<LABEL_TYPE, BASE_PRODUCT>( right ) {};

			/** A Creator's clone method.
			  *
			  * NOTE:	If the Creator is specialized further, the clone method has to 
			  *			be overridden.
			  *
			  *	@return the pointer to the Factory Method class
			  */
			Method<LABEL_TYPE, BASE_PRODUCT>* clone() const;

			/** When instantiated it will create an static instance of specified
			  * factory method
			  */
			static Creator<LABEL_TYPE, LABEL, 
									BASE_PRODUCT, PRODUCT>	g_Creator;
		};

		// NOTE:	It would not work for WIN32. Initialize it again.
		template< class LABEL_TYPE, LABEL_TYPE LABEL, class BASE_PRODUCT, 
					class PRODUCT >
		Creator<LABEL_TYPE, LABEL, BASE_PRODUCT, PRODUCT>
			Creator<LABEL_TYPE, LABEL, 
							BASE_PRODUCT, PRODUCT>::g_Creator;

		template< class LABEL_TYPE, LABEL_TYPE LABEL, class BASE_PRODUCT, 
					class PRODUCT >
		Creator<LABEL_TYPE, LABEL, 
							BASE_PRODUCT, PRODUCT>::Creator()
		:Method<LABEL_TYPE, BASE_PRODUCT>(LABEL)
		{
		}

		template< class LABEL_TYPE, LABEL_TYPE LABEL, class BASE_PRODUCT, 
					class PRODUCT >
		BASE_PRODUCT* 
		Creator<LABEL_TYPE, LABEL, BASE_PRODUCT, PRODUCT>::operator()() const
		{
			return( new PRODUCT() );
		}

		template< class LABEL_TYPE, LABEL_TYPE LABEL, class BASE_PRODUCT, 
					class PRODUCT >
		Method<LABEL_TYPE, BASE_PRODUCT>* 
		Creator<LABEL_TYPE, LABEL, BASE_PRODUCT, PRODUCT>::clone() const
		{
			return( new Creator<LABEL_TYPE, LABEL, BASE_PRODUCT, PRODUCT>( *this ) );
		}


		/** Creator specialization that creates a product by using its overloaded 
		  * constructor that receives the lable.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template< class LABEL_TYPE, LABEL_TYPE LABEL, class BASE_PRODUCT, 
					class PRODUCT = BASE_PRODUCT >
		class CreateWithLable : public Creator<LABEL_TYPE, LABEL, BASE_PRODUCT, PRODUCT>
		{
		public:
			/** Creates an instance of a PRODUCT using the PRODUCT's overloaded 
			  * constructor that receives the lable.
			  *
			  * @return a created instance as a BASE_PRODUCT pointer.
			  */
			virtual BASE_PRODUCT* operator()() const;
		};

		template< class LABEL_TYPE, LABEL_TYPE LABEL, class BASE_PRODUCT, 
					class PRODUCT >
		BASE_PRODUCT* 
		CreateWithLable<LABEL_TYPE, LABEL, BASE_PRODUCT, PRODUCT>::operator()() const
		{
			return( new PRODUCT( LABEL ) );
		}
	}	// namespace 
}	// namespace inexum

#endif	// inexum_stl_Creator_h
