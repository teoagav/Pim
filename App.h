#ifndef _APP_H_
#define _APP_H_

#include <string>
#include <memory>
#include "ImageState.h"

class App {
  std::unique_ptr<ImageState> imageState;
  //TODO std::unique_ptr<Listener> listener;

  public:
    App(std::string fileName = "");
    void run();
};

#endif
