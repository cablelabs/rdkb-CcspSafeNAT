/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

   -------------------------------------------------------------------

    description:

        This file implementes Port Forwarding rules for TR181 
		Device.NAT.PortForwarding.{i}. objects

    -------------------------------------------------------------------

    environment:

        platform independent

    -------------------------------------------------------------------

    author:

        Murugan Viswanathan (mviswa004c)

    -------------------------------------------------------------------

    revision:

        07/15/2016    initial revision.
******************************************************************************/
   
#include <stdio.h>
#include "ansc_platform.h"



/*
 * InternalPort should be 0 for PortMapping (Non-HS port mapping rule)
 * NOTE: Currently this parameter is not exposed through SafeNAT.
 */
BOOL
SafeNAT_Validate_InternalPort
    (
    	ULONG	uInternalPortValue
    );


/*
 * InternalPort should NOT be 0 for Home Security (HS) port mapping
 * (Must be Non-zero - between 1 and 65536 - for HS port forwarding)
 * NOTE: Currently HS is not exposed through SafeNAT.
 */
BOOL
SafeNAT_Validate_HS_InternalPort
    (
    	ULONG	uInternalPortValue
    );


/*
 * External port range cannot be re-used.
 * ExternalPort & ExternalPortEndRange should not be in the range of existing rule's start and end port range.
 */
BOOL
SafeNAT_Validate_ExternalPort
    (
    		ULONG	uStartExternalPort1,
			ULONG 	uEndExternalPort1,
    		ULONG	uStartExternalPort2,
			ULONG 	uEndExternalPort2
    );


/*
 * Description should not be reused in HS PortMapping or port PortMapping.
 */
BOOL
SafeNAT_Validate_Description
    (
    		char*	pDescriptionValue1,
			char*	pDescriptionValue2
    );


/*
 * InternalClient should be in the "DHCP Pool range" (for Non-HS port mapping)
 */
BOOL
SafeNAT_Validate_InternalClient
    (
    		char*	pInternalClient
    );


/*
 * InternalClient should be in the 172.16.12.xxx range for HS port mapping
 * NOTE: Currently HS is not exposed through SafeNAT.
 */
BOOL
SafeNAT_Validate_HS_InternalClient
    (
    		char*	pInternalClient
    );








