/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/
#ifndef  _COSA_SAFENAT_DML_H
#define  _COSA_SAFENAT_DML_H

#include "safenat.h"
#include "safenat_portmapping_rules.h"


/***********************************************************************

Module Init:

***********************************************************************/
ANSC_STATUS
CosaDmlSafeNATInit
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************************

 APIs for TR181 Object Device.SafeNAT. :

***********************************************************************/
BOOL
SafeNAT_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    );

BOOL
SafeNAT_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    );

BOOL
SafeNAT_GetParamUlongValue
    (
		ANSC_HANDLE                 hInsContext,
		char*                       ParamName,
		ULONG*                      puLong
    );

BOOL
SafeNAT_SetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
		ULONG                      uValue
    );

BOOL
SafeNAT_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );

BOOL
SafeNAT_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pString
    );

BOOL
SafeNAT_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    );

ULONG
SafeNAT_Commit
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
SafeNAT_Rollback
    (
        ANSC_HANDLE                 hInsContext
    );


/*****************************************************************************************

 APIs for Object

	X_RDKCENTRAL-COM_PortMapping
	
******************************************************************************************/

ULONG
X_RDKCENTRAL_PortMapping_GetEntryCount
    (
        ANSC_HANDLE					hInsContext
    );

ANSC_HANDLE
X_RDKCENTRAL_PortMapping_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    );

BOOL
X_RDKCENTRAL_PortMapping_IsUpdated
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
X_RDKCENTRAL_PortMapping_Synchronize
    (
        ANSC_HANDLE                 hInsContext
    );

ANSC_HANDLE
X_RDKCENTRAL_PortMapping_AddEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG*                      pInsNumber
    );

ULONG
X_RDKCENTRAL_PortMapping_DelEntry
    (
        ANSC_HANDLE                 hInsContext,
        ANSC_HANDLE                 hInstance
    );

BOOL
X_RDKCENTRAL_PortMapping_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    );

BOOL
X_RDKCENTRAL_PortMapping_GetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int*                        pInt
    );

BOOL
X_RDKCENTRAL_PortMapping_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      pUlong
    );

ULONG
X_RDKCENTRAL_PortMapping_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );

BOOL
X_RDKCENTRAL_PortMapping_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    );

BOOL
X_RDKCENTRAL_PortMapping_SetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int                         value
    );

BOOL
X_RDKCENTRAL_PortMapping_SetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG                       uValuepUlong
    );

BOOL
X_RDKCENTRAL_PortMapping_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pString
    );

BOOL
X_RDKCENTRAL_PortMapping_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    );

ULONG
X_RDKCENTRAL_PortMapping_Commit
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
X_RDKCENTRAL_PortMapping_Rollback
    (
        ANSC_HANDLE                 hInsContext
    );



#endif //_COSA_SAFENAT_DML_H



