/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/
   
#include <stdio.h>
#include "ansc_platform.h"
#include "safenat.h"

int main(int argc, char* argv[])
{
    printf("###### [SafeNAT] Registering SafeNAT component '%s' with CR ..\n", SAFENAT_COMPONENT_NAME);

    msgBusInit(SAFENAT_COMPONENT_NAME);
       
    printf("###### [SafeNAT] Registered SafeNAT component '%s' with CR ..\n", SAFENAT_COMPONENT_NAME);

    while(1)
    {
        sleep(30);
    }

    printf("###### [SafeNAT] SafeNAT %s EXIT\n", __FUNCTION__ );

    return 0;
}

