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
 * File:		Serializable.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 							020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef inexum_OSP_Seralizable_h
#define inexum_OSP_Seralizable_h

#include <inexum/definitions.h>
#include <inexum/Types.h>
#include <inexum/stl/Factory.h>

#include <map>


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
		class Class;
		class JavaObjectSerializer;

		/** The encapsulation of C++ Serializable pattern. Provides support
		  * for initialization of C++ objects with the values received from Java object
		  * stream.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier Serializable
		{
		public:
			/** The functional object that registers names of serializable classes.
			  *
			  * @author		iNexum Systems Inc.
			  * @version	1.0.0
			  */
			class DeclarationSpecifier CppJavaNamesRegister 
			{
			public:
				/// Map of member names to the class member symbols
				typedef std::map<std::string, std::string>	CppJavaNamesMap;
				/// Pair of a member name and the class member symbol
				typedef CppJavaNamesMap::value_type		CppJavaNamesPair;

				/** Overloaded constructor registers the C++ and java class name
				  *
				  *	@param cppName - the C++ class name
				  *	@param javaName - corrsponding Java class name
				  */
				CppJavaNamesRegister(const std::string& cppName, 
										const std::string& javaName);

				/** Provide java class name for a requested C++ class name.
				  *
				  *	@param cppName - the C++ class name
				  *	@return corrsponding Java class name
				  */
				static const std::string& javaName(const std::string& cppName);

			protected:
			private:
				// Provides a registry destruction
				class CppJavaNamesSingleton : public inexum::stl::Singleton<CppJavaNamesSingleton>
				{
				public:
					~CppJavaNamesSingleton();
					CppJavaNamesMap* cppJavaNamesMap();
				private:
					/// The map of serializable java name classes
					static CppJavaNamesMap*	gm_pCppJavaNamesMap;
				};
			};

			/** Remove object from referenced list if object is deleted.
			  *
			  * @author		iNexum Systems Inc.
			  * @version	1.0.0
			  */
			class DeclarationSpecifier ObjectHandler 
			{
			public:
				/// Initialize object address to NULL.
				ObjectHandler() :m_Address(NULL) {};

				/** Overloaded constructor.
				  *
				  *	@param address - the object address
				  *	@param serializer - the serializer used to serialize trhe object
				  */
				ObjectHandler(const void* address, JavaObjectSerializer& serializer)
					:m_Address(address), m_pSerializer(&serializer)
				{};


				/// Remove the object from referenced list.
				~ObjectHandler();

				/** Object's address setter.
				  *
				  *	@param address - the object address
				  *	@param serializer - the serializer used to serialize trhe object
				  */
				void setObject(const void* address, JavaObjectSerializer& serializer) 
				{ 
					m_Address = address; 
					m_pSerializer = &serializer;
				};

			protected:
			private:
				/// the object address
				const void*	m_Address;
				JavaObjectSerializer*	m_pSerializer;
			};

			/// The Serializable destructor.
			virtual ~Serializable() {}

			/** The getter of a void pointer address of the C++ serializable object.
			  *
			  * @return void pointer address of the C++ serializable object.
			  */
			void* object() { return(m_pObject); }

			/** The setter of a void pointer address of the C++ serializable object.
			  *
			  * @param pObject - the void pointer address of a C++ serializable object.
			  */
			virtual void initialize(void* pObject, const Class& aClass ) 
			{
				m_pObject = pObject;
				initializeObject(m_pObject, aClass);
			}

			/** Initialize the C++ serializable object using the provided class 
			  * description.
			  *
			  * @param aClass - the reference to a class description containing 
			  *					the values received from Java object stream.
			  */
			virtual void initialize(const Class& aClass)
			{
				m_pObject = instantiateObject();
				initializeObject(m_pObject, aClass);
			}

			/** Override to serialize the C++ serializable object using the
			  * provided Java object serializer.
			  *
			  * @param address - the object address 
			  *	@param serializer - Java object serializer.
			  */
			virtual void serialize(const void* address, 
									JavaObjectSerializer& serializer) = 0;

			/** A class name setter.
			  *
			  * @param name - the serializable class name string.
			  */
			void className(const std::string& name) { m_className = name; };

			/// The serializable wraps a super class.
			void superClass() { m_isSuperClass = true; }

			/** Verify does serializable wraps a super class..
			  *
			  * @return true if wraps a supr class , otherwise false..
			  */
			bool isSuperClass() { return(m_isSuperClass); }

			/** Override to return appropriate serial version unique identifier.
			  *
			  * @return 0 as a serial version unique identifier.
			  */
			virtual JLong serialVersionUID() const { return(0); }

			/** Java object serialization array code.
			  *
			  * @return '['
			  */
			static const char	ArrayCode();

			/** The size of word 'class'.
			  *
			  * @return 6
			  */
			static const size_t	ClassSize();

		protected:
			/** Overloaded constructor.
			  * 
			  * @param className - the Java class name to be serialized.
			  */
			Serializable(const std::string className) 
				: m_pObject(NULL), m_className(className),
				 m_isSuperClass(false)
			{}

			/** Override to initialize a serializable object.
			  * 
			  * @param pObject - the address of an object to be initialized.
			  * @param aClass - the class description corresponding to the object.
			  */	
			virtual void initializeObject(void* pObject, const Class& aClass) = 0;

			/** Override to instantiate an object of serializable class.
			  * 
			  * @return the void pointer address of a serializable object.
			  */
			virtual void* instantiateObject() = 0;

			/** Object type code getter.
			  * 
			  * @return the Java object type TC_OBJECT.
			  */
			virtual byte objectTypeCode() const;

			/** The class name getter.
			  * 
			  * @return the class name string of serializable object.
			  */
			const std::string& className() const { return(m_className); }

		private:
			/// The class name of serializable object
			std::string	m_className;

			bool	m_isSuperClass;

			///  The C++ serializable object's address
			void*		m_pObject;

			/// Array code '['
			static const char	c_ArrayCode;

			/// size of word 'class' (6)
			static const size_t	c_classSize;

		};

		/** The declatation of Serializable Factory used to create appropriate
		  * instance of Serializable class with attached C++ serializable object
		  * that will be initialized by Serializable object
		  */
		  typedef inexum::stl::Factory<std::string, Serializable>	SerializableFactory;
	}	// namespace OSP
}	// namespace inexum

#endif	// inexum_OSP_Seralizable_h

