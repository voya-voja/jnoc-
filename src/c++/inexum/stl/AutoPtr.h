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
 * File:		AutoPtr.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					980715	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef inexum_stl_AutoPtr_h
#define inexum_stl_AutoPtr_h

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
		#if !defined( sun )

			#include <memory>

			/* Auto pointer implementation for platforms where STD is available.
			  * 
			  * @param Ty - the class type of auto pointer's element
			  */
			template<class _Ty> class AutoPtr : public std::auto_ptr< _Ty > 
			{
			public:
				/* Overloaded constructor
				  *
				  * @param P - the pointer to object to be refered  by the auto pointer
				  */
				explicit AutoPtr(_Ty *_P = 0) :std::auto_ptr< _Ty >(_P) {};
				
			};

		#else

			#include "language.h"

			/** Auto pointer implementation for platforms where STD is not available.
			  * 
			  * @param Ty - the class type of auto pointer's element.
			  *
			  * @author		iNexum Systems Inc.
			  * @version	1.0.0
			  */
			template<class _Ty>
			class AutoPtr
			{
			public:
				/// The type of the element of the auto pointer
				typedef _Ty element_type;

				/** Overloaded constructor
				  *
				  * @param P - the pointer to object to be refered  by the auto pointer
				  */
				explicit AutoPtr(_Ty *_P = 0) : _Owns(_P != 0), _Ptr(_P) {}

				/** Auto pointer's copy constructor - transfers the ownership of the 
				  * referenced object from _Y object to this object of auto pointer
				  */
				AutoPtr(const AutoPtr<_Ty>& _Y) : _Owns(_Y._Owns), _Ptr(_Y.release()) {}

				/** Auto pointers destructor - removes the referenced object if
				  * this instance of autopointer owns the referenced object.
				  */
				~AutoPtr()
				{
					if (_Owns) delete _Ptr;
				}

				/** Assign operator - if this autopointer owns the referenced object,
				  * removes the referenced object and receives the reference from _Y 
				  * object. This object takes ownership of the referenced object.
				  */
				AutoPtr<_Ty>& operator=(const AutoPtr<_Ty>& _Y)
				{
					if (_Ptr != _Y.get())
					{
						if (_Owns) delete _Ptr;
						_Owns = _Y._Owns;
						_Ptr = _Y.release();
					}
					else if (_Y._Owns)
					{
						_Owns = true;
					}
					return (*this);
				}

				/// @return the reference to the referenced object
				_Ty& operator*() const { return (*get()); }

				/// @return the pointer of the referenced object
				_Ty *operator->() const { return (get()); }

				/** The referenced object getter.
				  *
				  * @return the pointer to the referenced object
				  */
				_Ty *get() const { return (_Ptr); }

				/** Release teh ownership over the referenced object and return its 
				  * pointer.
				  *
				  * @return the pointer to the referenced object
				  */
				_Ty *release() const
				{
					((AutoPtr<_Ty> *)this)->_Owns = false;
					return (_Ptr);
				}

			private:
				/** Ownership flag, true if thsi instance of auto pinter owns 
				  * referenced object
				  */
				bool _Owns;
				/// The pointer to teh referenced object
				_Ty *_Ptr;
			};

		#endif	// sun
	}	// namespace stl
}	// namespace inexum

#endif	// iNexum_Auto_ptr_h
