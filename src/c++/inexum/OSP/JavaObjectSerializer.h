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
 * File:		JavaObjectSerialization.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef inexum_OSP_JavaObjectSerializer_h
#define inexum_OSP_JavaObjectSerializer_h

#include "JavaObjectParser.h"
#include <stdlib.h>
#include <iostream.h>
#include <map>
#include <inexum/Types.h>
#include <inexum/definitions.h>

// Map of member names to the class member symbols
typedef std::map<std::string, unsigned>	HandleMap;

#ifdef WIN32
	ExternTemplate template class DeclarationSpecifier std::_Tree<HandleMap::key_type, 
																HandleMap::value_type, 
																HandleMap::_Kfn, 
																HandleMap::key_compare, 
																HandleMap::allocator_type>;
	ExternTemplate template class DeclarationSpecifier std::map<std::string, unsigned>;
#endif
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
		class Serializable;
		class JavaBuiltinObjectSerializer;

		/** A Java object serializer encapsulates the serialization of C++ objects
		  *	in the format that can be sent through Java object serialization.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier JavaObjectSerializer
		{
		public:
			class SerializerException {};

			/** Overloaded constructor:
			  *
			  * @param output - the output object stream
			  */
			JavaObjectSerializer(ostream& output);

			/// Destructor
			~JavaObjectSerializer();

			/** Serialize object at provided address as an object of provided class.
			  *
			  * @param className - the Java class name string
			  * @param address - the object's address
			  */
			void run(const std::string& className, const void* address);

			/** Serialize builtin object at provided address as an object of provided type.
			  *
			  * @param typeName - the Java class name string
			  * @param address - the object's address
			  */
			void writeBuiltinObject(const std::string& typeName, const void* address);

			/** Verify if the entity has been serialized.
			  *
			  * @param entityName - the entity name string
			  * @return true if entity has been serialized, otherwise false.
			  */
			bool isSerialized(const std::string& entityName) const;

			/** Retreive the handle to an entity.
			  *
			  * @param entityName - the entity name string
			  * @return the handle to the entity.
			  *	@throws SerializerException if the entity name can not be found.
			  */
			unsigned handle(const std::string& entityName);

			/** Retreive the handle to an entity.
			  *
			  * @param entityAddress - the address of an entity
			  * @return the handle to the entity.
			  *	@throws SerializerException if the entity name can not be found.
			  */
			unsigned handle(unsigned entityAddress);

			/** Create an entity handle.
			  *
			  * @param entityName - the entity name string
			  */
			void newHandle(const std::string& entityName);

			/** Create an entity handle.
			  *
			  * @param entityAddress - the address of an entity
			  */
			void newHandle(unsigned entityAddress);

			/// Write Object Stream header.
			void writeStreamHeader();

			/** Write a byte array to the output object stream.
			  *
			  * @param bytes - the reference to a byte array
			  * @param size - the size of a byte array
			  */
			virtual void write(const byte* bytes, int size);

			/** Write a byte array in reveresed order to the output object stream.
			  *
			  * @param bytes - the reference to a byte array
			  * @param size - the size of a byte array
			  */
			virtual void writeReverse(const byte* bytes, int size);


			/** Write a string to the output object stream.
			  *
			  * @param str - the reference to a string
			  */
			void writeString(const std::string& str);

			/** Verify if the entity has been serialized. If there is a reference
			  *	to the entity the reference will be added to the object stream.
			  *
			  * @param address - the entity address
			  * @return true if entity has been serialized, otherwise false.
			  */
			bool referenced(const void* address);

			/** Verify if the entity has been serialized. If there is a reference
			  *	to the entity the reference will be added to the object stream.
			  *
			  * @param name - the entity name string
			  * @return true if entity has been serialized, otherwise false.
			  */
			bool referenced(const std::string& name);

			/** If there is a reference to the entity the reference will be
			  *	removed from the object stream.
			  *
			  * @param address - the entity address
			  */
			void remove(const void* address);

			/** Write a class description.
			  *
			  * @param name - the Java class name string
			  * @param memberSize - the number of class's members
			  * @param serialVersionUID - the Java serial version unique identifier
			  *								for the class
			  */
			void writeClassDescription(const std::string& name, 
								unsigned short memberSize, 
								JLong serialVersionUID);

			/** Write a class description end.
			  *
			  * @param address - the address of the object
			  * @param superClassName - the name of super class
			  */
			void writeClassDescriptionEnd(const void* address, 
										const std::string& superClassName);

			/** Write a member.
			  *
			  * @param address - the address of a class member
			  * @param type - the type of a member
			  */
			void writeMember(const void* address, const std::string& type);

			/// Java object serialization magic number
			const static unsigned short c_magic;

			/// Java object serialization varsion number
			const static unsigned short c_version;

			/// Write null to the object stream.
			void writeNull();

			/** Return serializer for java builtin object.
			  *
			  * @return java builtin object serializer
			  */
			JavaObjectSerializer& builtinObjectSerializer();

			/// Java object serialization token character for an array
			static byte tcArray();

			/// Send reset tocken character and reset the serializer.
			void reset();

			/// Java object serialization token character for a reference
			const static byte			c_tcReference;

			/// Java object serialization token character for an object
			const static byte			c_tcObject;

			/// Java object serialization token character for a class description
			const static byte			c_tcClassDesription;

			/// Java object serialization token character for a string
			const static byte			c_tcString;

			/// Java object serialization token character for an array
			const static byte			c_tcArray;

			/// Java object serialization token character for a class
			const static byte			c_tcClass;

			/// Java object serialization token character for a data block
			const static byte			c_tcBlockData;

			/// Java object serialization token character for the end of data block
			const static byte			c_tcEndBlockData;

			/// Java object serialization token character for a reset
			const static byte			c_tcReset;

			/// Java object serialization token character for a long block data
			const static byte			c_tcBlockDataLong;

			/// Java object serialization token character for an exception
			const static byte			c_tcException;

			/// Java object serialization token character for null
			const static byte			c_tcNull;

			/// Java object serialization class description flag
			const static byte			c_classDescriptionFlags;

		protected:
			/** Output stream getter.
			  *
			  * @return output stream object
			  */
			ostream&	output(){ return(m_output); };

			/** Override to specify the state of serializer's buffer.
			  *
			  * @return true.
			  */
			virtual bool isEmpty() const { return(true); };

			/// Override to flush serializer's buffer to the output stream.
			virtual void flush() {};

		private:
			/// Pair of a member name and the class member symbol
			typedef HandleMap::value_type			HandlePair;

			///	the map of hadles
			HandleMap	m_handleMap;

			///	the map of hadles
			unsigned	m_NextHandle;

			/// the reference to an output object stream
			ostream&	m_output;

			JavaObjectSerializer*	m_pBuiltinSerializer;
		};
	}	// namespace OSP
}	// namespace inexum
#endif	//	inexum_OSP_JavaObjectSerializer_h