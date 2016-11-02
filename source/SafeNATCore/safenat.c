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

