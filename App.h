#ifndef _APP_H_
#define _APP_H_

#include <string>
#include <memory>
#include "DisplayState.h"

class App {
  std::unique_ptr<DisplayState> displayState;
  std::unique_ptr<Renderer> renderer;
  std::unique_ptr<Listener> listener;

  public:
    App(std::string fileName = "");
    void run();
};

#endif
