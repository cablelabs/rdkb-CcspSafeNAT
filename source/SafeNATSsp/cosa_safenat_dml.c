/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/
   
#include "ansc_platform.h"
#include "cosa_safenat_dml.h"
#include "cosa_safenat_internal.h"
#include "ssp_global.h"

extern ANSC_HANDLE bus_handle;
extern COSA_DATAMODEL_SAFENAT* 		g_pSafeNAT;

PCOSA_BACKEND_MANAGER_OBJECT 		g_pCosaBEManager;
unsigned int*						g_pSPMapInstList	= NULL;
unsigned int						g_SPMapInstCount 	= 0;
/* CcspPandM component ID and d-bus path */
#define SAFENAT_PROXY_COMPONENT_ID	"eRT.com.cisco.spvtg.ccsp.pam"
#define SAFENAT_PROXY_DBUS_PATH 	"/com/cisco/spvtg/ccsp/pam"

#define SAFENAT_SPMAP_BASE_ADDR 	0x10000


/**************************************************************************************************/

ANSC_STATUS
CosaDmlSafeNATInit
    (
        ANSC_HANDLE                 hThisObject
    )
{
    SAFENAT_PRINT("[SafeNAT]   %s(handle:0x%x) : ENTER \n", __FUNCTION__ , hThisObject);
    ANSC_STATUS                     returnStatus        = ANSC_STATUS_SUCCESS;
    SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : EXIT \n", __FUNCTION__ , hThisObject);

	return returnStatus;
}

/**************************************************************************************************/

BOOL
SafeNAT_GetParamBoolValue
(
    ANSC_HANDLE                 hInsContext,
    char*                       ParamName,
    BOOL*                       pBool
)
{

    SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s') : ENTER \n", __FUNCTION__ , hInsContext, ParamName);

	BOOL ret = FALSE;
	char *parameterNames[1];
	parameterValStruct_t **parameterval = NULL;
	int val_size = 0;

    if (AnscEqualString(ParamName, "X_RDKCENTRAL-COM_EnablePortMapping", TRUE))
	{
		char NATParamName[] = {"Device.NAT.X_Comcast_com_EnablePortMapping"};
		parameterNames[0] = (char*)&NATParamName;

		if(CcspBaseIf_getParameterValues(bus_handle,
				SAFENAT_PROXY_COMPONENT_ID,
				SAFENAT_PROXY_DBUS_PATH,
				parameterNames,
				1,
				&val_size,
				&parameterval) == CCSP_SUCCESS)
		{
			ret = TRUE;

			if(val_size == 1 && parameterval != NULL)
			{
				SAFENAT_PRINT("[SafeNAT]  %s : parameterval[0]->parameterValue = \"%s\"\n", __FUNCTION__ , parameterval[0]->parameterValue);

				if(AnscEqualString(parameterval[0]->parameterValue, "1", TRUE) || AnscEqualString(parameterval[0]->parameterValue, "TRUE", FALSE))
					*pBool = TRUE;
				else
					*pBool = FALSE;
			}
			else
			{
				SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_getParameterValues() parameterval == NULL !! or val_size == %d\n", __FUNCTION__, val_size );
			}

			//caller to CcspBaseIf_getParameterValues() should free parameterval
			SAFE_FREE(parameterval);
		}
		else
		{
			SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_getParameterValues() error !!\n", __FUNCTION__ );
		}
}

    SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s') : EXIT \n", __FUNCTION__ , hInsContext, ParamName);
    return ret;
}

/**************************************************************************************************/

