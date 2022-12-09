#include <string.h>
#include "info.h"
#include <stdlib.h>
#include <pthread.h>

static char* ERRORMSG = NULL;
static short gen_errmsg(ERRORCODE code)
{
  switch (code)
  {
    case E_OTHER:
       ERRORMSG = "An Unexpected, unknown error has occured!";
       break;

    case E_ACCESSFAIL:
       ERRORMSG = "Couldn't access a required file!";
      break;

    case E_READFAIL:
      ERRORMSG = "Couldn't find what's needed in required files"
      break;

    default:
      ERRORMSG = NULL;
      break;
  }

  return code;
}

void getInformation(Information* info)
{ 
  if(gen_errmsg(getMemoryInformation(info->memory))) return;
  if(gen_errmsg(getCPUInformation(info->cpu))) return;
  if(gen_errmsg(getUptime(info->uptime))) return;
}`

void getError(char*buffer)
{
  strcpy(buffer, ERRORMSG);
}

size_t has_failed(void)
{
  if (ERRORMSG == NULL)
    return 0;

  return strlen(ERRORMSG);
}

void printError(void)
{
  if (has_failed())
  fprintf(stderr, "There was an error: %s", ERRORMSG);
}

