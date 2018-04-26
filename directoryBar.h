#ifndef _DIRECTORY_BAR_

#define _DIRECTORY_BAR_

#include <stdlib.h>
#include "button.h"

struct DIRECTORY_BAR {
  char* directory;
  size_t length;
  size_t bufferSize;
  struct BUTTON button;
};

struct DIRECTORY_BAR* initDirectoryBar();
void goIntoDirectory(struct DIRECTORY_BAR* bar, char* name, size_t length);
void goUpOneLevel(struct DIRECTORY_BAR* bar);
void freeDirectoryBar(struct DIRECTORY_BAR* bar);
void drawCurrentDirectoryBar(struct DIRECTORY_BAR* currentDirectory);

#endif
