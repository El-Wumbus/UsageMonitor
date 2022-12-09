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
      
      // get uptime
      UptimeInformation uptime_struct;
      error = getUptime(&uptime_struct);
      if (error)
      {
        return error;
      }

      uptime[i] = uptime_struct.uptime;
      ideltime[i] = uptime_struct.idletime;
      
      sleep(1); // Wait a second.
    }

    // Add everything together because we're taking an average
    usage += 100 - ((100*(idletime[1] - idletime[0])) / (uptime[1] - uptime[0]));
  }

  // Close the file as we are finally done with it.
  fclose(system_uptime);

  // Divide everything to finish taking the average
  unsigned short final_usage = usage/AVERAGE_SIZE;

  // Copy data
 cpu_info->usage = final_usage;
 return 0;
}

ERRORCODE getCPUFrequency(CPUInformation *cpu_info_struct)
{
   // The the ammount of data points to average
  const AVERAGE_LEN = 2;
  float frequency_mhz[AVERAGE_LEN], average_frequency = 0;
  
  // Open the cpu info file in read-only
  FILE *cpu_info = fopen("/proc/cpuinfo", "r");

  if (cpu_info == NULL)
  {
    return 1;
  }

  // Collect the data
  for (int i=0; i < AVERAGE_LEN; i++)
  {
    // average the frequency of all cpus
    float frequency[BUFFERSIZE];
    int frequency_len = 0;  

    // keep collecting the frequencies for all cpus
    for(;fscanf(cpu_info, "cpu MHz\t: %f", &frequency[frequency_len]); frequency_len++;)
    {
      combined_frequency += frequency[frequency_len];
    };


    frequency_mhz[i] += combined_frequency / frequency_len;
    sleep(0.5);
  }
  
  // Average the data
  for (int i=0; i < AVERAGE_LEN; i++)
  {
    average_frequency += frequency_mhz[i];
  }

  average_frequency /= AVERAGE_LEN; 

}

ERRORCODE getCPUInformation(CPUInformation *cpu_info_struct)
{
  unsigned int cores, threads;
  char model[BUFFERSIZE];

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

  // Get the cpu model name
  if (!fscanf(cpu_info, "model name\t: %s"), &model)
  {
    return 2;
  }
  
  // We're done
  fclose(cpu_info);

  cpu_info_struct->cores = cores;
  cpu_info_struct->threads = threads;

  // Copy the string
  strcpy(cpu_info_struct->model, model);
  return 0;
}

ERRORCODE getUptime(UptimeInformation* uptime_struct)
{
  // uptime == system uptime, idletime == cpu time spent doing nothing
  unsigned long uptime, idletime;
  FILE *system_uptime = fopen("/proc/uptime", "r");

  if (system_uptime == NULL)
  {
    return 1;
  }

  // Read two non-negative large numbers, the first is the uptime,
  // the second is the idletime. All measured in seconds.
  if(!fscanf("%lu %lu", &uptime, &idletime))
  {
    fclose(system_uptime);
    return 2;
  }

  // Copy data
  uptime_struct->uptime = uptime;
  uptime_struct->idletime = idletime;
  return 0;
}
