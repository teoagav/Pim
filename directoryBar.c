#include "directoryBar.h"
#include <unistd.h>
#include <string.h>

size_t currentDirectoryBufferSize = 0;

struct DIRECTORY_BAR* initDirectoryBar() {
  char* cwd = getcwd(NULL, 0);
  const size_t length = strlen(cwd);
  currentDirectoryBufferSize = currentDirectoryStringSize;

  struct DIRECTORY_BAR* newBar = malloc(sizeof(struct DIRECTORY_BAR));
  newBar->directory = cwd;
  newBar->length = length;
  newBar->bufferSize = length;
  newBar->button.xPos = ;

  return newBar;
}

void freeDirectoryBar(struct DIRECTORY_BAR* bar);

void goIntoDirectory(struct DIRECTORY_BAR* bar);

void goUpOneLevel(struct DIRECTORY_BAR* bar);
