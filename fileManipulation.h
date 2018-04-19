#ifndef _FILE_MANIPULATION_

#define _FILE_MANIPULATION_

#include <dirent.h>
#include <stddef.h>

enum DIRECTORY_ITEM_TYPE {
  UP_ONE_LEVEL_TYPE,
  FILE_TYPE,
  FOLDER_TYPE
};

struct DIRECTORY_ITEM {
  char* name;
  size_t nameLength;
  enum DIRECTORY_ITEM_TYPE type;
};

struct DIRECTORY {
  size_t itemCount;
  struct DIRECTORY_ITEM* items;
};

struct DIRECTORY listDirectoryItems(const char* const directoryPath);
void freeDirectory(struct DIRECTORY directory);

#endif
