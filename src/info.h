typedef int ERRORCODE;

typedef struct memoryInformation
{
  size_t used;
  size_t available;
  size_t total;
} memoryInformation;

ERRORCODE getMemoryInformation(memoryInformation* info_struct);


