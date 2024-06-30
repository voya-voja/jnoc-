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
 * File:		Singleton.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					980715	nmv			create
 *----------------------------------------------------------------------------*/
#pragma warning(disable:4786)

#ifndef inexum_stl_Singleton_h
#define inexum_stl_Singleton_h

#include "SingletonVictim.h"

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
		/** Encapsulation of singleton pattern. The instantiated class should be a 
		  * instantiation parameter. Only one instance of instantiated class will
		  * be created per application.
		  *
		  * The singleton class should be declared like:
		  *
		  *		class MySingleton : public Singleton< MySingleton > { ... };
		  *
		  * @param CHILD - the singleton class
		  *
		  *	@author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template< class CHILD >
		class Singleton : protected SingletonVictim
		{
		public:
			/** The Singleton instance getter.
			  *
			  * @return a refrence to the singleton instance
			  */
			static CHILD& Instance();

		protected:
			/// Singleton default constructor
			Singleton() {};

			/// Singleton destructor
			virtual ~Singleton() {};

		private:
			/// The pointer to a Singleton instance
			static CHILD*	gmpSingleton;
		};


		template< class CHILD >
		CHILD*	Singleton<CHILD>::gmpSingleton = NULL;

		template< class CHILD >
		CHILD& Singleton<CHILD>::Instance()
		{
			if( gmpSingleton == NULL )
			{
				gmpSingleton = new CHILD;
			}
			return( *gmpSingleton );
		}
	}	// namespace stl
}	// namespace inexum

#endif	// inexum_stl_Singleton_h
