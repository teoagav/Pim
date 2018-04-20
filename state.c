#include "state.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

size_t currentDirectoryStringSize = 0;
size_t currentDirectoryBufferSize = 0;

struct State initState() {
  char* cwd = getcwd(NULL, 0);
  currentDirectoryStringSize = strlen(cwd);
  currentDirectoryBufferSize = currentDirectoryStringSize;
  struct State newState = {cwd, listDirectoryItems(".")};
  return newState;
}

void freeState(struct State* state) {
  free(state->currentDirectory);
  freeDirectory(state->directoryContents);
}
