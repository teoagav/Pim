#ifndef _DIRECTORY_BAR_

#define _DIRECTORY_BAR_

struct DIRECTORY_BAR {
  char* directory;
  size_t length;
  struct BUTTON button;
};

struct DIRECTORY_BAR* initDirectoryBar();
void freeDirectoryBar(struct DIRECTORY_BAR* bar);

#endif
