
char isClicked(struct BUTTON* button, const int clickXPos, const in clickYPos){
  return (button->xPos < clickXPos) && ((button->xPos + button->width) > clickXPos) &&
    (button->yPos < clickYPos) && ((button->yPos + button->height) > clickYPos);
}
