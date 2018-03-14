#include "App.h"
#include "ImageState.h"
//TODO #include "Renderer.h"

App::App(std::string fileName): imageState{ std::make_unique<ImageState>(ImageState{fileName}) }
  //TODO listener{ std::make_unique<Listener>(Listener{}) }
  {}

void App::run(){
  //TODO Renderer renderer{this};
  imageState->printState();
  //while(1) {
    //TODO renderer.refresh();
  //}
}
