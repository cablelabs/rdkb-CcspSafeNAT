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
   
#include "safenat_portmapping_rules.h"

//extern unsigned int* g_pSPMapInstList;
#define SAFENAT_HS_IP_START   "172.16.12."

/*
 * InternalPort should be 0 for PortMapping (Non-HS port mapping rule)
 * NOTE: Currently this parameter is not exposed through SafeNAT.
 */
BOOL
SafeNAT_Validate_InternalPort
    (
    	ULONG	uInternalPortValue
    )
{
	// No validation required since this Parameter is not exposed through SafeNAT TR181 XML.
	// In future if this is exposed through XML, we need validation here.
	if (uInternalPortValue == 0)
		return TRUE;
	else
		return FALSE;
}


/*
 * InternalPort should NOT be 0 for Home Security (HS) port mapping
 * (Must be Non-zero - between 1 and 65536 - for HS port forwarding)
 * NOTE: Currently HS is not exposed through SafeNAT.
 */
BOOL
SafeNAT_Validate_HS_InternalPort
    (
    	ULONG	uInternalPortValue
    )
{
	// No validation required since Home Security is not exposed through SafeNAT TR181 XML.
	// In future if HS is exposed through XML, we need this validation.
	if (uInternalPortValue > 0 && uInternalPortValue <= 0xffff )
		return TRUE;
	else
		return FALSE;
}


/*
 * External port range cannot be re-used.
 * ExternalPort & ExternalPortEndRange should not overlap with the range of existing rule's start and end port.
 */
BOOL
SafeNAT_Validate_ExternalPort
    (
    		ULONG	uStartExternalPort1,
			ULONG 	uEndExternalPort1,
    		ULONG	uStartExternalPort2,
			ULONG 	uEndExternalPort2

    )
{
	if ( (uStartExternalPort1 >= uStartExternalPort2) && (uStartExternalPort1 <= uEndExternalPort2) )
	{
		return FALSE;
	}
	else if ( (uEndExternalPort1 >= uStartExternalPort2) && (uEndExternalPort1 <= uEndExternalPort2) )
	{
		return FALSE;
	}
	else if ( (uStartExternalPort1 < uStartExternalPort2) && (uEndExternalPort1 > uEndExternalPort2) )
	{
		return FALSE;
	}
	else
		return TRUE;

}


/*
 * Description should not be reused in HS PortMapping or port PortMapping.
 */
BOOL
SafeNAT_Validate_Description
    (
    		char*	pDescriptionValue1,
    		char*	pDescriptionValue2
    )
{
	if( AnscEqualString(pDescriptionValue1, pDescriptionValue2, FALSE))
	{
		return FALSE;
	}
	else
		return TRUE;
}


/*
 * InternalClient should be in the "DHCP Pool range"
 * and should not be in the HS Port Mapping address range.
 */
BOOL
SafeNAT_Validate_InternalClient
    (
    		char*	pInternalClient
    )
{
	// should not allow HS range for non-HS port mapping.
	if(strstr(pInternalClient, SAFENAT_HS_IP_START))
		return FALSE;

	// DHCP pool range already taken care in stack.
	return TRUE;
}


/*
 * InternalClient should be in the 172.16.12.xxx range for HS port mapping
 * NOTE: Currently HS is not exposed through SafeNAT.
 */
BOOL
SafeNAT_Validate_HS_InternalClient
    (
    		char*	pInternalClient
    )
{
	// Must allow only address starting with 172.16.12.
	if((int)strstr(pInternalClient, SAFENAT_HS_IP_START) == (int)pInternalClient)
		return TRUE;
	else
		return FALSE;
}

