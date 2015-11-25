/*	File:		UserChkGestaltFunction.c	Contains:	Use as a alternate means of identifying whether a Gestalt selector 				is available.  The CheckGestalt clause requires the scriptor to enter				all valid Gestalt selector results.  This poses a future compatibility				problem in that one would like to simply know that a gestalt selector				exists and not have to worry about matching the result in order to pass				the clause.  This user function simply requires that the scriptor pass in 				the gestalt selector to check for.  A true result is returned if the selector 				is found, false otherwise or if the Gestalt trap was not available.	Written by: Rich Kubota		Copyright:	Copyright � 1988-1999 by Apple Computer, Inc., All Rights Reserved.				You may incorporate this Apple sample source code into your program(s) without				restriction. This Apple sample source code has been provided "AS IS" and the				responsibility for its operation is yours. You are not permitted to redistribute				this Apple sample source code as "Apple sample source code" after having made				changes. If you're going to re-distribute the source, we require that you make				it clear in the source that the code was descended from Apple sample source				code, but that you've made changes.	Change History (most recent first):				8/18/1999	Karl Groethe	Updated for Metrowerks Codewarror Pro 2.1				*/#if 0c -b UserChkGestaltFunction.cLink -ra =resPurgeable -rt infn=1002 -rn -m USERCHKGESTALTFUNCTION -t rsrc -c RSED �		UserChkGestaltFunction.c.o �		"{Libraries}"Interface.o �		-o UserChkGestaltFunction.rsrc#endif#include <Types.h>#include <Traps.h>#include <OSUtils.h>#include <GestaltEqu.h>#include <Patches.h>#include "UserChkGestaltFunction.h"/******************  function prototypes  *********************/short 		NumToolboxTraps(void);TrapType 	GetTrapType(unsigned short theTrap);Boolean 	TrapAvailable(unsigned short theTrap);/**************************************************************/pascal Boolean UserChkGestaltFunction(short targetVRefNum, long blessedID, long selector){#pragma unused (blessedID, targetVRefNum)	OSErr	err;	long	result;		if (TrapAvailable(_Gestalt))		// check whether the Gestalt trap is available	{		err = Gestalt((OSType)selector, &result);	// pass the selector to the Gestalt call		return (err == noErr);		// return result	}	else		return false;				// gestalt not found, return false}/******** The following code is from IM VI *******/short NumToolboxTraps(void){		if (NGetTrapAddress(_InitGraf, ToolTrap) == 		NGetTrapAddress(0xAA6E, ToolTrap))		return(0x200);	else		return(0x400);}#define TrapMask	0x0800TrapType GetTrapType(unsigned short theTrap){	if (theTrap & TrapMask)		return (ToolTrap);	else		return (OSTrap);}Boolean TrapAvailable(unsigned short theTrap){	TrapType	theType;		theType = GetTrapType(theTrap);	if (theType == ToolTrap) {		theTrap &= 0x07FF;		if (theTrap >= NumToolboxTraps())			theTrap = _Unimplemented;	}		return (NGetTrapAddress(theTrap, theType) != 			NGetTrapAddress(_Unimplemented, ToolTrap));}