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
 * File:		Simple.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030915	nmv			create
 *----------------------------------------------------------------------------*/
#include "Simple.h"

serialize_begin("simple.java.Simple", simple::java::Simple, "", 0)
	serialize_by_value("I", "mNo", mNo);
	serialize_pointer("simple.java.Simple", "mInstance", mpInstance);
serialize_end

#ifdef iNxmDebug
	template<> void inexum::util::DebugClass<simple::java::Simple>::print()
	{
		output() << "[" << (void*)&object() << "]" << "{" << endl
			<< indent() << "mNo = " << object().mNo  << ";" << endl;
		output() << indent() << "mpInstance = ";
		if(object().mpInstance != NULL)
		{
			DebugClass<simple::java::Simple>(*object().mpInstance).print();
		}
		else
			output() << "[" << (void*)NULL << "]";
		output() << endl << indent() << "}" << endl;
	} 
#endif

