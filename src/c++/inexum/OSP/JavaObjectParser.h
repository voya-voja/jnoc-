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
 * File:		JavaObjectParser.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					020515	nmv			create
 *----------------------------------------------------------------------------*/

#pragma warning(disable:4786)

#ifndef inexum_OSP_JavaObjectParser_h
#define inexum_OSP_JavaObjectParser_h

#include <iostream.h>
#include <vector>
#include <stack>
#include <memory>

#include <inexum/util/Debug.h>
#include <inexum/Throwable.h>
#include "javaObjParser.h"
#include <inexum/definitions.h>


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
		class Entity;
		class Class;
		class Object;
		class Value;

		/** A Java object parser encapsulates the parsing of Java object stream.
		  * It provides the access to a object symbol sent using Java object serialization,
		  * if the stream has been parsed without error(s).
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class JavaObjectParser
		{
		public:
			/** @doc The states of a JavaObjectParser when reading the object 
			  * stream:
			  *
			  *		k_ReadBoolean,
			  *		k_ReadByte, 
			  *		k_ReadChar,	
			  *		k_ReadShort,
			  *		k_ReadInt,	
			  *		k_ReadLong,	
			  *		k_ReadFloat,
			  *		k_ReadDouble,
			  *		k_ReadString,
			  *		k_ReturnByte
			  */
			enum State 
			{
				k_ReadBoolean,	// 0
				k_ReadByte, 	// 1
				k_ReadChar,		// 2
				k_ReadShort,	// 3
				k_ReadInt,		// 4
				k_ReadLong,		// 5
				k_ReadFloat,	// 6
				k_ReadDouble,	// 7
				k_ReadString,	// 8
				k_ReturnByte	// 9
			};

			/** Overloaded constructor:
			  *
			  * @param input - the input object stream
			  */
			JavaObjectParser(istream& input);

			/// Destructor
			~JavaObjectParser();

			/** Runs the parser. At the end of successful run the parser refers to
			  * a symbol representing the object sent through the stream.
			  */
			void run();

			/** The symbol of a paresed object loaded with parsed values.
			  *
			  * @return a reference to the parsed object symbol
			  */
			Object* object() { return(m_pFirstObject); }

			/** The parsers InsertNoToken token.
			  *
			  * @return a value of InsertNoToken token.
			  */
			static int InsertNoToken() { return(g_insertNoToken); }

			/// Java object serialization base handle 0x007e0000
			static const unsigned	c_baseWireHandle;

			/// Reset the parser state.
			void reset();

		protected:
			/// The stack of entities
			typedef std::stack<Entity*>		EntityStack;

			/// The list of referenced entities
			typedef std::vector<Entity*>	EntityVector;

			friend int inexum::OSP::yylex (YYSTYPE* yylval, void* pParser);
			friend int inexum::OSP::yyparse(void* pParser);

			/** The Java object stream getter
			  *
			  * @return the input stream
			  */
			istream& getStream() { return(m_input); }

			/** The parser state getter
			  *
			  * @return the state of parser
			  */
			State state() const { return(m_state); }

			/** The parser state setter
			  *
			  * @param aState - a state to move parser to
			  */
			void state(State aState) { m_state = aState; }

			/** Add a class or array description to the stack of entities. If the name
			  * of the class description adds array, othervise adds a class description.
			  * Also, the added entity will be added to the list of referenced entities.
			  *
			  * @param name - the class description name string
			  * @param uid - the unique identifier of teh class description
			  * @param handle - the handle for list of entities
			  */
			void addClassDescription(const std::string& name, JLong uid, int handle);

			/** The class description flags setter
			  *
			  * @param flags - the class description flags
			  */
			void classDescriptionFlags(byte flags);

			/** The super class setter
			  *
			  * @param pClass - the pointer to a super class
			  */
			void superClass(Class* pClass);

			/** Class description end indicator. Remove the entity from the top of 
			  * the parser's stack of entities.
			  *
			  * @return the pointer to the class description removed from the top of
			  *			stack
			  */
			Class* classDescriptionEnd();

			/** Sets the number of members to the class description on the top of 
			  * the entities stack.
			  *
			  * @param count - the number of class members
			  */
			void addMembers(int count);
			
			/** Add a member of Java builtin type to the class description on the top of
			  * the entities stack.
			  *
			  * @param type - a character identifing Java built in type: 
			  *				'B' - byte;
			  *				'C' - char;
			  *				'D' - double;
			  *				'F' - float;
			  *				'I' - integer;
			  *				'J' - long;
			  *				'S' - short;
			  *				'Z' - boolean.
			  *
			  * @param name - the member name string
			  */
			void addMember(char type, const std::string& name);
			
			/** Add a member object to the class description on the top of
			  * the entities stack.
			  *
			  * @param type - a character identifing Java class instance:
			  *				'[' - array;
			  *				'J' - object.
			  *
			  * @param name - the member name string
			  * @param typeName - the member's class name string
			  */
			void addMember(char type, const std::string& name, const std::string& typeName);
			
			/** An object with its class description is created and added to the
			  * list of referenced entities. If it is first object in the stream it will
			  * be added to the top of the stack.
			  *
			  * @param pClass - a pointer to the object's class description.
			  * @param handle - the objects handle number
			  */
			void newObject(Class* pClass, int handle);
			
			/** An array object with its array description is created and added to the
			  * list of referenced entities. If it is first object in the stream it will
			  * be added to the top of the stack.
			  *
			  * @param pClass - a pointer to the object's array description.
			  * @param handle - the objects handle number
			  */
			void newArray(Class* pClass, int handle);

			/// Indicates the begining of the object's data sector.
			void classDataListStart();

			/// Indicates the array description.
			void arrayStart();
			
			/** Sets the number of array elements to the array description from the top
			  * of entity stack.
			  *
			  * @param size - the number of array elements.
			  */
			void elementArrayStart(int size);
			
			/** Sets the value into the object description of Java builtin type
			  *
			  * @param value - the pointer to a holder of the value.
			  */
			void add(Value* value);

			/** Indicates the value is about to be set. Sets the next member of builtin
			  * type to the top of the entity stack.
			  */
			void valueStart();

			/** Indicates the value is about to be set. Removes the member of builtin
			  * type from the top of the entity stack. If the parent object completed
			  * loading of all its members, the end token of that entity will be 
			  * inserted into the parsing stream.
			  */
			void valueEnd();

			/** Sets the string value into the string object description.
			  *
			  * @param newString - the string value.
			  */
			void newString(const std::string& newString);

			/** Sets the string value into the string object description and adds
			  * the reference on a string to the list of referenced entities.
			  *
			  * @param newString - the string value.
			  * @param handle - the handle number of the referenced string
			  */
			void newString(const std::string& newString, int handle);

			/** Positions the parser to read a new string after reading specified 
			  * number of tokens.
			  *
			  * @param size - the string size.
			  * @param tokenCount - the number of tokens upto the string
			  */
			void readString(int size, int tokenCount = 0)
			{
				m_stringSize = size;
				m_tokenCount2string = tokenCount;
			}

			/** Current string size getter.
			  *
			  * @return the string size.
			  */
			int getStringSize() const { return(m_stringSize); }

			/** Return the class description identified by the reference handle.
			  *
			  * @param handle - the reference handle.
			  * @return the class description.
			  */
			Class* classDescReference(int handle);

			/** Return the string identified by the reference handle.
			  *
			  * @param handle - the reference handle.
			  * @return the class description.
			  */
			char* stringReference(int handle) const;

			/** Return the object identified by the reference handle.
			  *
			  * @param handle - the reference handle.
			  * @return the class description.
			  */
			Entity* objectReference(int handle);

			/** Return the next reference handle.
			  *
			  * @return the next reference handle.
			  */
			int newHandle();

			/** Sets the magic number.
			  *
			  * @param magicNo - the Java object serialization magic number
			  */
			void magic(short magicNo) { m_magic = magicNo; }

			/** Sets the version.
			  *
			  * @param version - the Java object serialization version number
			  */
			void version(short version) { m_version = version; }


			/** Sets the serial version unique identifier.
			  *
			  * @param version - the Java object serialization serial version unique identifier
			  */
			void serialVersionUID(long id) { m_serialVersionUID = id; }

			/** Returns the token expected to be inserted into the stream.
			  * 
			  * @return inserted token.
			  */
			int insertToken();

			/// Counts the parser tokens for error reports.
			void incrementTokenCount() { m_tokenCount++; }

			
			/** Token counter getter.
			  * 
			  * @return current token count.
			  */
			int tokenCount() const { return(m_tokenCount); }

			/** Return a final state of yyparse function.
			  * 
			  * @return YYFINAL value.
			  */
			int finalState();

			/** Request to do test for the end of object transmition.
			  * 
			  * @param yystate - a state of a yyparse function.
			  */
			void endTest(int yystate);

			/** Create a new BlockData object and add to the top of the stack.
			  * 
			  * @param size - a data block size.
			  */
			void newBlockData(int size);

			/** Add a new byte into a BlockData object that is on the top of the stack.
			  * 
			  * @param size - a data block size.
			  */
			void addByte(byte aByte);

			/** NOT USED.
			  * 
			  * @param pClass - a class description.
			  */
			void objectNewClassDescription(Class* pClass);

			/** NOT USED.
			  * 
			  * @param pEntity - an entity description.
			  */
			void object(Entity* pEntity);

			/** NOT USED.
			  * 
			  * @param pClass - a class description.
			  */
			void addClass(Class* pClass);

		private:
			void setInsertToken(int token) 
			{
				debug_method(util::DebugMethod(util::Debug::c_serialize, 
						"JavaObjectParser", "setInsertToken", "token: %d", token));
				m_insertedTokens.push(token); 
			}

			int getInsertedToken() 
			{
				int returnToken = g_insertNoToken;
				if(m_insertedTokens.size() > 0)
				{
					returnToken = m_insertedTokens.top();
					m_insertedTokens.pop();
				}
				return(returnToken);
			}

			void resetParserVariables();

			/// The input stream
			istream&		m_input;

			/// The pointer to the object sent through the stream.
			Object*		m_pFirstObject;

			/// The parser's entity stack
			EntityStack		m_parsingEntities; 

			/// The parser's list of referenced entities
			EntityVector	m_referencedEntities;

			/// The stack of tokens to be inserted to the stream.
			std::stack<int>	m_insertedTokens;

			/// The parser's current read state.
			State			m_state;

			short			m_magic;
			short			m_version;
			long			m_serialVersionUID;
			int				m_tokenCount;
			int				m_stringSize;
			int				m_handle;
			int				m_tokenCount2string;

			static const int	g_insertNoToken;
		};

		///
		class ParseException : public Throwable
		{
		};
	}	// namespace OSP
}	// namespace inexum

#endif	// inexum_OSP_JavaObjectParser_h