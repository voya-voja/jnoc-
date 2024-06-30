/*******************************************************************************
*  Copyright (C) 1997 - 2002 iNexum Systems Inc.
*  All Rights Reserved
*  This Module contains Proprietary Information of iNexum Systems Inc.,
*
*  The copyright notice above does not evidence any
*  actual or intended publication of such source code.
*******************************************************************************/
/*----------------------------------------------------------------------------*
 *                                                                            *
 * File:		definitions.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					031003	nmv			create
 *----------------------------------------------------------------------------*/
#ifdef WIN32
	 /* libjnocpp.dll or debug version libjnocpp.dll are available for development
	  * of Win32 applications. The Win32 application must be compiled with /MD or
	  * debug version /MDd compiler switch and 'iNexumDll' must be defined.
	  */

	// disable warning on 255 char debug symbols
	#pragma warning (disable : 4786)

	// disable warning on extern before template instantiation
	#pragma warning (disable : 4231)

	// disable warning template class specialization is already instantiated
	#pragma warning (disable : 4660)

	// disable warning '<letter>' : unrecognized character escape sequence
	#pragma warning (disable : 4129)

	// disable warning 'extern ' : ignored on left of '...'
	#pragma warning (disable : 4091)

	#ifdef iNxmJavaDll
		#define jDeclarationSpecifier	__declspec(dllexport)
		#define jExternTemplate
	#elif defined( iNxmJavaLib ) 		
		#define jDeclarationSpecifier
		#define jExternTemplate
	#else
		#if defined( _USRDLL )
			#error Win32 dll has to be compiled with 'iNexumDll' defined.
		#endif
		#define jDeclarationSpecifier	__declspec(dllimport)
		#define jExternTemplate			extern		
	#endif	// iNexumDll
#endif // WIN32
