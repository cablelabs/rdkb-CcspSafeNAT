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
/**************************************************************************

    module: cosa_safenat_internal.c

        For COSA Data Model Library Development

    -------------------------------------------------------------------

    description:

        This file implementes back-end apis for the COSA Data Model Library

    -------------------------------------------------------------------

    environment:

        platform independent

**************************************************************************/

#include "cosa_safenat_internal.h"
#include "cosa_safenat_dml.h"

ANSC_HANDLE
CosaSafeNATCreate
    (
        VOID
    )
{
	printf("[SafeNAT] ###### : %s ENTER \n", __FUNCTION__);

    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
	PCOSA_DATAMODEL_SAFENAT       	pMyObject    = (PCOSA_DATAMODEL_SAFENAT)NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PCOSA_DATAMODEL_SAFENAT)AnscAllocateMemory(sizeof(COSA_DATAMODEL_SAFENAT));

    if ( !pMyObject )
    {
    	printf("[SafeNAT] ###### : %s exit ERROR !!\n", __FUNCTION__);
        return  (ANSC_HANDLE)NULL;
    }

    /*
         * Initialize the common variables and functions for a container object.
         */
        pMyObject->Oid               = COSA_DATAMODEL_SAFENAT_OID;
        pMyObject->Create            = CosaSafeNATCreate;
        pMyObject->Remove            = CosaSafeNATRemove;
        pMyObject->Initialize        = CosaSafeNATInitialize;

        pMyObject->Initialize((ANSC_HANDLE)pMyObject);

	printf("[SafeNAT] ###### : %s EXIT \n", __FUNCTION__);

    return  (ANSC_HANDLE)pMyObject;
}


ANSC_STATUS
CosaSafeNATInitialize
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus        = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_SAFENAT       pMyObject           = (PCOSA_DATAMODEL_SAFENAT)hThisObject;
	printf("[SafeNAT] ###### : %s ENTER \n", __FUNCTION__);


    returnStatus = CosaDmlSafeNATInit((ANSC_HANDLE)pMyObject);
    
    if ( returnStatus != ANSC_STATUS_SUCCESS )
    {
    	printf("[SafeNAT] ###### : %s Exit ERROR \n", __FUNCTION__);

        return  returnStatus;
    }
    
	printf("[SafeNAT] ###### : %s EXIT \n", __FUNCTION__);

    return returnStatus;
}


ANSC_STATUS
CosaSafeNATRemove
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_SAFENAT            pMyObject    = (PCOSA_DATAMODEL_SAFENAT)hThisObject;    
	printf("[SafeNAT] ###### : %s ENTER \n", __FUNCTION__);

    /* Remove self */
    AnscFreeMemory((ANSC_HANDLE)pMyObject);
	printf("[SafeNAT] ###### : %s EXIT \n", __FUNCTION__);

	return returnStatus;
}

