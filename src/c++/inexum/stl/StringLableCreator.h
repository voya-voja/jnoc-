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
 * File:		StringLableCreator.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020628	nmv			create
 *----------------------------------------------------------------------------*/
#pragma warning(disable:4786)

#ifndef inexum_stl_StringLableCreator_h
#define inexum_stl_StringLableCreator_h

#include "Factory.h"
#include <inexum/Types.h>

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
		/** A string labeled factory Method for specific base product and 
		  * product type. Once Creator temlate is instantiated it will register it self
		  * into the factory instantiated for the same lable type and base product.
		  * The same instance of the Creator will be used to create instances of the 
		  * product that would be returned by the factory as a pointer to a base 
		  * product.
		  *
		  * NOTE:	To instantiate this class for ProductClass0 that is specialization
		  *			of MyProductClass:
		  *	
		  *			template inexum::StringLableCreator<MyProductClass, ProductClass0 >;
		  *
		  *			inexum::StringLableCreator<MyProductClass, ProductClass0 > 
		  *				inexum::StringLableCreator<MyProductClass, ProductClass0 >g_Creator("ProductClass0");
		  *
		  * @param BASE_PRODUCT - a base class of a PRODUCT used to represent different
		  *						  products in a factory
		  * @param PRODUCT - the class for which the objects would be generated, it is
		  *					 defaulted to a BASE_PRODUCT.
		  *
		  *	@see Creator
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template< class BASE_PRODUCT, class PRODUCT = BASE_PRODUCT >
		class StringLableCreator : public Method<std::string, BASE_PRODUCT>
		{
		public:
			/** Overloaded constructor expects the creators label as a string.
			  *
			  * @param label - the creator's label used to register with a factory
			  */
			StringLableCreator(const std::string& label);

			/// Destructor.
			virtual ~StringLableCreator() {};

			/** A factory method. Create the instance of the PRODUCT and return it
			  * as a pointer to BASE_PRODUCT.
			  *
			  * @return a BASE_PRODUCT pointer to created instance of PRODUCT.
			  */
			virtual BASE_PRODUCT* operator()() const;

		protected:
			// Visual C++ 5.0 do not initialize a static instance when parameterized class
			// is instantiated. Therefore, instantiated class should initialize it again.
		#if !defined(WIN32)
		//private:
		#endif	// WIN32

			/// Copy constructor.
			StringLableCreator(const StringLableCreator<BASE_PRODUCT, PRODUCT>& right)
					: Method<std::string, BASE_PRODUCT>(right) 
			{};

			/** The factory Method clone method. Create the instance of 
			  * StringLableCreator and return it as a pointer to a factory Method.
			  *
			  * @return a BASE_PRODUCT pointer to created instance of PRODUCT.
			  */
			Method<std::string, BASE_PRODUCT>* clone() const;

			/** When instantiated it would create an static instance of specified
			  * factory method.
			  */
			static StringLableCreator<BASE_PRODUCT, PRODUCT>	g_Creator;
		};

		// NOTE:	It would not work for WIN32. Initialize it again.
		template<class BASE_PRODUCT, class PRODUCT>
		StringLableCreator<BASE_PRODUCT, PRODUCT>
			StringLableCreator<BASE_PRODUCT, PRODUCT>::g_Creator;

		template<class BASE_PRODUCT, class PRODUCT>
		StringLableCreator<BASE_PRODUCT, PRODUCT>::StringLableCreator(const std::string& label)
		:Method<std::string, BASE_PRODUCT>(label)
		{
		}

		template<class BASE_PRODUCT, class PRODUCT >
		BASE_PRODUCT* StringLableCreator<BASE_PRODUCT, PRODUCT>::operator()() const
		{
			return(new PRODUCT());
		}

		template<class BASE_PRODUCT, class PRODUCT >
		Method<std::string, BASE_PRODUCT>* StringLableCreator<BASE_PRODUCT, PRODUCT>::clone() const
		{
			return(new StringLableCreator<BASE_PRODUCT, PRODUCT>(*this));
		}

		/** Specialization of Creator class that creates a product by useing its 
		  * overloaded constructor that receives the lable.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template< class BASE_PRODUCT, class PRODUCT = BASE_PRODUCT >
		class CreateWithStringLable : public Method<std::string, BASE_PRODUCT>
		{
		public:
			CreateWithStringLable(const std::string& label) 
				:Method<std::string, BASE_PRODUCT>(label)
			{}

			~CreateWithStringLable()
			{
			}

			/** Creates an instance of a PRODUCT using the PRODUCT's overloaded 
			  * constructor that receives the lable.
			  *
			  * @return a created instance as a BSAE_PRODUCT pointer.
			  */
			virtual BASE_PRODUCT* operator()() const;

			/** The factory Method clone method. Create the instance of 
			  * StringLableCreator and return it as a pointer to a factory Method.
			  *
			  * @return a BASE_PRODUCT pointer to created instance of PRODUCT.
			  */
			Method<std::string, BASE_PRODUCT>* clone() const;

		private:
			/** When instantiated it would create an static instance of specified
			  * factory method.
			  */
			static CreateWithStringLable<BASE_PRODUCT, PRODUCT>	g_Creator;
		};

		template< class BASE_PRODUCT, class PRODUCT >
		BASE_PRODUCT* 
		CreateWithStringLable< BASE_PRODUCT, PRODUCT>::operator()() const
		{
			return(new PRODUCT(label()));
		}

		template<class BASE_PRODUCT, class PRODUCT >
		Method<std::string, BASE_PRODUCT>* CreateWithStringLable<BASE_PRODUCT, PRODUCT>::clone() const
		{
			return(new CreateWithStringLable<BASE_PRODUCT, PRODUCT>(*this));
		}
	}	// namespace stl
}	// namespace inexum
	
#endif	// inexum_stl_StringLableCreator_h
