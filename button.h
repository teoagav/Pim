#ifndef _BUTTON_

#define _BUTTON_

struct STATE;

struct BUTTON {
  int xPos;
  int yPos;
  int width;
  int height;
};

char isClicked(struct BUTTON* button, const int clickXPos, const int clickYPos);
void handleDoubleClick(struct STATE* state, const int xPos, const int yPos);

#endif