BOOL
SafeNAT_SetParamBoolValue
(
	ANSC_HANDLE                 hInsContext,
	char*                       ParamName,
	BOOL                        bValue
)
{
	BOOL ret = FALSE;
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s') : ENTER \n", __FUNCTION__ , hInsContext, ParamName);

	parameterValStruct_t val = {0};
	char* faultParam = NULL;

	if( AnscEqualString(ParamName, "X_RDKCENTRAL-COM_EnablePortMapping", TRUE))
	{
		SAFENAT_PRINT("[SafeNAT]  %s : SET for X_RDKCENTRAL-COM_EnablePortMapping\n", __FUNCTION__ );

		val.parameterName = "Device.NAT.X_Comcast_com_EnablePortMapping";
		val.type = ccsp_boolean;
		val.parameterValue = bValue ? "true" : "false";

		if(CcspBaseIf_setParameterValues(bus_handle,
										SAFENAT_PROXY_COMPONENT_ID,
										SAFENAT_PROXY_DBUS_PATH,
										0, 0x0,   /* session id and write id */
										&val,
										1,
										TRUE, /* no commit */
										&faultParam) == CCSP_SUCCESS)
		{
			ret = TRUE;
			SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_setParameterValues('%s') success.\n", __FUNCTION__ , val.parameterName);
		}
		else
		{
			SAFENAT_PRINT("[SafeNAT]  %s : Failed to SetValue for param '%s'\n", __FUNCTION__, faultParam);
			SAFE_FREE(faultParam);
		}

	}

	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s') : EXIT \n", __FUNCTION__ , hInsContext, ParamName);
	return ret;
}

/**************************************************************************************************/

BOOL
SafeNAT_GetParamUlongValue
(
    ANSC_HANDLE                 hInsContext,
    char*                       ParamName,
    ULONG*                      puLong
)
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s') : ENTER \n", __FUNCTION__ , hInsContext, ParamName);

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );
    return FALSE;
}

/**************************************************************************************************/

BOOL
SafeNAT_SetParamUlongValue
(
    ANSC_HANDLE                 hInsContext,
    char*                       ParamName,
    ULONG                       uValue
)
{

	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s') : ENTER \n", __FUNCTION__ , hInsContext, ParamName);
	
    SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );
    return FALSE;
}

/**************************************************************************************************/

BOOL
SafeNAT_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s') : ENTER \n", __FUNCTION__ , hInsContext, ParamName);

    SAFENAT_PRINT("Unsupported parameter '%s'\n", ParamName);

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return FALSE;
}

/**************************************************************************************************/

BOOL
SafeNAT_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pString
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s') : ENTER \n", __FUNCTION__ , hInsContext, ParamName);

    SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return FALSE;
}

/**************************************************************************************************/
/*
*    caller:     owner of this object
*
*   prototype:
*
*        BOOL
*        SafeNAT_Validate
*            (
*                ANSC_HANDLE                 hInsContext,
*                char*                       pReturnParamName,
*                ULONG*                      puLength
*            );
*
*    description:
*
*        This function is called to validate.
*
*    argument:   ANSC_HANDLE                 hInsContext,
*                The instance handle;
*
*                char*                       pReturnParamName,
*                The buffer (128 bytes) of parameter name if there's a validation.
*
*                ULONG*                      puLength
*                The output length of the param name.
*
*    return:     TRUE if there's no validation.
*
**************************************************************************************************/
BOOL
SafeNAT_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : ENTER \n", __FUNCTION__ , hInsContext);
	
	// No validation  (done in NAT)
	BOOL ret = TRUE;

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return ret;
}


/**************************************************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        SafeNAT_Commit
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is called to finally commit all the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**************************************************************************************************/

ULONG
SafeNAT_Commit
    (
        ANSC_HANDLE                 hInsContext
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : ENTER \n", __FUNCTION__ , hInsContext);

    ANSC_STATUS  returnStatus  = ANSC_STATUS_SUCCESS;

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return returnStatus;
}

/**************************************************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        SafeNAT_Rollback
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is called to roll back the update whenever there's a
        validation found.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**************************************************************************************************/

ULONG
SafeNAT_Rollback
    (
        ANSC_HANDLE                 hInsContext
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : ENTER \n", __FUNCTION__ , hInsContext);

	ANSC_STATUS  returnStatus  = ANSC_STATUS_SUCCESS;

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return returnStatus;

}

/*****************************************************************************************
**
** APIs for Object
**
**	X_RDKCENTRAL-COM_PortMapping
**
******************************************************************************************/

