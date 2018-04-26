#ifndef _STATE_

#define _STATE_

#include <stddef.h>
#include "directoryItem.h"
#include "directoryBar.h"

struct STATE {
  struct DIRECTORY_BAR* currentDirectory;
  struct DIRECTORY* directoryContents;
};

struct STATE* initState();
void freeState(struct STATE* state);

#endif
