#include <unistd.h>
#include <string.h>
#include "directoryBar.h"
#include "sdlHelper.h"
#include "GUIConstants.h"
#include <stdio.h>

size_t currentDirectoryBufferSize = 0;

struct DIRECTORY_BAR* initDirectoryBar() {
  char* cwd = getcwd(NULL, 0);
  const size_t length = strlen(cwd);

  struct DIRECTORY_BAR* newBar = malloc(sizeof(struct DIRECTORY_BAR));
  newBar->directory = cwd;
  newBar->length = length;
  newBar->bufferSize = length;
  newBar->button.xPos = FILE_LIST_LEFT_PADDING;
  newBar->button.yPos = CURRENT_DIRECTORY_TOP_PADDING;
  newBar->button.width = SCREEN_WIDTH - FILE_LIST_LEFT_PADDING - FILE_LIST_RIGHT_PADDING;
  newBar->button.height = CURRENT_DIRECTORY_BAR_HEIGHT;

  return newBar;
}

void freeDirectoryBar(struct DIRECTORY_BAR* bar) {
  free(bar->directory);
  free(bar);
}

void goIntoDirectory(struct DIRECTORY_BAR* bar, char* name, size_t length) {
  const size_t actualExtraLength = bar->length == 1 ? length : length + 1;
  while (bar->length + actualExtraLength > bar->bufferSize) {
    bar->bufferSize *= 2;
  }
  bar->directory = realloc(bar->directory, bar->bufferSize * sizeof(char));

  if (bar->length == 1) {
    strcpy(bar->directory + bar->length, name);
  }
  else {
    bar->directory[bar->length] = '/';
    strcpy(bar->directory + bar->length + 1, name);
  }

  bar->length += actualExtraLength;
}

void goUpOneLevel(struct DIRECTORY_BAR* bar) {
  if (bar->length == 1) {
    return;
  }
  size_t last = bar->length - 1;
  while(last > 0 && bar->directory[last] != '/') {
    last--;
  }

  if (last == 0) {
    bar->directory[0] = '/';
    bar->directory[1] = '\0';
    bar->length = 1;
    return;
  }
  bar->directory[last] = '\0';
  bar->length = last;
}

void drawCurrentDirectoryBar(struct DIRECTORY_BAR* currentDirectory) {
	drawRectOutLine(currentDirectory->button.xPos, currentDirectory->button.yPos,
    currentDirectory->button.width, currentDirectory->button.height);
	drawText(currentDirectory->directory, currentDirectory->length, currentDirectory->button.xPos,
    currentDirectory->button.yPos + TEXT_TOP_OFFSET);
}