ULONG
X_RDKCENTRAL_PortMapping_GetEntryCount
    (
        ANSC_HANDLE					hInsContext
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : ENTER \n", __FUNCTION__ , hInsContext);

	unsigned int 		InstNumCount    = 0;
	unsigned int*		pInstNumList    = NULL;

    if(CcspBaseIf_GetNextLevelInstances
    		(
				bus_handle,
				SAFENAT_PROXY_COMPONENT_ID,
				SAFENAT_PROXY_DBUS_PATH,
				"Device.NAT.PortMapping.",
				&InstNumCount,
				&pInstNumList
			) == CCSP_SUCCESS)
    {
            SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_GetNextLevelInstances() returned total: %u \n", __FUNCTION__ , hInsContext, InstNumCount);
            int i;
            for (i = 0; i < InstNumCount; i++ )
            {
                SAFENAT_PRINT("[SafeNAT] index: %u : instance: %u\n", i, pInstNumList[i]);
            }

        	//if SafePNAT map exists, cleanup before populating.
        	if (g_pSPMapInstList != NULL)
        	{
        		free(g_pSPMapInstList);
        		g_pSPMapInstList = NULL;
        		g_SPMapInstCount = 0;
        	}

            g_pSPMapInstList = pInstNumList;
            g_SPMapInstCount = InstNumCount;
        }
    else
    {
    	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : CcspBaseIf_GetNextLevelInstances() error, return NULL! \n", __FUNCTION__ , hInsContext);
        return 0;
    }

	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : return %u. EXIT \n", __FUNCTION__ , hInsContext, InstNumCount);

    return InstNumCount;

}

/*
ULONG
X_RDKCENTRAL_PortMapping_GetEntryCount2
    (
        ANSC_HANDLE					hInsContext
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : ENTER \n", __FUNCTION__ , hInsContext);

	ULONG count = 0;
	char *parameterNames[1];
	parameterValStruct_t **parameterval = NULL;
	int val_size = 0;

	char NATParamName[] = {"Device.NAT.PortMappingNumberOfEntries"};
	parameterNames[0] = (char*)&NATParamName;

	if(CcspBaseIf_getParameterValues(
			bus_handle,
			SAFENAT_PROXY_COMPONENT_ID,
			SAFENAT_PROXY_DBUS_PATH,
			parameterNames,
			1,
			&val_size,
			&parameterval) == CCSP_SUCCESS)
	{
		if(val_size >= 1 && parameterval != NULL)
		{
			SAFENAT_PRINT("[SafeNAT]  %s : parameterval[0]->parameterValue = \"%s\"\n", __FUNCTION__ , parameterval[0]->parameterValue);

			count = _ansc_atoi(parameterval[0]->parameterValue);

			SAFENAT_PRINT("[SafeNAT]  %s : count = %u\n", __FUNCTION__ , count);
		}
		else
		{
			SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_getParameterValues() parameterval == NULL !! or val_size == %d\n", __FUNCTION__, val_size );
		}

		//caller to CcspBaseIf_getParameterValues() should free parameterval
		SAFE_FREE(parameterval);
	}
	else
	{
		SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_getParameterValues() error !!\n", __FUNCTION__ );
	}

	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : EXIT \n", __FUNCTION__ , hInsContext);

    return count;

}
*/

/**************************************************************************************************/

ANSC_HANDLE
X_RDKCENTRAL_PortMapping_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, nIndex: %u ) : ENTER \n", __FUNCTION__ , hInsContext, nIndex);
	ANSC_HANDLE pSListEntry = NULL;

	if( (nIndex < g_SPMapInstCount) && (pInsNumber != NULL) )
	{
		*pInsNumber = g_pSPMapInstList[nIndex];
		pSListEntry = (ANSC_HANDLE)(SAFENAT_SPMAP_BASE_ADDR + *pInsNumber);
	}

	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, nIndex: %u ) : InstNum: %d, return 0x%x. EXIT \n", __FUNCTION__, hInsContext, nIndex, *pInsNumber, pSListEntry );

    return pSListEntry;

}

/**************************************************************************************************/

