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
 * File:		java_serializable.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/
#ifndef java_serializable_h
#define java_serializable_h

#pragma warning(disable:4786)
#pragma warning(disable:4661)

#include <inexum/OSP/Serialize.h>
#include <inexum/OSP/Member.h>
#include <inexum/OSP/SerializableArray.h>
#include <inexum/OSP/SerializableVoidPointerArray.h>
#include <inexum/OSP/SerializableTypePointerArray.h>
#include <inexum/OSP/SerializableCreator.h>
#include <inexum/stl/StringLableCreator.h>

#include "Types.h"

/** Promote a C++ class as Serializable. This macro must be used in a class 
  * declaration section to promote a C++ class to be Serializable. The macro 
  * assigns the instantiation of inexum::OSP::Serialize class for the C++ class as a 
  * friend to the C++ class.
  *
  *	@doc	Example:
  *
  *			.class MyClass {
  *
  *			..	serialize(MyClass);
  *
  *			..	MyAnotherClass			m_another;
  *
  *			..	java::lang::Integer*	m_pInt;
  *
  *			..	int						m_int;
  *
  *			.};
  *
  *
  *	@param _class_ - a class name
  *
  * @see	inexum::OSP::Serialize
  * @see	serialize_begin
  * @see	serialize_by_value
  * @see	serialize_pointer
  * @see	serialize_end
  * @see	serialize_array
  * @see	serialize_pointer_array
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
#define serialize(_class_) \
	friend class inexum::OSP::Serialize<_class_ >; \
	static inexum::OSP::Serializable::CppJavaNamesRegister gm_namesRegister; \
	inexum::OSP::Serializable::ObjectHandler m_SerialObjectHandler
 
/** The beginning of a serialize section that defines the map of members of a 
  *	C++ Serializable class. This macro should be used in a class's cpp file to
  *	create only one instantiation of inexum::OSP::Serialize class for the C++ 
  *	Serializable class.
  *
  *	@doc	Example (file MyClass.cpp):
  * 
  *		.serialize_begin("com.myPackage.MyClass", MyClass, "", 0)
  *
  * 		..	serialize_by_value("com.myPackage.MyAnotherClass", "m_another", m_another)
  *
  * 		..	serialize_pointer("java.lang.Integer", "m_int", m_pInt);
  *
  * 		..	serialize_by_value("I", "m_i", m_int);
  *
  * 		.serialize_end
  *
  *
  *	The C++ class name does not have to be the same as Java class name.
  *
  *	@postcondition	serialize_begin is followed by the definition of zero or 
  *					more of serialize_by_value or serialize_pointer macros. The
  *					serialize block will end with serialize_end.
  *
  *	@param java_class_name - a Java class name as a string.
  *	@param cpp_class - a corresponding C++ class
  *	@param superclass_java_name - a superclass java class name or empty string if there is no superclass.
  *	@param serial_version_uid - a serial version uid number as specified in java implementation of the class
  *						'private static final long serialVersionUID' variable should be specified for
  *						 any serializable class. More then one class can have the same serialVersionUID. 
  *						Java 2 SDK provides 'serialver' RMI tool that returns a class serialVersionUID.
  *
  *	@see	inexum::OSP::Serialize
  *	@see	inexum::OSP::StringLableCreator
  *	@see	serialize
  *	@see	serialize_by_value
  *	@see	serialize_pointer
  *	@see	serialize_end
  *
  *	@author	iNexum Systems Inc.
  *	@version	1.0.0
  */
