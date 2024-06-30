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
 * File:		simpleMain.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030915	nmv			create
 *----------------------------------------------------------------------------*/
#include <boost/thread/thread.hpp>
#include "exmplsmpl.h"

void main()
{
#ifdef WIN32
	#ifdef _CRTDBG_MAP_ALLOC
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif	// _CRTDBG_MAP_ALLOC
#endif	// WIN32
	try
	{
		debug_mode(Debug::c_app0/*|Debug::c_net|Debug::c_serialize*/);

		// use threads
		boost::thread server(&doServer);
		boost::thread client(&doClient);
		server.join();
		client.join();
	}
	catch(...)
	{
		debug_line(DebugLine(Debug::c_app0, "Exception in simple"));
    }
}
