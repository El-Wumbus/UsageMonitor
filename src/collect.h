#include "info.h";

typedef struct Information
{
  // The memory information
  MemoryInformation* memory;
  
  // The CPU information
  CPUInformation* cpu;

  // The uptime information
  UptimeInformation* uptime;
} Information;
