#include <dirent.h>
#include <stddef.h>

enum DIRECTORY_ITEM_TYPE {
  UP_ONE_LEVEL_TYPE,
  FILE_TYPE,
  FOLDER_TYPE
};

struct DIRECTORY_ITEM {
  char* name;
  enum DIRECTORY_ITEM_TYPE type;
};

struct DIRECTORY {
  size_t itemCount;
  struct DIRECTORY_ITEM* items;
};

struct DIRECTORY listDirectoryItems(const char* const directoryPath);
void freeDirectory(struct DIRECTORY directory);
