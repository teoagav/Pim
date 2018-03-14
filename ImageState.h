#ifndef _IMAGE_STATE_H_
#define _IMAGE_STATE_H_

#include <vector>
#include <cstddef>
#include <string>
#include <cstdint>

class FileCouldNotBeOpenedError{};

struct Pixel {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
};

class ImageState{
  size_t width;
  size_t height;
  std::string imageName;
  std::vector<Pixel> imagePixels;
  public:
    ImageState(std::string fileName);
    Pixel &getPixel(size_t xCoord, size_t yCoord);
    void printState();
};

#endif
