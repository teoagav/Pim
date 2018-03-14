#include <SDL2/SDL.h>
#include "App.h"

#include <iostream>

int main(int argc, char **argv) {

  if(argc == 1){
    App pim{};
    pim.run();
  } else if(argc == 2){
    App pim{argv[1]};
    pim.run();
  } else {
    std::cout << "Invalid arguments. Use: pim (optional file name)" << std::endl;
  }

  return 0;
}
