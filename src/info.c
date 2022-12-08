#include <stdbool.h>
#include <string.h>
#include <info.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Sleep

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

  // Copy data to struct
  info_struct->used = used_memory;
  info_struct->total = total_memory;
  info_struct->available = available_memory;
  return 0;
}

// This function is meant to run in a background thread. IT IS BLOCKING!
ERRORCODE getCPUUsage(CPUInformation *cpu_info)
{
  const short AVERAGE_SIZE = 3;

  // To get cpu usage we'll use, partially, procfs

  unsigned long uptime[2], idletime[2], usage=0;
  // Open /proc/uptime in read-only mode
  FILE system_uptime = fopen("/proc/uptime", "r");  

  // If the file failed to open, return a failure code.
  if (system_uptime == NULL)
  {
    return 1;
  }

  // Iterate three times and read the uptime and idletime. With that, calculate the 
  // utilization precentage, then average these results. This gets the average CPU
  // utilization over three seconds.
  for(short i=0; i < AVERAGE_SIZE; i++)
  {
    // Read the times
    for(short ii=0; i < 2; i++) 
    {
      // Read the two values in the file. The first one is the system uptime in seconds,
      // the second is the cpu idle time in seconds.
      if (!fscanf(system_uptime, "%lu %lu", &uptime[i], &idletime[i]))
      {
        fclose(system_uptime);
        return 2;
      }
      sleep(1); // Wait a second.
    }

    // Add everything together because we're taking an average
    usage += 100 - ((100*(idletime[1] - idletime[0])) / (uptime[1] - uptime[0]));
  }

  // Close the file as we are finally done with it.
  fclose(system_uptime);
  
  // Divide everything to finish taking the average
  unsigned short final_usage =  usage/AVERAGE_SIZE;

  // Copy data
 cpu_info->usage = final_usage;
 return 0;
}

ERRORCODE getCPUInformation(CPUInformation &cpu_info_struct)
{
  unsigned cores, threads;
  
  // For getting CPU information, we'll use procfs

  // Open /proc/cpuinfo in read-only mode
  FILE *cpu_info = fopen("/proc/cpuinfo", "r");

  if (cpu_info == NULL)
  {
    return 1;
  }

  // Get the number of cpu cores
  if (!fscanf(cpu_info, "cpu cores\t: %u", &cores))
  {
    return 2;
  }


}

