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
#ifndef _SAFENAT_H_
#define _SAFENAT_H_

#define SAFENAT_COMPONENT_NAME		"CcspSafeNAT"


#define SAFE_FREE(__x__) if(__x__ != NULL) { free((void*)(__x__)); __x__ = NULL;} else {printf("Trying to free null pointer!!\n");}

//#define SAFENAT_PRINT_CONSOLE

#if defined SAFENAT_PRINT_CONSOLE
#define SAFENAT_PRINT(format, ...)   printf(format, ## __VA_ARGS__); fflush(stdout)
#else
#define SAFENAT_PRINT(format, ...)   CcspTraceInfo((format, ## __VA_ARGS__))
#endif



/**
 * @brief Initializes the Message Bus and registers component with the stack.
 *
 * @param[in] name Component Name.
 * @return status 0 for success and 1 for failure
 */
int msgBusInit(const char *name);


#endif /* _SAFENAT_H_ */