BOOL
X_RDKCENTRAL_PortMapping_IsUpdated
    (
        ANSC_HANDLE                 hInsContext
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : ENTER \n", __FUNCTION__ , hInsContext);
	BOOL	bIsUpdated   = TRUE;

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return bIsUpdated;
}

/**************************************************************************************************/

ULONG
X_RDKCENTRAL_PortMapping_Synchronize
    (
        ANSC_HANDLE                 hInsContext
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : ENTER \n", __FUNCTION__ , hInsContext);
    ANSC_STATUS	returnStatus	=	ANSC_STATUS_SUCCESS;

    //Note: Sync is also done in X_RDKCENTRAL_PortMapping_GetEntryCount (to prevent multiple calls to P&M NAT)

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return returnStatus;
}

/**************************************************************************************************/

ANSC_HANDLE
X_RDKCENTRAL_PortMapping_AddEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG*                      pInsNumber
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : ENTER \n", __FUNCTION__ , hInsContext);
	ANSC_HANDLE pSListEntry = NULL;

	if(CcspBaseIf_AddTblRow(
			bus_handle,
			SAFENAT_PROXY_COMPONENT_ID,
			SAFENAT_PROXY_DBUS_PATH,
			0,
			"Device.NAT.PortMapping.",
			(int*)pInsNumber) == CCSP_SUCCESS)
	{
		SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_AddTblRow() SUCCESS. Added index %u\n", __FUNCTION__ , *pInsNumber);

		pSListEntry = (ANSC_HANDLE)(SAFENAT_SPMAP_BASE_ADDR + *pInsNumber);
	}
	else
	{
		SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_AddTblRow() error !!\n", __FUNCTION__ );
	}

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return pSListEntry;
}

/**************************************************************************************************/

ULONG
X_RDKCENTRAL_PortMapping_DelEntry
    (
        ANSC_HANDLE                 hInsContext,
        ANSC_HANDLE                 hInstance
     )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, hInstance: 0x%x ) : ENTER \n", __FUNCTION__ , hInsContext, hInstance);

    ANSC_STATUS	returnStatus	=	ANSC_STATUS_FAILURE;

    ULONG insNum = (ULONG)hInstance - SAFENAT_SPMAP_BASE_ADDR;
    //check if insNum is valid
    int i = 0;
    BOOL bFound = FALSE;
    for (i = 0; i < g_SPMapInstCount; i++)
    {
    	if(g_pSPMapInstList[i] == insNum)
    	{
    		bFound = TRUE;
    		break;
    	}
    }

    if(bFound)
    {
		char NATParamName[64] = {};
		//object name with instance number.
		sprintf(NATParamName, "%s.%u.", "Device.NAT.PortMapping", insNum);

		if( CcspBaseIf_DeleteTblRow(
				bus_handle,
				SAFENAT_PROXY_COMPONENT_ID,
				SAFENAT_PROXY_DBUS_PATH,
				0,
				(char*)NATParamName) == CCSP_SUCCESS )
		{
			SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_DeleteTblRow() SUCCESS. Deleted:'%s'\n", __FUNCTION__ , NATParamName);
			returnStatus	=	ANSC_STATUS_SUCCESS;
		}
		else
		{
			SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_DeleteTblRow() Failed to delete '%s' !!\n", __FUNCTION__, NATParamName );
		}
    }
    else
    {
    	SAFENAT_PRINT("[SafeNAT]  %s : Instance 0x%x not found !!\n", __FUNCTION__, hInstance );
    }

	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, hInstance: 0x%x ) : EXIT \n", __FUNCTION__ , hInsContext, hInstance);
    return returnStatus;
}

/**************************************************************************************************/

BOOL
X_RDKCENTRAL_PortMapping_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s') : ENTER \n", __FUNCTION__ , hInsContext, ParamName);

    BOOL	ret   = TRUE;

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return ret;
}

/**************************************************************************************************/

BOOL
X_RDKCENTRAL_PortMapping_GetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int*                        pInt
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s : ENTER \n", __FUNCTION__ );
    BOOL	ret   = TRUE;

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return ret;
}

