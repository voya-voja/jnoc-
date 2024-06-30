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
 * File:		Factory.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					980715	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef inexum_stl_Factory_h
#define inexum_stl_Factory_h

#include "Singleton.h"
#include "Map.h"
#include "Vector.h"

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
		/** A factory method abstarction (encapsulation of factory pattern).
		  * It would be Factory class if MS compiler supported instantiation of
		  * template class Map with pointer to nested class.
		  *
		  * @param LABEL_TYPE - the method lable type.
		  * @param BASE_PRODUCT - the base product returned by create method
		  *
		  *	@author		iNexum Systems Inc.
		  *	@version	1.0.0
		  */
		template< class LABEL_TYPE, class BASE_PRODUCT >
		class Method
		{
		public:
			/// Method's destructor
			virtual ~Method() {};

			/** override to fabricate an instance of desired product. 
			  *
			  * @return a base class pointer to created instance.
			  */
			virtual BASE_PRODUCT* operator()() const = 0;

			/** override to dynamicaly create an instance of derived class
			  *
			  * @return a factory Method pointer.
			  */
			virtual Method<LABEL_TYPE, BASE_PRODUCT>* clone() const = 0;

			/** Label getter.
			  *
			  * @return the lable value of this method
			  */
			LABEL_TYPE label() const { return( mLabel ); };

		protected:
			/// The method's copy constructor
			Method( const Method<LABEL_TYPE, BASE_PRODUCT>& right ) :mLabel( right.mLabel ) {};

			/** The Method overloaded constructor.
			  *
			  * @param lable - a product label value.
			  */
			Method( LABEL_TYPE label );

		private:
			/// Default constructor
			Method() {};

			/// the product name that will be fabricated
			LABEL_TYPE	mLabel;
		};

		/** An encapsulation of a Factory pattern. Instanciate for a specific factory 
		  * by providing type of the label and type of the product that will be 
		  * fabricated. Only one instance of thespecific factory will be created per 
		  * application (the Factory is a Singleton).
		  *
		  * @param LABEL_TYPE - a type of the methods' lables
		  * @param BASE_PRODUCT - the factory's base product
		  *
		  *	@author		iNexum Systems Inc.
		  *	@version	1.0.0
		  */
		template< class LABEL_TYPE, class PRODUCT >
		class Factory : public Singleton< Factory<LABEL_TYPE, PRODUCT> >
		{
		public:
			/** Assign new factory method to the factory instance.
			  *
			  * @param factoryMethod - a reference to a Method to be assigned
			  */
			void assign( /*const*/ Method<LABEL_TYPE, PRODUCT>& factoryMethod );

			/** Create a product associated with specified label.
			  *
			  * @param label - the lable of the product to be created
			  * @return a base product pointer
			  */
			PRODUCT* create( LABEL_TYPE label );

		protected:
			/// The Factory distractor
			virtual ~Factory() {};

		private:
			/// The map of lables to corresponding factory method
//			MapPtr< LABEL_TYPE, Method<LABEL_TYPE, PRODUCT> >	mTable;
			std::map< LABEL_TYPE, Method<LABEL_TYPE, PRODUCT>* >	mTable;
		};

		template< class LABEL_TYPE, class PRODUCT >
		void Factory<LABEL_TYPE, PRODUCT >::assign( /*const*/ Method<LABEL_TYPE, PRODUCT>& 
																	factoryMethod )
		{
			mTable[ factoryMethod.label() ] = &factoryMethod/*.clone()*/;
		}

		template< class LABEL_TYPE, class PRODUCT >
		PRODUCT* Factory<LABEL_TYPE, PRODUCT >::create( LABEL_TYPE label )
		{
			Method<LABEL_TYPE, PRODUCT>& method = *mTable[ label ];
			return( method() );
		}

		template< class LABEL_TYPE, class BASE_PRODUCT >
		Method<LABEL_TYPE, BASE_PRODUCT >::Method( LABEL_TYPE label ) 
		:mLabel(label) 
		{
			Factory<LABEL_TYPE, BASE_PRODUCT>& factory = 
									Factory<LABEL_TYPE, BASE_PRODUCT>::Instance();
			factory.assign( *this );
		}

	}	// namespace stl
}	// namespace inexum

#endif	// inexum_stl_Factory_h
