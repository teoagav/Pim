#ifndef _DIRECTORY_ITEM_

#define _DIRECTORY_ITEM_

struct BUTTON {
  int xPos,
  int yPos,
  int height,
  int width,
};

char isClicked(struct BUTTON* button, const int clickXPos, const in clickYPos);

#endif
