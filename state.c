#include "state.h"
#include <stdlib.h>
#include <stdio.h>


char stateInitted = 0;

struct STATE* initState() {
  if (stateInitted){
    printf("Warning: State has already been initialized\n");
  }
  char* cwd = getcwd(NULL, 0);
  currentDirectoryStringSize = strlen(cwd);
  currentDirectoryBufferSize = currentDirectoryStringSize;
  struct STATE* newState = malloc(sizeof(struct STATE));
  newState->currentDirectory = cwd;
  newState->cdStringLength = currentDirectoryStringSize;
  newState->directoryContents =  listDirectoryItems(".");
  stateInitted = 1;

  return newState;
}

void freeState(struct STATE* state) {
  //freeDirectoryBar(state->currentDirectory);
  free(state->currentDirectory);
  freeDirectory(state->directoryContents);
  free(state);
  state = NULL;
  stateInitted = 0;
}
