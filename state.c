#include "state.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

size_t currentDirectoryStringSize = 0;
size_t currentDirectoryBufferSize = 0;
char stateInitted = 0;

struct State initState() {
  if (!stateInitted){
    printf("Warning: State has already been initialized\n");
  }
  char* cwd = getcwd(NULL, 0);
  currentDirectoryStringSize = strlen(cwd);
  currentDirectoryBufferSize = currentDirectoryStringSize;
  struct State newState = {cwd, currentDirectoryStringSize, listDirectoryItems(".")};
  stateInitted = 1;

  return newState;
}

void freeState(struct State* state) {
  free(state->currentDirectory);
  freeDirectory(state->directoryContents);
  stateInitted = 0;
}
