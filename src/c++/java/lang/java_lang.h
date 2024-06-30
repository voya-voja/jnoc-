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
 * File:		java_lang.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef java_lang_JavaLangType_h
#define java_lang_JavaLangType_h

#include <inexum/java_serializable.h>
#include <inexum/Types.h>
#include <memory>
#include <inexum/util/Debug.h>
#include <inexum/stl/Vector.h>
#include <inexum/definitions.h>

/** iNexum's java classes implemented in C++.
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
namespace java
{
	/** iNexum's java/lang classes implemented in C++.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
	namespace lang
	{
		/** iNexum's C++ implementation of a 'java/lang/Number' class.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier Number 
		{ 
			serialize(Number); 
		public:
			virtual ~Number() {} 
		};

		/** iNexum's C++ implementation of a 'java/lang/<built in type>' class.
		  *
		  *	@doc
		  * NOTE: C++ instantiation for bool JavaLangType<bool> has not been 
		  * serialized as specialization of java/lang/Number class following 
		  * the Java class inheritance.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		template< class Type >
		class JavaLangType : public Number
		{
			serialize(JavaLangType< Type >); 
			Type	value;

			#ifdef iNxmDebug
				friend class inexum::util::DebugClass<JavaLangType<Type> >;
			#endif	// iNxmDebug
		public:
			/// Default constructor
			JavaLangType() : value(0) {};

			/// Copy constructor
			JavaLangType(const JavaLangType<Type>& right) : value(right.value) {};

			/** Overloaded constructor that sets a value
			  *
			  * @param v - a value to be set
			  */
			JavaLangType(Type v) : value(v) {};

			/// Destructor
			virtual ~JavaLangType() 
			{ 
			};

			/** Assign operator
			  *
			  * @param right - a right operand
			  * @return - reference to this object
			  */
			JavaLangType<Type>& operator=(const JavaLangType<Type>& right) 
			{
				value = right.value;
				return(*this);
			};

			/** Equal operator
			  *
			  * @param right - a right operand
			  * @return - true if the values are equal, otherwise false
			  */
			bool operator==(const JavaLangType<Type>& right) 
			{
				return(value == right.value);
			};

			/** Less operator
			  *
			  * @param right - a right operand
			  * @return - true this value is less then right operand value, otherwise false
			  */
			bool operator<(const JavaLangType<Type>& right) 
			{
				return(value < right.value);
			};
		};

		/// java.lang.Byte
		typedef JavaLangType<byte>			Byte;
		ExternTemplate template class DeclarationSpecifier JavaLangType<byte>;

		/// java.lang.Character
		typedef JavaLangType<wchar_t>			Character;
		ExternTemplate template class DeclarationSpecifier JavaLangType<wchar_t>;

		/// java.lang.Double
		typedef JavaLangType<double>		Double;
		ExternTemplate template class DeclarationSpecifier JavaLangType<double>;

		/// java.lang.Float
		typedef JavaLangType<float>			Float;
		ExternTemplate template class DeclarationSpecifier JavaLangType<float>;

		/// java.lang.Integer
		typedef JavaLangType<int>			Integer;
		ExternTemplate template class DeclarationSpecifier JavaLangType<int>;

		/// java.lang.Long
		typedef JavaLangType<inexum::JLong>	Long;
		ExternTemplate template class DeclarationSpecifier JavaLangType<inexum::JLong>;

		/// java.lang.Short
		typedef JavaLangType<short>			Short;
		ExternTemplate template class DeclarationSpecifier JavaLangType<short>;

		/// java.lang.Boolean
		typedef JavaLangType<bool>			Boolean;
		ExternTemplate template class DeclarationSpecifier JavaLangType<bool>;

		/// java.lang.String
		typedef std::basic_string<char>	String;

	}	// namespace lang
}	// namespace java

ExternTemplate template class DeclarationSpecifier std::vector<java::lang::Number*>;
ExternTemplate template class DeclarationSpecifier inexum::stl::VectorPtr<java::lang::Number>;

ExternTemplate template class DeclarationSpecifier std::vector<java::lang::Byte*>;
ExternTemplate template class DeclarationSpecifier inexum::stl::VectorPtr<java::lang::Byte>;

ExternTemplate template class DeclarationSpecifier std::vector<java::lang::Character*>;
ExternTemplate template class DeclarationSpecifier inexum::stl::VectorPtr<java::lang::Character>;

ExternTemplate template class DeclarationSpecifier std::vector<java::lang::Double*>;
ExternTemplate template class DeclarationSpecifier inexum::stl::VectorPtr<java::lang::Double>;

ExternTemplate template class DeclarationSpecifier std::vector<java::lang::Float*>;
ExternTemplate template class DeclarationSpecifier inexum::stl::VectorPtr<java::lang::Float>;

ExternTemplate template class DeclarationSpecifier std::vector<java::lang::Integer*>;
ExternTemplate template class DeclarationSpecifier inexum::stl::VectorPtr<java::lang::Integer>;

ExternTemplate template class DeclarationSpecifier std::vector<java::lang::Long*>;
ExternTemplate template class DeclarationSpecifier inexum::stl::VectorPtr<java::lang::Long>;

ExternTemplate template class DeclarationSpecifier std::vector<java::lang::Short*>;
ExternTemplate template class DeclarationSpecifier inexum::stl::VectorPtr<java::lang::Short>;

ExternTemplate template class DeclarationSpecifier std::vector<java::lang::Boolean*>;
ExternTemplate template class DeclarationSpecifier inexum::stl::VectorPtr<java::lang::Boolean>;

#ifdef iNxmDebug
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<java::lang::Boolean>;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<java::lang::Byte>;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<java::lang::Character>;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<java::lang::Double>;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<java::lang::Float>;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<java::lang::Integer>;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<java::lang::Long>;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<java::lang::Short>;

	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<inexum::stl::VectorPtr<java::lang::Boolean> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<inexum::stl::VectorPtr<java::lang::Byte> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<inexum::stl::VectorPtr<java::lang::Character> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<inexum::stl::VectorPtr<java::lang::Double> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<inexum::stl::VectorPtr<java::lang::Float> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<inexum::stl::VectorPtr<java::lang::Integer> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<inexum::stl::VectorPtr<java::lang::Long> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<inexum::stl::VectorPtr<java::lang::Short> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<inexum::stl::VectorPtr<java::lang::String> >;
#endif	// iNxmDebug

#endif	// java_lang_JavaLangType_h

