#include "button.h"
#include "directoryBar.h"
#include "state.h"
#include "directoryItem.h"
#include "directoryBar.h"

char isClicked(struct BUTTON* button, const int clickXPos, const int clickYPos) {
  return (button->xPos < clickXPos) && ((button->xPos + button->width) > clickXPos) &&
    (button->yPos < clickYPos) && ((button->yPos + button->height) > clickYPos);
}

void directoryItemDoubleClicked(const struct STATE* state, const int xPos, const int yPos) {
	 for (size_t i = 0; i < state->directoryContents->itemCount; i++) {
		 if (isClicked(&(state->directoryContents->items[i].button), xPos, xPos)) {
			 if (state->directoryContents->items[i].type == UP_ONE_LEVEL_TYPE) {

			 }
			 else if (state->directoryContents->items[i].type == FOLDER_TYPE) {

			 }
			 break;
		 }
	 }
}

void handleDoubleClick(const struct STATE* state, const int xPos, const int yPos) {
  directoryItemDoubleClicked(state, xPos, yPos);
}
