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
 * File:		Simple.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030915	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef simple_java_Simple_h
#define simple_java_Simple_h

#include <inexum/java_serializable.h>
#include <inexum/util/Debug.h>

namespace simple
{
	namespace java
	{
		class Simple 
		{
			serialize(Simple);

			Simple*  mpInstance;
			int     mNo;
    
		public:
			/** Creates a linked list of Simple objects.
			  *
			  * @param number - number of Simple instance to be created as linked list
			  */
			Simple(int number)
				:mpInstance(NULL)
			{
				number--;
				mNo = number;
				if(number > 0)
					mpInstance = new Simple(number);
			}
    
			/** Creates a new instance of Simple */
			Simple() 
				:mNo(0), mpInstance(NULL)
			{
			}

			/// Desctructor
			virtual ~Simple()
			{
				if(mpInstance != NULL)
					delete mpInstance;
			}
		private:
			#ifdef iNxmDebug
				friend inexum::util::DebugClass<Simple>;
			#endif
		};
	}	// namespace java
}	// namespace simple

#endif	// simple_java_Simple_h