/**************************************************************************************************/

BOOL
X_RDKCENTRAL_PortMapping_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      pUlong
    )
{
	BOOL	ret = FALSE;

	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s') : ENTER \n", __FUNCTION__ , hInsContext, ParamName);

	ULONG insNum = (ULONG)hInsContext - SAFENAT_SPMAP_BASE_ADDR;

 	char *parameterNames[1];
	parameterValStruct_t **parameterval = NULL;
	int val_size = 0;
	char NATParamName[64] = {};

	if( AnscEqualString(ParamName, "ExternalPort", TRUE)
		|| AnscEqualString(ParamName, "ExternalPortEndRange", TRUE)
		|| AnscEqualString(ParamName, "Protocol", TRUE)
		|| AnscEqualString(ParamName, "InternalClient", TRUE) )
	{
		sprintf(NATParamName, "%s.%u.%s", "Device.NAT.PortMapping", insNum, ParamName);
		parameterNames[0] = (char*)&NATParamName;
		SAFENAT_PRINT("[SafeNAT]  %s : parameterNames[0]:'%s' \n", __FUNCTION__, parameterNames[0] );

		if(CcspBaseIf_getParameterValues(
				bus_handle,
				SAFENAT_PROXY_COMPONENT_ID,
				SAFENAT_PROXY_DBUS_PATH,
				parameterNames,
				1,
				&val_size,
				&parameterval) == CCSP_SUCCESS)
		{
			if(val_size >= 1 && parameterval != NULL)
			{
				SAFENAT_PRINT("[SafeNAT]  %s : parameterval[0]->parameterValue = \"%s\"\n", __FUNCTION__ , parameterval[0]->parameterValue);

				if( AnscEqualString(ParamName, "ExternalPort", TRUE)
						|| AnscEqualString(ParamName, "ExternalPortEndRange", TRUE))
				{
					*pUlong = _ansc_atoi(parameterval[0]->parameterValue);
					ret = TRUE;
				}
				else if (AnscEqualString(ParamName, "Protocol", TRUE))
				{
					if (AnscEqualString(parameterval[0]->parameterValue, "TCP", TRUE)) *pUlong = 1;
					else if (AnscEqualString(parameterval[0]->parameterValue, "UDP", TRUE)) *pUlong = 2;
					else if (AnscEqualString(parameterval[0]->parameterValue, "BOTH", TRUE)) *pUlong = 3;
					else *pUlong = 0;
					ret = TRUE;
				}
				else if (AnscEqualString(ParamName, "InternalClient", TRUE))
				{
				    struct in_addr addr = {0};
				    char * Address = parameterval[0]->parameterValue;
				    if ( inet_aton(Address, &addr) )
				    {
				        *pUlong = addr.s_addr;
						ret = TRUE;
				    }
				}

				SAFENAT_PRINT("[SafeNAT]  %s : *pUlong = %u\n", __FUNCTION__ , *pUlong);
			}
			else
			{
				SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_getParameterValues() parameterval == NULL !! or val_size == %d\n", __FUNCTION__, val_size );
			}

			//caller to CcspBaseIf_getParameterValues() should free parameterval
			SAFE_FREE(parameterval);
		}
		else
		{
			SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_getParameterValues() error !!\n", __FUNCTION__ );
		}
	}
	else
	{
        SAFENAT_PRINT("[SafeNAT]  %s : Invalid GET Param \"%s\" \n", __FUNCTION__, ParamName);
	}

	SAFENAT_PRINT("[SafeNAT]  %s : ret=%d EXIT \n", __FUNCTION__ , ret);

    return ret;
}

/**************************************************************************************************/

