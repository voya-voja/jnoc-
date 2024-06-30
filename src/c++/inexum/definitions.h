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
 * File:		iNexumDefinitions.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					021003	nmv			create
 *----------------------------------------------------------------------------*/
#ifdef _WINDOWS
	 /* libjnocpp.dll or debug version libjnocpp.dll are available for development
	  * of Win32 applications. The Win32 application must be compiled with /MD or
	  * debug version /MDd compiler switch and 'iNexumDll' must be defined.
	  */

	// disable warning 'extern ' : ignored on left of '...'
	#pragma warning (disable : 4091)

	// disable warning '<letter>' : unrecognized character escape sequence
	#pragma warning (disable : 4129)

	// disable warning on extern before template instantiation
	#pragma warning (disable : 4231)

	// disable warning '... ' needs to have dll-interface to be used by clients of '...'
	#pragma warning (disable : 4251)

	// disable warning 'initializing': conversion from 'size_t' to 'byte', possible loss of data
	#pragma warning (disable : 4267)

	// disable warning 'type cast': truncation from 'const void *' to 'unsigned int'
	#pragma warning (disable : 4302)

	// disable warning 'type cast': pointer truncation from 'const void *' to 'unsigned int'
	#pragma warning (disable : 4311)

	// disable warning template class specialization is already instantiated
	#pragma warning (disable : 4660)

	// disable warning on 255 char debug symbols
	#pragma warning (disable : 4786)

	// disable warning '...': '__declspec(dllexport)' and 'extern' are incompatible on an explicit instantiation
	#pragma warning (disable : 4910)


	#ifdef iNexumDll
		#define DeclarationSpecifier	__declspec(dllexport)
		#define ExternTemplate
	#elif defined( iNexumLib ) 		
		#define DeclarationSpecifier
		#define ExternTemplate
	#else
		#if defined( _USRDLL )
			#error WINDOWS dll has to be compiled with 'iNexumDll' defined.
		#endif
		#define DeclarationSpecifier	__declspec(dllimport)
		#define ExternTemplate			extern		
	#endif	// iNexumDll
#else
    #define DeclarationSpecifier
    #define ExternTemplate
#endif // _WINDOWS
