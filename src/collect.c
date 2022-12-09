#include <string.h>
#include "info.h"
#include <stdlib.h>
#include <pthread.h>

static char* ERRORMSG;

static void any_err(ERRORCODE code)
{
  switch (code)
  {
    case 
  }
}

getInformation(Information* info)
{ 
  any_err(getMemoryInformation(info->memory));
}