ULONG
X_RDKCENTRAL_PortMapping_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    )
{
	ULONG ret = 1; //1 - fail, 0 - success
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s', pUlSize: %u) : ENTER \n", __FUNCTION__ , hInsContext, ParamName, *pUlSize);
	ULONG insNum = (ULONG)hInsContext - SAFENAT_SPMAP_BASE_ADDR;

 	char *parameterNames[1];
	parameterValStruct_t **parameterval = NULL;
	int val_size = 0;
	char NATParamName[64] = {};

    if( AnscEqualString(ParamName, "Description", TRUE))
    {
		sprintf(NATParamName, "%s.%u.%s", "Device.NAT.PortMapping", insNum, ParamName);
		parameterNames[0] = (char*)&NATParamName;
		SAFENAT_PRINT("[SafeNAT]  %s : parameterNames[0]:'%s' \n", __FUNCTION__, parameterNames[0] );

		if(CcspBaseIf_getParameterValues(
				bus_handle,
				SAFENAT_PROXY_COMPONENT_ID,
				SAFENAT_PROXY_DBUS_PATH,
				parameterNames,
				1,
				&val_size,
				&parameterval) == CCSP_SUCCESS)
		{
			if(val_size >= 1 && parameterval != NULL)
			{
				SAFENAT_PRINT("[SafeNAT]  %s : parameterval[0]->parameterValue = \"%s\"\n", __FUNCTION__ , parameterval[0]->parameterValue);

		        if ( AnscSizeOfString(parameterval[0]->parameterValue) < *pUlSize)
		        {
		            AnscCopyString(pValue, parameterval[0]->parameterValue);
		            ret = 0;
		        }
		        else
		        {
		            *pUlSize = AnscSizeOfString(parameterval[0]->parameterValue)+1;
		          	 SAFENAT_PRINT("[SafeNAT]: %s(handle:0x%x, ParamName:'%s') ERROR Size!\n", __FUNCTION__, hInsContext, ParamName);
		        }
			}
			else
			{
				SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_getParameterValues() parameterval == NULL !! or val_size == %d\n", __FUNCTION__, val_size );
			}

			//caller to CcspBaseIf_getParameterValues() should free parameterval
			SAFE_FREE(parameterval);
		}
		else
		{
			SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_getParameterValues() error !!\n", __FUNCTION__ );
		}
    }

	SAFENAT_PRINT("[SafeNAT]  %s() : return pValue = '%s', ret=%d EXIT\n", __FUNCTION__, pValue, ret );

    return ret;
}

/**************************************************************************************************/

BOOL
X_RDKCENTRAL_PortMapping_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s : ENTER \n", __FUNCTION__ );
    BOOL	ret   = TRUE;

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return ret;
}

/**************************************************************************************************/

BOOL
X_RDKCENTRAL_PortMapping_SetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int                         value
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s : ENTER \n", __FUNCTION__ );
    BOOL	ret   = TRUE;

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return ret;
}

/**************************************************************************************************/

