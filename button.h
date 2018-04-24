#ifndef _BUTTON_

#define _BUTTON_

struct BUTTON {
  int xPos;
  int yPos;
  int width;
  int height;
};

char isClicked(struct BUTTON* button, const int clickXPos, const int clickYPos);

#endif
