#include "fileManipulation.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct DIRECTORY listDirectoryItems(const char* const directoryPath) {
  DIR* directory = opendir(directoryPath);

  if (directory == NULL) {
    printf("Could not open directory %s", directoryPath);
    struct DIRECTORY newDirectory = {0, NULL};
    return newDirectory;
  }

  size_t size = 1;
  size_t location = 0;

  struct DIRECTORY_ITEM* items = malloc(sizeof(struct DIRECTORY_ITEM));

  struct dirent* entry;
  while ((entry = readdir(directory)) != NULL) {
    enum DIRECTORY_ITEM_TYPE type;
    if (entry->d_type == DT_REG) {
      type = FILE_TYPE;
    }
    else if (entry->d_type == DT_DIR) {
      type = FOLDER_TYPE;
    }

    if (!type) {
      continue;
    }

    const size_t nameLength = strlen(entry->d_name);

    if (nameLength == 1 && entry->d_name[0] == '.') {
      continue;
    }

    if (size == location) {
      size *= 2;
      items = realloc(items, size*sizeof(struct DIRECTORY_ITEM));
    }

    if (nameLength == 2 && entry->d_name[0] == '.' && entry->d_name[1] == '.') {
      type = UP_ONE_LEVEL_TYPE;
    }

    //TODO sort items by type and alphabetically
    items[location].type = type;
    items[location].name = malloc((nameLength+1) * sizeof(char));
    strcpy(items[location].name, entry->d_name);
    ++location;
  }

  closedir(directory);

  struct DIRECTORY newDirectory = {location, items};
  return newDirectory;
}


void freeDirectory(struct DIRECTORY directory) {
  for (int i = 0; i < directory.itemCount; i++) {
    free(directory.items[i].name);
    directory.items[i].name = NULL;
  }
  free(directory.items);
  directory.items = NULL;
}
