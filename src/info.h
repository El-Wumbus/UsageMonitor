typedef unsigned int ERRORCODE;

enum ERRORTYPE
{
  E_NONE = 0,
  E_ACCESSFAIL = 1,
  E_READFAIL = 2,
  E_OTHER = 3
}

typedef unsigned short int precentage_t;
typedef struct MemoryInformation
{
  // The used memory
  size_t used;

  // The memory available for use
  size_t available;

  // The total memory inculding used and available_memory
  size_t total;
} memoryInformation;

typedef struct CPUInformation
{
  // The usage as a precentage
  precentage_t usage; 

  // The number of actual cores
  unsigned short cores;

  // The number of virtual cores/threads
  unsigned short threads;

  // The model name as a string
  char *model;

  // The current average core frequency in MHz
  unsigned int frequency;
} CPUInformation;

typedef struct UptimeInformation
{
  // The total CPU time 
  unsigned long uptime;

  //The time the CPU is idle
  unsigned long idletime;
} UptimeInformation;

ERRORCODE getMemoryInformation(MemoryInformation* info_struct);
ERRORCODE getCPUUsage(CPUInformation *cpu_info);
ERRORCODE getCPUFrequency(CPUInformation *cpu_info_struct);
ERRORCODE getCPUInformation(CPUInformation *cpu_info_struct);
ERRORCODE getUptime(UptimeInformation *uptime_struct);