#define serialize_begin(java_class_name, cpp_class, superclass_java_name, serial_version_uid)	\
	\
	inexum::OSP::SerializeCreator<cpp_class > \
				inexum::OSP::SerializeCreator<cpp_class >::g_Creator(java_class_name); \
	\
	inexum::OSP::Serializable::CppJavaNamesRegister cpp_class::gm_namesRegister(\
							typeid(cpp_class).name() + \
									inexum::OSP::Serializable::ClassSize(), java_class_name); \
	\
	inexum::JLong inexum::OSP::Serialize<cpp_class >::serialVersionUID() const \
	{ \
		return(serial_version_uid); \
	} \
	\
	void inexum::OSP::Serialize<cpp_class >::load(cpp_class& obj) { \
		superClass(superclass_java_name);
		


/** Define a serialize map of a class memeber. The macro should be used in
  * serialize block to map a class member that is owned by value.
  *
  *	@doc	Example (file MyClass.cpp):
  * 
  *		.serialize_begin("com.myPackage.MyClass", MyClass, "", 0)
  *
  * 		..	serialize_by_value("com.myPackage.MyAnotherClass", "m_another", m_another)
  *
  * 		..	serialize_pointer("java.lang.Integer", "m_int", m_pInt);
  *
  * 		..	serialize_by_value("I", "m_i", m_int);
  *
  * 		.serialize_end
  *
  *	The C++ class member name does not have to be the same as Java class member name.
  *
  *	@param java_type_name - a member's java type name as a string. Builtin types are:
  *					byte - B, char - C, double - D, float - F, integer - I, long - J, short - S, boolean - Z.
  *					If the member is an instance of an array, the type should start with '[' character and 
  *					and followed by the elements type, e.g. "[I" or "[java.lang.Number".
  *	@param java_member_name - a Java member name as a string.
  *	@param cpp_member - a corresponding class member name.
  *
  *	@precondition	serialize_begin precedes the definition of one or more of 
  *					serialize_by_value or serialize_pointer macros
  *	@postcondition	The macro must be followed with a semicolon. Also, the 
  *					serialize block must be closed with serialize_end macro.
  *
  * 	@see	inexum::OSP::Serialize
  * 	@see	serialize
  * 	@see	serialize_begin
  * 	@see	serialize_pointer
  * 	@see	serialize_end
  *
  * 	@author	iNexum Systems Inc.
  * 	@version	1.0.0
  */
#define serialize_by_value(java_type_name, java_member_name, cpp_member) \
	addMember(java_member_name, \
		new inexum::OSP::ByValueMember(java_type_name, java_member_name, (void*)&obj.cpp_member))

/** Define a serialize map of a class memeber. The macro should be used in
  * serialize block to map a class member that is owned as a pointer.
  *
  *		.serialize_begin("com.myPackage.MyClass", MyClass, "", 0)
  *
  * 		..	serialize_by_value("com.myPackage.MyAnotherClass", "m_another", m_another)
  *
  * 		..	serialize_pointer("java.lang.Integer", "m_int", m_pInt);
  *
  * 		..	serialize_by_value("I", "m_i", m_int);
  *
  * 		.serialize_end
  *
  *	The C++ class member name does not have to be the same as Java class member name.
  *
  *	@param java_type_name - a member's java type name as a string. Builtin types are:
  *					byte - B, char - C, double - D, float - F, integer - I, long - J, short - S, boolean - Z.
  *					If the member is an instance of an array, the type should start with '[' character and 
  *					and followed by the elements type, e.g. "[I" or "[java.lang.Number".
  *	@param java_member_name - a Java member name as a string.
  *	@param cpp_member - a corresponding class member name.
  *
  *	@precondition	serialize_begin precedes the definition of one or more of 
  *					serialize_by_value or serialize_pointer macros
  *	@postcondition	The macro must be followed with a semicolon. Also, the 
  *					serialize block must be closed with serialize_end macro.
  *
  * 	@see	inexum::OSP::Serialize
  * 	@see	serialize
  * 	@see	serialize_begin
  * 	@see	serialize_by_value
  * 	@see	serialize_end
  *
  * 	@author	iNexum Systems Inc.
  * 	@version	1.0.0
  */
#define serialize_pointer(java_type_name, java_member_name, cpp_member) \
	addMember(java_member_name, \
		new inexum::OSP::PointerMember(java_type_name, java_member_name, (void*)&obj.cpp_member))

/** The end of a serialize section that defines the map of members of a 
  *	C++ Serializable class.
  *
  *	@doc	Example (file MyClass.cpp):
  * 
  *		.serialize_begin("com.myPackage.MyClass", MyClass, "", 0)
  *
  * 		..	serialize_by_value("com.myPackage.MyAnotherClass", "m_another", m_another)
  *
  * 		..	serialize_pointer("java.lang.Integer", "m_int", m_pInt);
  *
  * 		..	serialize_by_value("I", "m_i", m_int);
  *
  * 		.serialize_end
  *
  *
  *	@precondition	serialize_end is follows by the definition of zero or 
  *					more of serialize_by_value or serialize_pointer macros, 
  *					which are preceded by serialize_begin macro.
  *
  *	@see	inexum::OSP::Serialize
  *	@see	serialize
  *	@see	serialize_begin
  *	@see	serialize_by_value
  *	@see	serialize_pointer
  *
  *	@author	iNexum Systems Inc.
  *	@version	1.0.0
  */
#define serialize_end	}

/** Define the serializable array. The Java builtin types are supported. The macro
  * can be used for user specified classes that act as C++ builtin types.
  *
  *	@doc	Example (file java_lang.cpp):
  * 
  *			. serialize_array("I", int, 0x4DBA602676EAB2A5);
  *
  *	@param java_type_name - a Java type name as a string of the array elements.
  *	@param cpp_type - the C++ type the array elements.
  *	@param serial_version_uid - a serial version uid number as specified in java implementation of the class
  *						'private static final long serialVersionUID' variable should be specified for
  *						any serializable class. More then one class can have the same serialVersionUID. 
  *						Java 2 SDK provides 'serialver' RMI tool that returns a class serialVersionUID.
  *
  *	@see	inexum::OSP::SerializableArray
  *	@see	inexum::OSP::StringLableCreator
  *	@see	serialize
  *	@see	serialize_pointer_array
  *
  *	@author	iNexum Systems Inc.
  *	@version	1.0.0
  */
#define serialize_array(java_type_name, cpp_type, serial_version_uid) \
	template class inexum::OSP::SerializableArray<cpp_type>; \
	\
	template class inexum::stl::CreateWithStringLable<inexum::OSP::Serializable, \
										inexum::OSP::SerializableArray<cpp_type> >; \
	\
	inexum::stl::CreateWithStringLable<inexum::OSP::Serializable, \
									inexum::OSP::SerializableArray<cpp_type> > \
		inexum::stl::CreateWithStringLable<inexum::OSP::Serializable, \
			inexum::OSP::SerializableArray<cpp_type> >::g_Creator(\
					inexum::OSP::Serializable::ArrayCode() + std::string(java_type_name)); \
	\
	inexum::OSP::Serializable::CppJavaNamesRegister \
		inexum::OSP::SerializableArray<cpp_type>::gm_namesRegister(\
			std::string("[") + (typeid(cpp_type).name()), \
			std::string("[") + java_type_name); \
	\
	inexum::JLong inexum::OSP::SerializableArray<cpp_type>::serialVersionUID() const \
	{ \
		return(serial_version_uid); \
	}

	
/** Define the serializable array of pointers. The macro should be used for 
  *	user specified classes.
  *
  *	@doc	Example (file java_lang.cpp):
  * 
  *			. serialize_pointer_array("java.lang.Number", java::lang::Number, 0x8d4686cc5ce1152c);
  *
  *	@param java_type_name - a Java type name as a string of the array elements.
  *	@param cpp_type - the C++ type the array elements.
  *	@param serial_version_uid - a serial version uid number as specified in java implementation of the class
  *						'private static final long serialVersionUID' variable should be specified for
  *						any serializable class. More then one class can have the same serialVersionUID. 
  *						Java 2 SDK provides 'serialver' RMI tool that returns a class serialVersionUID.
  *
  *	@see	inexum::OSP::SerializableArray
  *	@see	inexum::OSP::StringLableCreator
  *	@see	serialize
  *	@see	serialize_pointer_array
  *
  *	@author	iNexum Systems Inc.
  *	@version	1.0.0
  */
#define serialize_pointer_array(java_type_name, cpp_type, serial_version_uid) \
	template class inexum::OSP::SerializableTypePointerArray<cpp_type>; \
	\
	template class inexum::stl::CreateWithStringLable<inexum::OSP::Serializable, \
										inexum::OSP::SerializableTypePointerArray<cpp_type> >; \
	\
	inexum::stl::CreateWithStringLable<inexum::OSP::Serializable, \
										inexum::OSP::SerializableTypePointerArray<cpp_type> > \
		inexum::stl::CreateWithStringLable<inexum::OSP::Serializable, \
			inexum::OSP::SerializableTypePointerArray<cpp_type> >::g_Creator(\
				inexum::OSP::Serializable::ArrayCode() + std::string(java_type_name)); \
	\
	inexum::OSP::Serializable::CppJavaNamesRegister \
		inexum::OSP::SerializableTypePointerArray<cpp_type>::gm_namesRegister(\
			std::string("[") + (typeid(cpp_type).name() + inexum::OSP::Serializable::ClassSize()), \
			std::string("[") + java_type_name); \
	\
	inexum::JLong inexum::OSP::SerializableTypePointerArray<cpp_type>::serialVersionUID() const \
	{ \
		return(serial_version_uid); \
	}

#include <inexum/util/Debug.h>

ExternTemplate template class DeclarationSpecifier std::vector<byte>;
ExternTemplate template class DeclarationSpecifier std::vector<wchar_t>;
ExternTemplate template class DeclarationSpecifier std::vector<double>;
ExternTemplate template class DeclarationSpecifier std::vector<float>;
ExternTemplate template class DeclarationSpecifier std::vector<int>;
ExternTemplate template class DeclarationSpecifier std::vector<inexum::JLong>;
ExternTemplate template class DeclarationSpecifier std::vector<short>;
ExternTemplate template class DeclarationSpecifier std::vector<bool>;
ExternTemplate template class DeclarationSpecifier std::vector<std::string>;

#ifdef iNxmDebug
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<bool>;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<inexum::JLong>;

	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<std::vector<bool> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<std::vector<byte> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<std::vector<wchar_t> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<std::vector<double> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<std::vector<float> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<std::vector<int> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<std::vector<inexum::JLong> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<std::vector<short> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<std::vector<std::string> >;
	ExternTemplate template class DeclarationSpecifier inexum::util::DebugClass<inexum::stl::VectorPtr<std::string> >;
#endif	// iNxmDebug

#endif	// java_serializable_h

/** @name	JNOC++ Serialize Example
  * @memo	JNOC++ (Java Network Object Communication ++).
  *
  *	@doc
  *	JNOC++ is compatible with JOS (Java Object Serialization) version 5. 
  *	According to JOS version 5 all non static Java class members will be sent 
  *	via Java object stream.
  *
  *	@doc	MyClass.java:
  *			.public class MyClass implements Serializable {
  *
  *			..	private MyAnotherClass			m_another;
  *
  *			..	protected Integer[]				m_ints;
  *
  *			..	private int[]					m_array;
  *
  *			..	private	Object[]				m_objects;
  *
  *			... ...
  *
  *			..	private static final long serialVersionUID = 0;
  *
  *			.};
  *
  *	JNOC++ does not provide special support for Java's base class java.lang.Object.
  *	Rather uses void* to reference any JNOC++ serialize-able class; or the C++
  *	classes do not have to be inherited from any class that corresponds to 
  *	java.lang.Object class.
  *
  *	Corresponding C++ class, JNOC++ serialize-able, can have a subset of 
  *	corresponding Java class members. Also, it is allowed to have additional C++
  *	class members, like m_memberJustInCpp bellow.
  *
  *	The name of a C++ class or a member does not have to be the same as Java
  *	class or Java member name, respectively. 
  *
  *	The accessibility of a member within the class does not have to be the same,
  *	e.g. bellow, class member m_array is private in Java and protected in C++,
  *	while the member m_ints is protected in Java and corresponding m_pInts is
  *	private in C++.
  *
  *	@doc	MyCppClass.h:
  *
  *			.class MyCppClass {
  *
  *			..	serialize(MyClass);
  *
  *			..	AnotherClass			m_another;
  *
  *			..	std::vector<java::lang::Integer*>*	m_pInts;
  *
  *			..	std::vector<void*>		m_objects;
  *	
  *			..	bool					m_memberJustInCpp;
  *
  *			.protected:
  *
  *			..	std::vector<int>		m_array;
  *
  *			... ...
  *
  *			.};
  *
  *
  *	@doc	MyCppClass.cpp:
  * 
  *		.serialize_begin("com.myPackage.MyClass", MyCppClass, "", 0)
  *
  * 		..	serialize_by_value("com.myPackage.MyAnotherClass", "m_another", m_another);
  *
  * 		..	serialize_pointer("[java.lang.Integer", "m_ints", m_pInts);
  *
  * 		..	serialize_by_value("[java.lang.Object", "m_objects", m_objects);
  *
  * 		..	serialize_by_value("[I", "m_array", m_array);
  *
  * 		.serialize_end
  *
  *	All Java arrays in JNOC++ are supported only with the use of std::vector 
  *	and inexum::stl::VectorPtr classes. The java.lang.Object array is supported by  
  *	JNOC++ through the use of std::vector<void*>. So, in a way JNOC++ treats
  *	java.lang.Object reference as a void pointer in C++.
  *
  * @see	inexum::OSP::Serialize
  * @see	serialize
  * @see	serialize_begin
  * @see	serialize_by_value
  * @see	serialize_pointer
  * @see	serialize_end
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
