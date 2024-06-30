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
 * File:		Debug.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					980715	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef inexum_util_Debug_h
#define inexum_util_Debug_h


#include <stdlib.h>
#include <stdarg.h>
#include <fstream.h>
#include <string>
#include <iostream.h>
#include <time.h>
#include <inexum/definitions.h>
#include <inexum/Types.h>

#ifdef WIN32
	#ifdef _CRTDBG_MAP_ALLOC
		#include <crtdbg.h>
		#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#endif	// _CRTDBG_MAP_ALLOC
#endif	// WIN32

class DeclarationSpecifier ofstream;

/** iNexum classes.
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
namespace inexum
{
	/** Utility namespace.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
	namespace util
	{
#ifdef iNxmDebug
		/** An abstract handler of debug statements. The debug statements will be
		  * captured in 'debug.log' file if the mode of a debug statement has been 
		  * added to the list of debug modes to be filtered. By default the mode is
		  * 'no debug statements'.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DeclarationSpecifier Debug
		{
		public:
			/// Debug modes. 
			enum Mode
			{
				/// no debug statements
				c_non = 0,

				/// basic statements
				c_basic = 1,

				/// network statements
				c_net = 2,

				/// sequrity statements
				c_security = 4,

				/// database statements
				c_db = 8,

				/// transaction statements
				c_transaction = 16,

				/// profile statements
				c_profile = 32,

				/// user interface statements
				c_ui = 64,

				/// serialization statements
				c_serialize = 128, 

				/// io statements
				c_io = 256, 

				/// 7 additional application specific debug modes
				c_app0 = 512, 
				c_app1 = 1024, 
				c_app2 =  2048, 
				c_app3 =  4096, 
				c_app4 =  8192, 
				c_app5 =  16384, 
				c_app6 =  32768,

				/// all/any debug statements
				c_all = 65535
			};

			/** Adds a debug mode to the list of modes to be captured.
			  *
			  * @param mode - the debug mode to be captured
			  */
			static void addMode(int mode) 
			{
				g_mode = (Mode)(g_mode | mode); 
			} 

			/** Active debug modes.
			  *
			  * @return the debug modes that have been captured
			  */
			static Mode getMode() { return(g_mode); }
    
			/** Debug output stream.
			  *
			  * @return debug output stream.
			  */
			static ostream& output() { return(g_log); }

			/// Increase the indent level for all the debug statements recorded in the future.
			static void increaseIndent() { g_indent += '\t'; }

			/// Decrease the indent level for all the debug statements recorded in the future.
			static void decreaseIndent() { g_indent = g_indent.substr(0, g_indent.size() - 1); }

			/** Debug indent level.
			  *
			  * @return the string containing the indent number of tabs.
			  */
			static const std::string& indent() { return(g_indent); }

			/** Record the message in debug log. The mesage would be preceded by pre and 
			  * followed by post messages if the Debug instance has been instantiated with
			  * the messages.
			  *
			  * @param msg - a free format text message
			  * @return debug output stream.
			  */
			ostream& output(const std::string& msg)
			{
				output() << indent() << m_preMessage << " " << msg << " " << m_postMessage << endl;
				return(output());
			}

			/** Record the formated message with its arguments in debug log. The mesage 
			  * would be preceded by pre and followed by post messages if the Debug instance 
			  * has been instantiated with the messages. The syntax of a formated message is 
			  * same as printf() formated message syntax, with additional tag %D that
			  * represents a reference to an instance of Debug specializations.
			  *
			  * @param formatMsg - a format message describing the variable argument list
			  * @param va_list - variable argument list.
			  * @return debug output stream.
			  */
			virtual ostream& output(const char* formatMsg, ...)
			{
				va_list argList;
				va_start(argList, formatMsg);
				print(formatMsg, argList);
				va_end(argList);
				return(output());
			}

			/** Debug statement preceding message.
			  *
			  * @return debug pre message.
			 */
			const std::string& preMessage() const { return(m_preMessage); }

			/** Debug statement post message.
			  *
			  * @return debug post message.
			 */
			const std::string& postMessage() const { return(m_postMessage); }

		protected:
			/** Default constructor would initialize the debug statement in basic mode, 
			  * without pre or post message.
			  *
			  * @param mode - the debug statement mode.
			 */
			Debug (Mode mode = c_basic) : m_mode(mode) {}

			/** Overloaded constructor would initialize the debug statement in basic mode,
			  * without post message
			  *
			  * @param preMessage - the debug statement preceding message.
			  * @param mode - the debug statement mode.
			 */
			Debug (const std::string& preMsg, Mode mode = c_basic) 
			: m_preMessage(preMsg), m_mode(mode)
			{}

			/** Overloaded constructor would initialize the debug statement in basic mode.
			  *
			  * @param preMessage - the debug statement preceding message.
			  * @param postMessage - the debug statement following message.
			  * @param mode - the debug statement mode.
			 */
			Debug (const std::string& preMsg, const std::string& postMsg, 
															Mode mode = c_basic) 
			: m_preMessage(preMsg), m_postMessage(postMsg), m_mode(mode)
			{}


			/** Override to provide the specific behavior when debug specialization 
			  * object is referenced with %D tag and passed in a variable argument 
			  * list to output() or print()  methods.
			  *
			 */
			virtual void print() { output() << "NOT OVERRIDEN!"; };

			/** Record the formated message with its arguments in debug log. The mesage 
			  * would be preceded by pre and followed by post messages if the Debug instance 
			  * has been instantiated with the messages. The syntax of a formated message is 
			  * same as printf() formated message syntax, with additional tag %D that
			  * represents a reference to an instance of Debug specializations.
			  *
			  * This method should be used by specilized classes which provide a method
			  * with variable argument list, like output() method in this class.
			  *
			  *	void method(const char* formatMsg, ...)
			  *
			  *	{
			  *
			  *		va_list argList;
			  *
			  *		va_start(argList, formatMsg);
			  *
			  *		Debug::print(formatMsg, argList);
			  *
			  *		va_end(argList);
			  *
			  *	}
			  *
			  * @param formatMsg - a format message describing the variable argument list
			  * @param argList - variable argument list.
			  */
			virtual void print(const std::string& formatMsg, va_list& argList)
			{
				if((m_mode & g_mode) == 0) return;

				std::string timeStr(time());
				output() << timeStr.substr(0, timeStr.size() - 1) << " "
											<< indent() << preMessage();
				std::string restFormatMsg(formatMsg);
				int position = 0;
				do
				{
					if(restFormatMsg[position] == '%' && restFormatMsg[position + 1] == 'D')
					{
						print(restFormatMsg, position, argList);
						printObject(argList );
						restFormatMsg = restFormatMsg.substr(position + 2);
						position = 0;
					}
				} while(restFormatMsg[position++] != '\0');
				print(restFormatMsg, position, argList );
				output() << postMessage() << endl;
			}

			/** Current time.
			  *
			  * @return a current time as a string.
			 */
			std::string time() const
			{
				time_t now;
				::time(&now);
				return(ctime(&now));
			}

		private:
			/** Write to debug log parts of formated message that do not have '%D'.
			  *
			  * @param formatMsg - a format message describing the variable argument list
			  * @param argList - variable argument list.
			 */
			void print(const std::string& longFormatMsg, int size, va_list& argList)
			{
				char* format = new char[ size + 1 ];
				strncpy(format, longFormatMsg.c_str(), size);
				format[ size ] = '\0';
	//			char* line = new char[_vscprintf((const char *)format, argList) + 1];
				char* line = new char[2048];
				vsprintf(line, format, argList);
				output() << line;
				delete line;
				int position = 0;
				bool symbol = false;
				do
				{
					if(format[position] == '%') symbol = true;
					if(symbol)
					{
						if(format[position + 1] == 'd')
						{
							va_arg(argList, int);
							symbol = false;
						}
						else if(symbol && format[position + 1] == 'c')
						{
							va_arg(argList, char);
							symbol = false;
						}
						else if(symbol && format[position + 1] == 'f')
						{
							va_arg(argList, double);
							symbol = false;
						}
						else if(symbol && format[position + 1] == 'e')
						{
							va_arg(argList, double);
							symbol = false;
						}
						else if(symbol && format[position + 1] == 's')
						{
							va_arg(argList, int);
							symbol = false;
						}
					}
				} while(format[position++] != '\0');
				delete format;
			}

			/** Write to debug log parts of formated message that is referenced by '%D'.
			  *
			  * @param argList - variable argument list positioned at the object.
			 */
			void printObject(va_list& argList)
			{
				Debug& pObject = *(Debug*)va_arg(argList, int);
				pObject.print();
			}

			/// Debug statement preceding message
			std::string	m_preMessage;

			/// Debug statement post message
			std::string	m_postMessage;

			/// Debug statement mode
			Mode		m_mode;

			/// Debug capture modes
			static Mode g_mode; 


			/// Debug log
			static ofstream		g_log;

			/// Current debug statement indent
			static std::string	g_indent;	
		};

		/** Function debug statement. The instance should be created at the begining
		  * of the function, with return object and argument list. At the place of 
		  * instance creation prints debug statement in following format:
		  *
		  *	<function name>([<argument> : <value>[,]]*) 
		  *
		  * At the end of the function prints debug statement in following format:
		  *
		  *	<function name>(return : <value>|"NO return")
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DebugFunction : public Debug
		{
		public:
			/** Overloaded constructor allows definition of debug statement for a function
			  * without arguments and return value.
			  *
			  * @param mode - debug statement mode.
			  * @param functionName - function name string.
			  */
			DebugFunction (int mode, const std::string& functionName) 
				: Debug(functionName + "(", ")", (Debug::Mode)mode), m_retFormat("NO return")
			{
				output("");
				increaseIndent();
			}

			/** Overloaded constructor allows definition of function name, return object
			  * and variable list of arguments for the function. It uses printf() formated 
			  * message, extended for %D referencing to a Debug instance. If the function 
			  * returns an object, the format message has to start (no space) with the 
			  * definition type of the return object and the reference to the return object 
			  * has to be specified first in the variable argument list, e.g.:
			  * 
			  * int myFunction(double amount, MyClass& obj) {
			  *
			  *	int retValue = -1;	// initialize return variable
			  *
			  *	DebugFunction debugStm("myFunction", "%d amount: %5.3f, object: %D", 
			  *					&retValue, amount, &DebugClass<MyCLass>(obj));
			  *
			  *	...
			  *
			  *	return(retValue);
			  *
			  * }
			  *
			  * Only if the debug mode includes c_base, the debug log output will be:
			  *
			  *	...
			  *
			  *	<date time> myFunction(amount: 1.321, object: MyClass{ x: 2 })
			  *
			  *		...
			  *
			  *	<date time> myFunction(return: 0)
			  *
			  *	...
			  *
			  * @param functionName - function name string.
			  * @param formatMsg - printf() format message, extended for %D referencing 
			  *				Debug instance. If function returns a value the format
			  *				message has to start without spaces with the type of the
			  *				return type.
			  * @param ... - variable argument list. If the function has a return value
			  *			the first argument has to be address of the return object.
			  */
			DebugFunction (const std::string& functionName, const char* formatMsg, ...) 
				: Debug(functionName + "(", ")"), m_retFormat("NO return")
			{ 
				va_list argList;
				va_start(argList, formatMsg);

				print(formatMsg, argList);
				va_end(argList);

				increaseIndent();
			}

			/** Overloaded constructor allows definition of function name, return object
			  * and variable list of arguments for the function. It uses printf() formated 
			  * message, extended for %D referencing to a Debug instance. If the function 
			  * returns an object, the format message has to start (no space) with the 
			  * definition type of the return object and the reference to the return object
			  * has to be specified first in the variable argument list, e.g.:
			  * 
				* int myFunction(double amount, MyClass& obj) {
			  *
			  *	int retValue = -1;	// initialize return variable
			  *
			  *	DebugFunction debugStm(Debug::c_net, "myFunction", 
			  *					"%d amount: %5.3f, object: %D", 
			  *					&retValue, amount, &DebugClass<MyCLass>(obj));
			  *
			  *	...
			  *
			  *	return(retValue);
			  *
			  * }
			  *
			  * Only if the debug mode includes c_net, the debug log output will be:
			  *
			  *	...
			  *
			  *	<date time> myFunction(amount: 1.321, object: MyClass{ x: 2 })
			  *
			  *		...
			  *
			  *	<date time> myFunction(return: 0)
			  *
			  *	...
			  *
			  * @param mode - debug statement mode.
			  * @param functionName - function name string.
			  * @param formatMsg - printf() format message, extended for %D referencing 
			  *				Debug instance. If function returns a value the format
			  *				message has to start without spaces with the type of the 
			  *				return type.
			  * @param ... - variable argument list. If the function has a return value
			  *			the first argument has to be address of the return object.
			  */
			DebugFunction (int mode, const std::string& functionName, const char* formatMsg, ...) 
				: Debug(functionName + "(", ")", (Debug::Mode)mode), m_retFormat("NO return")
			{ 
				va_list argList;
				va_start(argList, formatMsg);

				print(formatMsg, argList);
				va_end(argList);

				increaseIndent();
			}

			/// DebugFunction destructor outputs the function's return debug statement.
			~DebugFunction () 
			{ 
				decreaseIndent();

				char retStr[ 2048 ];
				vsprintf(retStr, m_retFormat.c_str(), m_argList);
				output(retStr);
			}

		protected:
			/** Overloaded constructor allows the construction of derived classes that
			  * provide the function name and optionally debug statement mode.
			  *
			  * @param functionName - function name string.
			  * @param mode - debug statement mode.
			  */
			DebugFunction (const std::string& functionName, 
									Debug::Mode mode = Debug::c_basic) 
				: Debug(functionName + "(", ")", mode), m_retFormat("NO return")
			{ 
			}

			/** Debug print method override to modify the format message and variable
			  * argument list, by preserving return object to be printed later.
			  *
			  * @param formatMsg - a format message describing the variable argument list
			  * @param argList - variable argument list.
			  */
			void print(const std::string& formatMsg, va_list& argList)
			{
				Debug::print(format(formatMsg, argList), argList);
			}

			/** Removes the return object reference for the formated message and 
			  * from the variable argument list.
			  *
			  * @param formatMsg - a format message describing the variable argument list
			  * @param argList - variable argument list.
			  */
			std::string format(const std::string& formatMsg, va_list& argList )
			{
				std::string fMsg(formatMsg);
				if(formatMsg[0] == '%')
				{
					m_argList = (va_list)va_arg(argList, int);
					int retEnd = fMsg.find(" ");

					if(retEnd == -1)
					{
						m_retFormat = "return: " + fMsg;
						fMsg = "";
					}
					else
					{
						m_retFormat = "return: " + fMsg.substr(0, retEnd);

						fMsg = fMsg.substr(retEnd + 1);
					}
				}
				return(fMsg);
			}

		private:
			/// A varaible argument list referencing the return object
			va_list		m_argList;
			
			/// The format message describing the return object
			std::string	m_retFormat;
		};

		/** Class method debug statement. The instance should be created at the 
		  * begining of the method, with return object and argument list. At the 
		  * place of instance creation prints debug statement in following format:
		  *
		  *	<class name>::<method name>([<argument> : <value>[,]]*) 
		  *
		  * At the end of the function prints debug statement in following format:
		  *
		  *	<class name>::<method name>(return : <value>|"NO return")
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class DebugMethod : public DebugFunction
		{
		public:
			/** Overloaded constructor allows definition of debug statement for a class
			  * method without arguments and return value.
			  *
			  * @param mode - debug statement mode.
			  * @param className - class name string.
			  * @param methodName - method name string.
			  */
			DebugMethod(int mode, const std::string& className, 
							const std::string& methodName)
			: DebugFunction(className + "::" + methodName, (Debug::Mode)mode)
			{
				output("");
				increaseIndent();
			}

			/** Overloaded constructor allows definition of class and method name, return 
			  * object and variable list of arguments for the method. It uses printf() 
			  * formated message, extended for %D referencing to a Debug instance. If the 
			  * function returns an object, the format message has to start (without space) 
			  * with the definition type of the return object and the reference to the 
			  * return object has to be specified first in the variable argument list, e.g.:
			  * 
			  * int MyClass::myMethod(double amount, MyClass2& obj) {
			  *
			  *	int retValue = -1;	// initialize return variable
			  *
			  *	DebugFunction debugStm("MyClass", "myMethod", 
			  *					"%d amount: %5.3f, object: %D", 
			  *					&retValue, amount, &DebugClass<MyCLass2>(obj));
			  *
			  *	...
			  *
			  *	return(retValue);
			  *
			  * }
			  *
			  * Only if the debug mode includes c_base, the debug log output will be:
			  *
			  *	...
			  *
			  *	<date time> MyClass::myMethod(amount: 1.321, object: MyClass{ x: 2 })
			  *
			  *		...
			  *
			  *	<date time> MyClass::myMethod(return: 0)
			  *
			  *	...
			  *
			  * @param className - class name string.
			  * @param methodName - method name string.
			  * @param formatMsg - printf() format message, extended for %D referencing 
			  *				Debug instance. If function returns a value the format 
			  *				message has to start without spaces with the type of the 
			  *				return type.
			  * @param ... - variable argument list. If the function has a return value
			  *			the first argument has to be address of the return object.
			  */
			DebugMethod (const std::string& className, 
							const std::string& methodName, 
							const char* formatMsg, ...) 
				: DebugFunction(className + "::" + methodName)
			{ 
				va_list argList;
				va_start(argList, formatMsg);

				print(formatMsg, argList);
				va_end(argList);

				increaseIndent();
			}

			/** Overloaded constructor allows definition of class and method name, return 
			  * object and variable list of arguments for the method. It uses printf() 
			  * formated message, extended for %D referencing to a Debug instance. If the 
			  * function returns an object, the format message has to start (without space)
			  * with the definition type of the return object and the reference to the 
			  * return object has to be specified first in the variable argument list, e.g.:
			  * 
			  * int MyClass::myMethod(double amount, MyClass2& obj) {
			  *
			  *	int retValue = -1;	// initialize return variable
			  *
			  *	DebugFunction debugStm(Debug::c_ui, "MyClass", "myMethod", 
			  *					"%d amount: %5.3f, object: %D", 
			  *					&retValue, amount, &DebugClass<MyCLass2>(obj));
			  *
			  *	...
			  *
			  *	return(retValue);
			  *
			  * }
			  *
			  * Only if the debug mode includes c_ui, the debug log output will be:
			  *
			  *	...
			  *
			  *	<date time> MyClass::myMethod(amount: 1.321, object: MyClass{ x: 2 })
			  *
			  *		...
			  *
			  *	<date time> MyClass::myMethod(return: 0)
			  *
			  *	...
			  *
			  * @param mode - debug statement mode.
			  * @param className - class name string.
			  * @param methodName - method name string.
			  * @param formatMsg - printf() format message, extended for %D referencing 
			  *				Debug instance. If function returns a value the format 
			  *				message has to start without spaces with the type of the 
			  *				return type.
			  * @param ... - variable argument list. If the function has a return value
			  *			the first argument has to be address of the return object.
			  */
			DebugMethod (int mode, const std::string& className, 
							const std::string& methodName, 
							const char* formatMsg, ...) 
				: DebugFunction(className + "::" + methodName, (Debug::Mode)mode)
			{ 
				va_list argList;
				va_start(argList, formatMsg);

				print(formatMsg, argList);
				va_end(argList);

				increaseIndent();
			}

		protected:
		private:
		};

		/** Debug line statement. At the place of instance creation prints
		  * free fromat debug statement.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		 */
		class DebugLine : public Debug
		{
		public:
			/** Overloaded constructor allows definition of free format message with a variable 
			  * list of arguments for the method. It uses printf() formated message, extended 
			  * for %D referencing to a Debug instance. 
			  * 
				* int MyClass::myMethod(double amount, MyClass2& obj) {
			  *
			  *	...
			  *
			  *	DebugLine("Local varaible amount: %5.3f sent to object: %D", 
			  *							amount, &DebugClass<MyCLass2>(obj));
			  *
			  *	...
			  *
			  * }
			  *
			  * Only if the debug mode includes c_base, the debug log output will be:
			  *
			  *	<date time> Local varaible amount: 1.321, object: MyClass{ x: 2 }
			  *
			  * @param formatMsg - printf() format message, extended for %D referencing 
			  *				Debug instance. 
			  * @param ... - variable argument list. 
			  */
			DebugLine (const char* formatMsg, ...) 
			{ 
				va_list argList;
				va_start(argList, formatMsg);

				print(formatMsg, argList);
				va_end(argList);
			}

			/** Overloaded constructor allows definition of free format message with a variable 
			  * list of arguments for the method. It uses printf() formated message, extended 
			  * for %D referencing to a Debug instance. 
			  * 
				* int MyClass::myMethod(double amount, MyClass2& obj) {
			  *
			  *	...
			  *
			  *	DebugLine(Debug::c_db, "Local varaible amount: %5.3f sent to object: %D", 
			  *							amount, &DebugClass<MyCLass2>(obj));
			  *
			  *	...
			  *
			  * }
			  *
			  * Only if the debug mode includes c_db, the debug log output will be:
			  *
			  *	<date time> Local varaible amount: 1.321, object: MyClass{ x: 2 }
			  *
			  * @param mode - debug statement mode.
			  * @param formatMsg - printf() format message, extended for %D referencing 
			  *				Debug instance. 
			  * @param ... - variable argument list. 
			  */
			DebugLine (int mode, const char* formatMsg, ...) 
			:Debug((Debug::Mode)mode)
			{ 
				va_list argList;
				va_start(argList, formatMsg);

				print(formatMsg, argList);
				va_end(argList);
			}

		protected:
		private:
		};

		/** Class debug statement. It allows creation of a debug statement
		  * that would accept an object of any class. The specialization of
		  * print method, allows implememntation of a debug signature of
		  * any class.
		  *
		  * @param _CLASS - debug class specialization will allow any object
		  *					to be passed to a debug statement referenced by %D.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		 */
		template<class _Class>
		class DebugClass : public Debug
		{
		public:
			/** Overloaded constructor creates debug wrapper around an
			  * object.
			  *
			  * @param object - the source of debug information.
			  */
			DebugClass(const _Class& object) 
				: m_object(object) 
			{ 
				increaseIndent();
			}

			/** Overloaded constructor creates debug wrapper around an
			  * object.
			  *
			  * @param mode - the debug statement mode.
			  * @param object - the source of debug information.
			  */
			DebugClass(Debug::Mode mode, const _Class& object) 
				: Debug(mode), m_object(object) 
			{ 
				increaseIndent();
			}

			/// Destructor
			~DebugClass()
			{
				decreaseIndent();
			}

			/** Specialize print method for the instantiation of _Class parameter
			  *	providing appropriate dubug information for an object of _Class.
			  */
			virtual void print() 
			{ 
				output() 
						<< "'warning D0001: No DebugClass<object class>::print()"
						<< " method for [object@" 
						<< &m_object << "]!'"; 
			}

			/** Object getter.
			  *
			  * @return the wrapped object of _Class type.
			  */
			const _Class& object() const { return(m_object); };

		protected:
		private:
			/// the wrapped object reference
			const _Class& m_object;
		};

		ExternTemplate std::string DeclarationSpecifier hexadecimal(const byte* bytes, int size, bool number = true);

