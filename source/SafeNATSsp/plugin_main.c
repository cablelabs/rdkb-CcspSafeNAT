/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#include "ansc_platform.h"
#include "ansc_load_library.h"
#include "cosa_plugin_api.h"
#include "plugin_main.h"
#include "cosa_safenat_dml.h"
#include "cosa_safenat_internal.h"

#define THIS_PLUGIN_VERSION          1

COSA_DATAMODEL_SAFENAT* g_pSafeNAT = NULL;

int ANSC_EXPORT_API
COSA_Init
    (
        ULONG                       uMaxVersionSupported, 
        void*                       hCosaPlugInfo         /* PCOSA_PLUGIN_INFO passed in by the caller */
    )
{
	printf("[SafeNAT] %s(uMaxVersionSupported:%u, 0x%x) ENTER \n", __FUNCTION__, uMaxVersionSupported, hCosaPlugInfo);
    PCOSA_PLUGIN_INFO               pPlugInfo  = (PCOSA_PLUGIN_INFO)hCosaPlugInfo;

    if ( uMaxVersionSupported < THIS_PLUGIN_VERSION )
    {
    	printf("[SafeNAT] %s Exit ERROR Version not supported! \n", __FUNCTION__);

      /* this version is not supported */
        return -1;
    }   
    
    pPlugInfo->uPluginVersion       = THIS_PLUGIN_VERSION;
    /* register the back-end apis for the data model */
    printf("[SafeNAT] register the back-end apis for the data model\n");
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "SafeNAT_GetParamBoolValue",  SafeNAT_GetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "SafeNAT_SetParamBoolValue",  SafeNAT_SetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "SafeNAT_GetParamUlongValue",  SafeNAT_GetParamUlongValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "SafeNAT_SetParamUlongValue",  SafeNAT_SetParamUlongValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "SafeNAT_GetParamStringValue",  SafeNAT_GetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "SafeNAT_SetParamStringValue",  SafeNAT_SetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "SafeNAT_Validate",  SafeNAT_Validate);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "SafeNAT_Commit",  SafeNAT_Commit);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "SafeNAT_Rollback",  SafeNAT_Rollback);

    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_GetEntryCount",  X_RDKCENTRAL_PortMapping_GetEntryCount);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_GetEntry",  X_RDKCENTRAL_PortMapping_GetEntry);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_IsUpdated",  X_RDKCENTRAL_PortMapping_IsUpdated);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_Synchronize",  X_RDKCENTRAL_PortMapping_Synchronize);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_AddEntry",  X_RDKCENTRAL_PortMapping_AddEntry);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_DelEntry",  X_RDKCENTRAL_PortMapping_DelEntry);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_GetParamBoolValue",  X_RDKCENTRAL_PortMapping_GetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_SetParamBoolValue",  X_RDKCENTRAL_PortMapping_SetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_GetParamIntValue",  X_RDKCENTRAL_PortMapping_GetParamIntValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_SetParamIntValue",  X_RDKCENTRAL_PortMapping_SetParamIntValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_GetParamUlongValue",  X_RDKCENTRAL_PortMapping_GetParamUlongValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_SetParamUlongValue",  X_RDKCENTRAL_PortMapping_SetParamUlongValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_GetParamStringValue",  X_RDKCENTRAL_PortMapping_GetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_SetParamStringValue",  X_RDKCENTRAL_PortMapping_SetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_Validate",  X_RDKCENTRAL_PortMapping_Validate);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_Commit",  X_RDKCENTRAL_PortMapping_Commit);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDKCENTRAL_PortMapping_Rollback",  X_RDKCENTRAL_PortMapping_Rollback);

    printf("[SafeNAT] COSA_Init() - CosaSafeNATCreate called\n");
    /* Create SafeNAT Object for Settings */
    g_pSafeNAT = (PCOSA_DATAMODEL_SAFENAT)CosaSafeNATCreate();

    if ( g_pSafeNAT )
    {
        // print success
    	   printf("[SafeNAT] COSA_Init() - CosaSafeNATInitialize called\n");
    	  CosaSafeNATInitialize(g_pSafeNAT);
    }
    else
    {
    	printf("[SafeNAT] %s exit ERROR CosaSafeNATCreate returned 0!!!\n", __FUNCTION__);
    }

	printf("[SafeNAT] %s EXIT \n", __FUNCTION__);

    return  0;
}

BOOL ANSC_EXPORT_API
COSA_IsObjectSupported
    (
        char*                        pObjName
    )
{
    
    return TRUE;
}

void ANSC_EXPORT_API
COSA_Unload
    (
        void
    )
{
    /* unload the memory here */
    if ( g_pSafeNAT )
    {
        // print success
        CosaSafeNATRemove(g_pSafeNAT);
    }

    g_pSafeNAT = NULL;
}
