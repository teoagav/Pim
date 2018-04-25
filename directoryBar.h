#ifndef _DIRECTORY_BAR_

#define _DIRECTORY_BAR_

#include "button.h"

struct DIRECTORY_BAR {
  char* directory;
  size_t length;
  size_t bufferSize;
  struct BUTTON button;
};

struct DIRECTORY_BAR* initDirectoryBar();
void goIntoDirectory(struct DIRECTORY_BAR* bar);
void goUpOneLevel(struct DIRECTORY_BAR* bar);
void freeDirectoryBar(struct DIRECTORY_BAR* bar);

#endif
