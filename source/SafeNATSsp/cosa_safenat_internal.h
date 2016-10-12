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
#ifndef  _COSA_SAFENAT_INTERNAL_H
#define  _COSA_SAFENAT_INTERNAL_H


#include "ansc_platform.h"
#include "ansc_string_util.h"

#define COSA_DATAMODEL_SAFENAT_OID  	50

typedef  ANSC_HANDLE
(*PFN_COSADM_CREATE)
    (
        VOID
    );

typedef  ANSC_STATUS
(*PFN_COSADM_REMOVE)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  ANSC_STATUS
(*PFN_COSADM_INITIALIZE)
    (
        ANSC_HANDLE                 hThisObject
    );


#define  COSA_BASE_CONTENT                                                                  \
    /* start of object class content */                                                     \
    ULONG                           Oid;                                                    \
    PFN_COSADM_CREATE               Create;                                                 \
    PFN_COSADM_REMOVE               Remove;                                                 \
    PFN_COSADM_INITIALIZE           Initialize;                                             \



/*
 * This is the cosa datamodel backend manager which is used to manager all backend object
 */
#define  COSA_BACKEND_MANAGER_CLASS_CONTENT                                                 \
    /* duplication of the base object class content */                                      \
    COSA_BASE_CONTENT                                                                       \
    /* start of NAT object class content */                                                 \
    ANSC_HANDLE                  hNat;                                                      \
    ANSC_HANDLE                  hDiag;                                                     \
    ANSC_HANDLE                  hDhcpv4;                                                   \
    ANSC_HANDLE                  hUsers;                                                    \
    ANSC_HANDLE                  hDeviceInfo;                                               \
    ANSC_HANDLE                  hUserinterface;                                            \
    ANSC_HANDLE                  hEthernet;                                                 \
    ANSC_HANDLE                  hTime;                                                     \
    ANSC_HANDLE                  hMoCA;                                                     \
    ANSC_HANDLE                  hProcStatus;                                               \
    ANSC_HANDLE                  hDdns;                                                     \
    ANSC_HANDLE                  hFirewall;                                                 \
    ANSC_HANDLE                  hSecurity;                                                 \
    ANSC_HANDLE                  hIP;                                                       \
    ANSC_HANDLE                  hHosts;                                                    \
    ANSC_HANDLE                  hDNS;                                                      \
    ANSC_HANDLE                  hRouting;                                                  \
    ANSC_HANDLE                  hBridging;                                                 \
    ANSC_HANDLE                  hUpnp;                                                     \
    ANSC_HANDLE                  hInterfaceStack;                                           \
    ANSC_HANDLE                  hPPP;                                                      \
    ANSC_HANDLE                  hDhcpv6;                                                   \
    ANSC_HANDLE                  hDeviceControl;                                            \
    ANSC_HANDLE                  hIgmp;                                                     \
    ANSC_HANDLE                  hIPv6rd;                                                   \
    ANSC_HANDLE                  hRA;                                                       \
    ANSC_HANDLE                  hNeighdisc;                                                \
    ANSC_HANDLE                  hMld;                                                      \
    ANSC_HANDLE                  hParentalControl;                                          \
    ANSC_HANDLE                  hRLog;                                                     \
    ANSC_HANDLE                  hMultiLan;                                                 \
    ANSC_HANDLE                  hGRE;                                                      \
    ANSC_HANDLE                  hTGRE;                                                     \
    ANSC_HANDLE                  hCGRE;                                                     \
    ANSC_HANDLE                  hHotspot;                                                  \
    ANSC_HANDLE                  hTSIP;                                                     \
    ANSC_HANDLE                  hFileTransfer;                                             \
    ANSC_HANDLE            hCosaPluginInfo;

typedef  struct
_COSA_BACKEND_MANAGER_OBJECT
{
    COSA_BACKEND_MANAGER_CLASS_CONTENT
#ifdef _COSA_SIM_
            ULONG                        has_wifi_slap;
            ULONG                        has_moca_slap;
#endif
}
COSA_BACKEND_MANAGER_OBJECT,  *PCOSA_BACKEND_MANAGER_OBJECT;

extern PCOSA_BACKEND_MANAGER_OBJECT g_pCosaBEManager;


#define  COSA_DML_NAT_CUSTOM                                            \
            BOOLEAN                 X_Comcast_com_EnablePortMapping;    \
            BOOLEAN                 X_Comcast_com_EnableHSPortMapping;  \
            BOOLEAN                 X_Comcast_com_EnableNATMapping;     \


typedef  struct
_COSA_DML_NAT
{
    ULONG                           X_CISCO_COM_TCPTimeout;
    ULONG                           X_CISCO_COM_UDPTimeout;
    ULONG                           X_CISCO_COM_ICMPTimeout;

    COSA_DML_NAT_CUSTOM
}
COSA_DML_NAT, *PCOSA_DML_NAT;

typedef  struct
_COSA_DML_NAT_DMZ
{
    BOOLEAN                         bEnabled;
    char                            RemoteIPStart[40];
    char                            RemoteIPEnd  [40];
    char                            InternalIP   [40];
    char                            InternalMAC  [18];
    char                            IPv6Host     [64];
}
COSA_DML_NAT_DMZ, *PCOSA_DML_NAT_DMZ;



#define  COSA_DATAMODEL_NAT_CLASS_CONTENT                                                   \
    /* duplication of the base object class content */                                                \
    COSA_BASE_CONTENT                                                                       \
    /* start of NAT object class content */                                                        \
    SLIST_HEADER                    NatPMappingList;                                        \
    SLIST_HEADER                    NatPTriggerList;                                        \
    COSA_DML_NAT                    Nat;                                                    \
    COSA_DML_NAT_DMZ                Dmz;                                                    \
    ULONG                           MaxInstanceNumber;                                      \
    ULONG                           ulPtNextInstanceNumber;                                 \
    ULONG                           PreviousVisitTime;                                      \
    UCHAR                           AliasOfPortMapping[64];                                 \
    ANSC_HANDLE                     hIrepFolderNat;                                         \
    ANSC_HANDLE                     hIrepFolderNatPt;                                       \


typedef  struct
_COSA_DATAMODEL_SAFENAT                                               
{
	COSA_DATAMODEL_NAT_CLASS_CONTENT
}
COSA_DATAMODEL_SAFENAT,  *PCOSA_DATAMODEL_SAFENAT;


typedef  struct
_COSA_CONTEXT_SAFEPMAPPING_LINK_OBJECT
{
    SINGLE_LINK_ENTRY                Linkage;
    ANSC_HANDLE                      hContext;
    ANSC_HANDLE                      hParentTable;  /* Back pointer */
    ULONG                            InstanceNumber;
    BOOL                             bNew;
    ANSC_HANDLE                      hPoamIrepUpperFo;
    ANSC_HANDLE                      hPoamIrepFo;
    BOOL                             bFound;
}
COSA_CONTEXT_SAFEPMAPPING_LINK_OBJECT,  *PCOSA_CONTEXT_SAFEPMAPPING_LINK_OBJECT;

/*
    Standard function declaration 
*/
ANSC_HANDLE
CosaSafeNATCreate
    (
        VOID
    );

ANSC_STATUS
CosaSafeNATInitialize
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
CosaSafeNATRemove
    (
        ANSC_HANDLE                 hThisObject
    );
    

#endif 
