#include "state.h"
#include <stdlib.h>
#include <stdio.h>


char stateInitted = 0;

struct STATE* initState() {
  if (stateInitted){
    printf("Warning: State has already been initialized\n");
  }
  struct STATE* newState = malloc(sizeof(struct STATE));
  newState->currentDirectory = initDirectoryBar();
  newState->directoryContents =  listDirectoryItems(".");
  stateInitted = 1;

  return newState;
}

void freeState(struct STATE* state) {
  freeDirectoryBar(state->currentDirectory);
  freeDirectory(state->directoryContents);
  free(state);
  state = NULL;
  stateInitted = 0;
}
