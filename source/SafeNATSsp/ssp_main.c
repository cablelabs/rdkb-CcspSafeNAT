/**
* @file ssp_main.c
* 
* @description This file is used to manage the dbus call and stack trace.
*
*/
#ifdef __GNUC__
#ifndef _BUILD_ANDROID
#include <execinfo.h>
#endif
#endif

#include "ssp_global.h"
#include "stdlib.h"
#include "ccsp_dm_api.h"
#include "safenat.h"

/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/
/*None*/

/*----------------------------------------------------------------------------*/
/*                               File scoped variables                              */
/*----------------------------------------------------------------------------*/
char  g_Subsystem[32] = {0};

/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/
static void daemonize(void);


/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/

/**
 * @brief This functionality helps in approaching the bus deamon to create and engage the components.
 */
int  cmd_dispatch(int  command)
{
	printf("[SafeNAT] cmd_dispatch() called with command: \'%c\'\n", command);
    switch ( command )
    {
        case    'e' :

#ifdef _ANSC_LINUX
            printf("[SafeNAT] Connect to bus daemon...\n");

            {
                char                            CName[256];

                if ( g_Subsystem[0] != 0 )
                {
                    _ansc_sprintf(CName, "%s%s", g_Subsystem, CCSP_COMPONENT_ID);
                }
                else
                {
                    _ansc_sprintf(CName, "%s", CCSP_COMPONENT_ID);
                }

                 printf("[SafeNAT] ssp_Mbi_MessageBusEngage() called\n");
		ssp_Mbi_MessageBusEngage
                    ( 
                        CName,
                        CCSP_MSG_BUS_CFG,
                        CCSP_COMPONENT_PATH
                    );
            }
#endif
		printf("[SafeNAT] ssp_create() called\n");
            ssp_create();
		printf("[SafeNAT] ssp_engage() called\n");
            ssp_engage();

            break;

        case    'm':

                AnscPrintComponentMemoryTable(pComponentName);

                break;

        case    't':

                AnscTraceMemoryTable();

                break;

        case    'c':
                
                ssp_cancel();

                break;

        default:
            break;
    }
  	printf("[SafeNAT] cmd_dispatch EXIT \n");

    return 0;
}

/**
 * @brief Bus platform initialization to engage the component to CR(Component Registrar).
 */
int msgBusInit(const char *pComponentName)
{
    BOOL                            bRunAsDaemon       = TRUE;
    int                             cmdChar            = 0;
	
    extern ANSC_HANDLE bus_handle;
    char *subSys            = NULL;  
    DmErr_t    err;

    printf("[SafeNAT] msgBusInit called with %s\n", pComponentName);

    AnscCopyString(g_Subsystem, "eRT.");

    if ( bRunAsDaemon ) 
        daemonize();

    cmd_dispatch('e');

    subSys = NULL;      /* use default sub-system */

    printf("[SafeNAT] Cdm_Init called with componentname: %s\n", pComponentName);
    err = Cdm_Init(bus_handle, subSys, NULL, NULL, pComponentName);
    if (err != CCSP_SUCCESS)
    {
	printf("[SafeNAT] Cdm_Init Failed!!!!\n");
        fprintf(stderr, "Cdm_Init: %s\n", Cdm_StrError(err));
        exit(1);
    }

    system("touch /tmp/safenat_initialized");
    printf("[SafeNAT] msgBusInit - /tmp/safenat_initialized created\n");

    printf("RDK_LOG_WARN, HARV : /tmp/safenat_initialized created\n");
    if ( bRunAsDaemon )
    {
	printf("[SafeNAT] msgBusInit - bRunAsDaemon is true. Return failure!!!\n");
        return 1; //Failure
    }
    else
    {
	printf("[SafeNAT] msgBusInit - bRunAsDaemon is %d\n", bRunAsDaemon);
        while ( cmdChar != 'q' )
        {
            cmdChar = getchar();

            cmd_dispatch(cmdChar);
        }
    }

    printf("[SafeNAT] msgBusInit - Cdm_Term() called\n");
    err = Cdm_Term();
    if (err != CCSP_SUCCESS)
    {
	printf("[SafeNAT] msgBusInit - Cdm_Term() failed!!! exit(1)\n");
    	fprintf(stderr, "Cdm_Term: %s\n", Cdm_StrError(err));
    	exit(1);
    }

    printf("[SafeNAT] msgBusInit - ssp_cancel() called\n");
    ssp_cancel();
printf("[SafeNAT] msgBusInit - EXIT\n");    
return 0; //Success
}

/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/

#if defined(_ANSC_LINUX)

/**
 * @brief daemonize is a continous loop running in the background waiting to cater component requests.
 */
static void daemonize(void) {
	
	switch (fork()) {
	case 0:
		break;
	case -1:
		// Error
		printf("SafeNAT: Error daemonizing (fork)! %d - %s\n", errno, strerror(
				errno));
		exit(0);
		break;
	default:
		_exit(0);
	}

	if (setsid() < 	0) {
		printf("SafeNAT: Error demonizing (setsid)! %d - %s\n", errno, strerror(errno));
		exit(0);
	}


#ifndef  _DEBUG

	fd = open("/dev/null", O_RDONLY);
	if (fd != 0) {
		dup2(fd, 0);
		close(fd);
	}
	fd = open("/dev/null", O_WRONLY);
	if (fd != 1) {
		dup2(fd, 1);
		close(fd);
	}
	fd = open("/dev/null", O_WRONLY);
	if (fd != 2) {
		dup2(fd, 2);
		close(fd);
	}
#endif
}

#endif