BOOL
X_RDKCENTRAL_PortMapping_SetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG                       uValue
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s', uValue: %u) ENTER\n", __FUNCTION__, hInsContext, ParamName, uValue);
    BOOL	ret   = FALSE;

	parameterValStruct_t val = {0};
	char* faultParam = NULL;

	ULONG insNum = (ULONG)hInsContext - SAFENAT_SPMAP_BASE_ADDR;

    char NATParamName[64] = {};
    sprintf(NATParamName, "%s.%u.%s", "Device.NAT.PortMapping", insNum, ParamName);

    val.parameterName = (char*)NATParamName;
	//val.type = ccsp_unsignedLong;

	char ParamVal[64] = {};

    if( AnscEqualString(ParamName, "ExternalPort", TRUE) || AnscEqualString(ParamName, "ExternalPortEndRange", TRUE))
    {
    	/* Validate ExternalPort and
    	 * and ExternalPortEndRange
    	 */
    	//SafeNAT_Validate_ExternalPort() - Taken care in RDKB stack, skip.

        /* convert to parameterValue string */
    	sprintf(ParamVal, "%u", uValue);
		val.parameterValue = (char*)ParamVal;
		val.type = ccsp_unsignedInt;
    }
    else if( AnscEqualString(ParamName, "Protocol", TRUE))
    {
    	/* convert to parameterValue string */
    	switch(uValue)
    	{
    	case 1:
    		sprintf(ParamVal, "%s", "TCP");
    		break;
    	case 2:
    		sprintf(ParamVal, "%s", "UDP");
    		break;
    	case 3:
    		sprintf(ParamVal, "%s", "BOTH");
    		break;
    	default:
    		SAFENAT_PRINT("[SafeNAT]  : %s(handle:0x%x, '%s', uValue:%u) UnSupported value!!. EXIT.\n", __FUNCTION__, hInsContext, ParamName, uValue);
    		return FALSE;
    	}
    	val.parameterValue = (char*)ParamVal;
    	val.type = ccsp_string;

    }
    else if( AnscEqualString(ParamName, "InternalClient", TRUE))
    {
    	struct in_addr addr = {0};
    	addr.s_addr = uValue;
     	sprintf(ParamVal, "%s", inet_ntoa(addr));

     	/*
     	 * Validate: Internal client should be in the valid range
     	 */
     	if(SafeNAT_Validate_InternalClient((char*)ParamVal) == FALSE)
     	{
     		SAFENAT_PRINT("[SafeNAT]  : %s(handle:0x%x, '%s', uValue:%u) UnSupported value!!. EXIT.\n", __FUNCTION__, hInsContext, ParamName, uValue);
     		return FALSE;
     	}

     	val.parameterValue = (char*)ParamVal;
    	val.type = ccsp_string;
    }
    else
    {
    	SAFENAT_PRINT("[SafeNAT]  : %s(handle:0x%x, '%s', uValue:%u) UnSupported Param!! EXIT\n", __FUNCTION__, hInsContext, ParamName, uValue);
    	return FALSE;
    }

    SAFENAT_PRINT("[SafeNAT]  %s() : calling CcspBaseIf_setParameterValues(Name:'%s', Value:'%s', Type: %d)\n", __FUNCTION__ , val.parameterName, val.parameterValue, val.type);
    /* call SPV to P&M */
    if(CcspBaseIf_setParameterValues(bus_handle,
    		SAFENAT_PROXY_COMPONENT_ID,
			SAFENAT_PROXY_DBUS_PATH,
			0, 0x0,   /* session id and write id */
			&val,
			1,
			TRUE, /* no commit */
			&faultParam) == CCSP_SUCCESS)
	{
		SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_setParameterValues('%s', '%s') success.\n", __FUNCTION__ , val.parameterName, val.parameterValue);
		ret = TRUE;
	}
	else
	{
		SAFENAT_PRINT("[SafeNAT]  %s : Failed to SetValue '%s' for param '%s'\n", __FUNCTION__, val.parameterValue, faultParam);
		SAFE_FREE(faultParam);
	}

	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x, '%s', uValue: %u) ret = %d EXIT\n", __FUNCTION__, hInsContext, ParamName, uValue, ret );

    return ret;
}

/**************************************************************************************************/

