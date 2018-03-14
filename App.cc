#include "App.h"
#include "ImageState.h"
#include "Renderer.h"

App::App(std::string fileName): imageState{ std::make_unique<ImageState>(ImageState{fileName}) },
  listener{ std::make_unique<Listener>(Listener{}) }
  {}

void App::run(){
  Renderer renderer{this};

  while(1) {
    renderer.refresh();
  }
}
