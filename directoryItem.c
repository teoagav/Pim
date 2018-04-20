#include "directoryItem.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int compareDirectoyItems(const void* dirItem1, const void* dirItem2) {
  return strcasecmp(((struct DIRECTORY_ITEM*)dirItem1)->name, ((struct DIRECTORY_ITEM*)dirItem2)->name);
  //TODO have custom compare for cases like files beginning with .
}

struct DIRECTORY listDirectoryItems(const char* const directoryPath) {
  DIR* directory = opendir(directoryPath);

  if (directory == NULL) {
    printf("Could not open directory %s", directoryPath);
    struct DIRECTORY newDirectory = {0,0, NULL};
    return newDirectory;
  }

  size_t size = 1;
  size_t location = 0;
  size_t directoryLoc = 0;

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

    if (type == FILE_TYPE || location == directoryLoc) {
      items[location].type = type;
      items[location].nameLength = nameLength;
      items[location].name = malloc((nameLength+1) * sizeof(char));
      strcpy(items[location].name, entry->d_name);
    }
    else if (type == UP_ONE_LEVEL_TYPE) {
      items[location].type = items[0].type;
      items[location].name = items[0].name;
      items[location].nameLength = items[0].nameLength;

      items[0].type = type;
      items[0].name = malloc((nameLength+1) * sizeof(char));
      strcpy(items[0].name, entry->d_name);
      items[0].nameLength = nameLength;
    }
    else {
      items[location].type = items[directoryLoc].type;
      items[location].name = items[directoryLoc].name;
      items[location].nameLength = items[directoryLoc].nameLength;

      items[directoryLoc].type = type;
      items[directoryLoc].name = malloc((nameLength+1) * sizeof(char));
      strcpy(items[directoryLoc].name, entry->d_name);
      items[directoryLoc].nameLength = nameLength;
    }

    if (type == UP_ONE_LEVEL_TYPE || type == FOLDER_TYPE) {
      ++directoryLoc;
    }

    ++location;
  }

  closedir(directory);

  qsort(items, directoryLoc, sizeof(struct DIRECTORY_ITEM), compareDirectoyItems);
  qsort(items + directoryLoc, location - directoryLoc,
    sizeof(struct DIRECTORY_ITEM), compareDirectoyItems);

  struct DIRECTORY newDirectory = {location, 0, items};
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
