#ifndef _STATE_

#define _STATE_

#include <stddef.h>
#include "directoryItem.h"

struct State {
  char* currentDirectory;
  size_t cdStringLength;
  struct DIRECTORY* directoryContents;
};

struct State initState();
void freeState(struct State* state);

#endif
