#include <stdbool.h>
#include <string.h>
#include <info.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ERRORCODE

// Get memory information using procfs
ERRORCODE getMemoryInformation(memoryInformation* info_struct)
{
  size_t total_memory = 0, available_memory = 0, used_memory = 0;

  // For getting memory information we'll use procfs.
  // Try to open the '/proc/meminfo' in read-only mode.
  FILE mem_info = fopen("/proc/meminfo", "r");

  // If unable to open the file, return an ERRORCODE
  if (mem_info == NULL)
    {
      return 1;
    }

  // Read the line (should only be one) containing the total memory.
  // If the line doesn't exist, return an ERRORCODE
  if(!fscanf (mem_info, "MemTotal:\t%u kB", &total_memory))
  {
    fclose(mem_info);
    return 2;
  }
  
  // Same as above, but for the available memory.
  if(!fscanf (mem_info, "MemAvailable:\t%u kB", &available_memory))
  {
    fclose(mem_info);
    return 2;
  }

  fclose(mem_info); // Close the file as we are finished with it.

  // Calculate the used memory
  used_memory = total_memory - available_memory;

  *info_struct = {
    .used = used_memory,
    .total = total_memory,
    .available = available_memory
  }
  return 0;
}
