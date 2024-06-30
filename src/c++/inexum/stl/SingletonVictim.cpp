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
 * File:		SingletonVictim.cpp
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					980715	nmv			create
 *----------------------------------------------------------------------------*/

#include "SingletonVictim.h"

using namespace inexum::stl;

VectorPtr<SingletonVictim>*	SingletonVictim::gm_pVictims = NULL;

SingletonVictim::SingletonKiller SingletonVictim::SingletonKiller::gm_SingletonKiller;

SingletonVictim::SingletonVictim()
{
	if(gm_pVictims == NULL)
		gm_pVictims = new VectorPtr<SingletonVictim>;
	gm_pVictims->push_back(this);
}

SingletonVictim::SingletonKiller::~SingletonKiller()
{
	if(SingletonVictim::gm_pVictims != NULL)
		delete SingletonVictim::gm_pVictims;
}
