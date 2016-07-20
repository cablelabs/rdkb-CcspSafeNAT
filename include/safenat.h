/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/

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