#endif		//iNxmDebug
	}	// namespace util
}	// namespace inexum

#ifdef iNxmDebug

	/** Set up debug mode if iNxmDebug has been defined.
	  *
	  *	@param _mode - a debug modes to be captured.
	  */
#define debug_mode(_mode)	inexum::util::Debug::addMode(_mode)

	/** Debug line statement if iNxmDebug has been defined.
	  *
	  *	debug_line(DebugLine("Object: %D", 
	  *							&DebugClass<MyClass>(obj)));
	  *
	  *	@param _line - a debug statement to be loged at that point
	  */
#define debug_line(_line)			_line

	/** Debug function statement if iNxmDebug has been defined.
	  *
	  *	debug_function(DebugFunction("Object: %D", 
	  *							&DebugClass<MyClass>(obj)));
	  *
	  *	@param _object - a debug function object statement to be loged at
	  *						the begining and at the end of the function.
	  */
#define debug_function(_object) inexum::util::Debug& debug = _object

	/** Debug method statement if iNxmDebug has been defined.
	  *
	  *	debug_method(DebugMethod("Object: %D", 
	  *							&DebugClass<MyClass>(obj)));
	  *
	  *	@param _object - a debug method object statement to be loged at
	  *						the begining and at the end of the function.
	  */
#define debug_method(_object)	inexum::util::Debug& debug = _object

#else
	#define debug_mode(_mode)

	#define debug_line(_line)

	#define debug_function(_object)

	#define debug_method(_object)
#endif	// iNxmDebug

#endif	// inexum_util_Debug_h
