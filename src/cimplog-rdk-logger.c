/**
 * Copyright 2016 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <rdk_debug.h>

#include "cimplog.h"

#define DEBUG_INI_NAME		"/etc/debug.ini"
#define MAX_BUF_SIZE 1024

//const char *__attribute__((weak)) rdk_logger_module_fetch(void);
const char *rdk_logger_module_fetch(void);
static int init_done = 0;
void __cimplog(const char *module, int level, const char *msg, ...)
{
    static const char *rdk_logger_module = NULL;

    if( !init_done )
    {
        RDK_LOGGER_INIT();
        rdk_logger_module = rdk_logger_module_fetch();
        if( NULL == rdk_logger_module )
        {
            fprintf(stderr, "\nERROR: RDK Logger not integrated for this module : %s !!!\n",module);
            fprintf(stderr, " ERROR: Provide cimplog method \"const char *rdk_logger_module_fetch(void)\" to get log prints !!\n");
	          //exit(1); // Not using RDKLogger is an Error. Return!
        }
        init_done = 1;
    }
#if 0
    if( NULL == rdk_logger_module )
    {
        //if RDK logger module is not defined, simple return - dont print.
        // used when calling module is not interested in log prints
        return;
    }
#endif
    //else print to RDK Logger
    static const rdk_LogLevel _level[] = { RDK_LOG_ERROR, RDK_LOG_INFO, RDK_LOG_DEBUG };
    va_list arg_ptr;
    char buf[MAX_BUF_SIZE];
    int nbytes;

    if (level <= LEVEL_INFO)
    {
        va_start(arg_ptr, msg);
        nbytes = vsnprintf(buf, MAX_BUF_SIZE, msg, arg_ptr);
        va_end(arg_ptr);

        if( nbytes >=  MAX_BUF_SIZE )	
        {
            buf[ MAX_BUF_SIZE - 1 ] = '\0';
        }
        else
        {
            buf[nbytes] = '\0';
        }

        //RDK_LOG(_level[0x3 & level], rdk_logger_module, "%s: %s", module, buf);
        fprintf(stderr, "\n%s()ERROR: No RDK Logger module : %s : buf : !!!\n",__func__,module,buf);
    }

    return;
}

// The below 'weak' linkage should be replaced with strong definition in the module integrating to cimplog
const char *rdk_logger_module_fetch(void)
{
    return NULL;
}


// To be used for additional rdk logging to different file other the primary logging
void __cimplog_rdk_generic(const char *rdk_logger_module, const char *module, int level, const char *msg, ...)
{
    if( !init_done )
    {
        RDK_LOGGER_INIT();
        init_done = 1;
    }
#if 0
    if( NULL == rdk_logger_module )
    {
        //if RDK logger module is not defined, simple return - dont print.
        // used when calling module is not interested in log prints
        return;
    }
#endif
    //else print to RDK Logger
    static const rdk_LogLevel _level[] = { RDK_LOG_ERROR, RDK_LOG_INFO, RDK_LOG_DEBUG };
    va_list arg_ptr;
    char buf[MAX_BUF_SIZE];
    int nbytes;

    if (level <= LEVEL_INFO)
    {
        va_start(arg_ptr, msg);
        nbytes = vsnprintf(buf, MAX_BUF_SIZE, msg, arg_ptr);
        va_end(arg_ptr);

        if( nbytes >=  MAX_BUF_SIZE )	
        {
            buf[ MAX_BUF_SIZE - 1 ] = '\0';
        }
        else
        {
            buf[nbytes] = '\0';
        }
        //RDK_LOG(_level[0x3 & level], rdk_logger_module, "%s: %s", module, buf);
        fprintf(stderr, "\n%s()ERROR: No RDK Logger module : %s : buf : !!!\n",__func__,module,buf);
    }

    return;
}