BOOL
X_RDKCENTRAL_PortMapping_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pString
    )
{
	SAFENAT_PRINT("[SafeNAT]  : %s(handle:0x%x, '%s', val:'%s') ENTER\n", __FUNCTION__, hInsContext, ParamName, pString);

	BOOL ret = FALSE;
	parameterValStruct_t val = {0};
	char* faultParam = NULL;
	ULONG insNum = (ULONG)hInsContext - SAFENAT_SPMAP_BASE_ADDR;

    if( AnscEqualString(ParamName, "Description", TRUE) )
    {
     	char *parameterNames[1];
    	parameterValStruct_t **parameterval = NULL;
    	int val_size = 0;
    	char ObjName[64] = {};
		sprintf(ObjName, "%s", "Device.NAT.PortMapping.");
		parameterNames[0] = (char*)&ObjName;

    	/* Validate Description: Get all existing parameter values and check each value */
		if(CcspBaseIf_getParameterValues(
    					bus_handle,
    					SAFENAT_PROXY_COMPONENT_ID,
    					SAFENAT_PROXY_DBUS_PATH,
    					parameterNames,
    					1,
    					&val_size,
    					&parameterval) == CCSP_SUCCESS)
    	{
			if(val_size >= 1 && parameterval != NULL)
			{
				BOOL bParamValid = TRUE;
				int i = 0;
				for (i = 0; i < val_size; i++)
				{
					SAFENAT_PRINT("[SafeNAT] : %s = \"%s\"\n", parameterval[i]->parameterName, parameterval[i]->parameterValue);

					if(strstr(parameterval[i]->parameterName, ".Description"))
					{
						if(SafeNAT_Validate_Description(pString, parameterval[i]->parameterValue) == FALSE)
						{
							bParamValid = FALSE;
							break; //Validation failed, return failure.
						}
					}
				}

				//do the set param stuff
				if(bParamValid)
				{
			        /* call SPV to P&M */
			    	char NATParamName[64] = {};
			    	sprintf(NATParamName, "%s.%u.%s", "Device.NAT.PortMapping", insNum, ParamName);

					val.parameterName = (char*)NATParamName;
					val.type = ccsp_string;
					val.parameterValue = pString;

					if(CcspBaseIf_setParameterValues(bus_handle,
								SAFENAT_PROXY_COMPONENT_ID,
								SAFENAT_PROXY_DBUS_PATH,
								0, 0x0,   /* session id and write id */
								&val,
								1,
								TRUE, /* no commit */
								&faultParam) == CCSP_SUCCESS)
					{
						ret = TRUE;
						SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_setParameterValues('%s', '%s') Success.\n", __FUNCTION__ , val.parameterName, val.parameterValue);
					}
					else
					{
						SAFENAT_PRINT("[SafeNAT]  %s : Failed to SetValue '%s' for param '%s'\n", __FUNCTION__, val.parameterValue, faultParam);
						SAFE_FREE(faultParam);
					}
				}
				else
				{
					SAFENAT_PRINT("[SafeNAT]  %s : Param value Invalid !!\n", __FUNCTION__);
				}
			}
			else /* val_size == 0 or parameterval null */
			{
				SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_getParameterValues() parameterval == NULL !! or val_size == %d\n", __FUNCTION__, val_size );
			}

			//caller to CcspBaseIf_getParameterValues() should free parameterval
			SAFE_FREE(parameterval);
    	}
    	else //CcspBaseIf_getParameterValues() failed. Can't get any params - fail
    	{
			SAFENAT_PRINT("[SafeNAT]  %s : CcspBaseIf_getParameterValues() Failed!\n", __FUNCTION__ );
    	}
    }
    else
    {
    	SAFENAT_PRINT("[SafeNAT]  : %s(handle:0x%x, '%s', val:'%s') Param unsupported!\n", __FUNCTION__, hInsContext, ParamName, pString);
    }

 	SAFENAT_PRINT("[SafeNAT]  : %s(handle:0x%x, ParamName:'%s', val:'%s') ret = %d EXIT\n", __FUNCTION__, hInsContext, ParamName, pString, ret);
    return ret;

}

/**************************************************************************************************/

BOOL
X_RDKCENTRAL_PortMapping_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : ENTER \n", __FUNCTION__ , hInsContext);

    BOOL	ret   = TRUE;

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return ret;
}

/**************************************************************************************************/

ULONG
X_RDKCENTRAL_PortMapping_Commit
    (
        ANSC_HANDLE                 hInsContext
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : ENTER \n", __FUNCTION__ , hInsContext);

	ANSC_STATUS		returnStatus  = ANSC_STATUS_SUCCESS;

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return returnStatus;
}

/**************************************************************************************************/

ULONG
X_RDKCENTRAL_PortMapping_Rollback
    (
        ANSC_HANDLE                 hInsContext
    )
{
	SAFENAT_PRINT("[SafeNAT]  %s(handle:0x%x) : ENTER \n", __FUNCTION__ , hInsContext);

	ANSC_STATUS		returnStatus  = ANSC_STATUS_SUCCESS;

	SAFENAT_PRINT("[SafeNAT]  %s : EXIT \n", __FUNCTION__ );

    return returnStatus;
}

/**************************************************************************************************/
/* EOF */
