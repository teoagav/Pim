#include "button.h"
#include "directoryBar.h"
#include "state.h"
#include "directoryItem.h"
#include "directoryBar.h"
#include <stdio.h>

char isClicked(struct BUTTON* button, const int clickXPos, const int clickYPos) {
  printf("x:%d, y:%d, h:%d, l:%d\n:", button->xPos, button->yPos, button->height, button->width);
  return (button->xPos < clickXPos) && ((button->xPos + button->width) > clickXPos) &&
    (button->yPos < clickYPos) && ((button->yPos + button->height) > clickYPos);
}

void directoryItemDoubleClicked(struct STATE* state, const int xPos, const int yPos) {
	 for (size_t i = 0; i < state->directoryContents->itemCount; i++) {

     printf("%s\n:", state->directoryContents->items[i].name);

		 if (isClicked(&(state->directoryContents->items[i].button), xPos, yPos)) {
			 if (state->directoryContents->items[i].type == UP_ONE_LEVEL_TYPE) {
         goUpOneLevel(state->currentDirectory);
         freeDirectory(state->directoryContents);
         state->directoryContents = listDirectoryItems(state->currentDirectory->directory);
			 }
			 else if (state->directoryContents->items[i].type == FOLDER_TYPE) {
         goIntoDirectory(state->currentDirectory, state->directoryContents->items[i].name, state->directoryContents->items[i].nameLength);
         freeDirectory(state->directoryContents);
         state->directoryContents = listDirectoryItems(state->currentDirectory->directory);
			 }
			 break;
		 }
	 }
}

void handleDoubleClick(struct STATE* state, const int xPos, const int yPos) {
  directoryItemDoubleClicked(state, xPos, yPos);
}
