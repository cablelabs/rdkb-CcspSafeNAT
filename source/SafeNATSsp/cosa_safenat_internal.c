/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/

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

