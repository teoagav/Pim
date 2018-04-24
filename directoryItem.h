#ifndef _DIRECTORY_ITEM_

#define _DIRECTORY_ITEM_

#include <dirent.h>
#include <stddef.h>
#include "button.h"

struct STATE;

enum DIRECTORY_ITEM_TYPE {
  UP_ONE_LEVEL_TYPE,
  FILE_TYPE,
  FOLDER_TYPE
};

struct DIRECTORY_ITEM {
  char* name;
  size_t nameLength;
  struct BUTTON button;
  enum DIRECTORY_ITEM_TYPE type;
};

struct DIRECTORY {
  size_t itemCount;
  size_t topItem;
  struct DIRECTORY_ITEM* items;
};

struct DIRECTORY* listDirectoryItems(const char* const directoryPath);
void drawDirectoryItems(const struct DIRECTORY* dir);
void directoryItemDoubleClicked(const struct STATE* state, const int xPos, const int yPos);
void freeDirectory(struct DIRECTORY* directory);

#endif
