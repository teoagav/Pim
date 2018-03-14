#include "ImageState.h"

#include <iostream>
#include <opencv2/opencv.hpp>

ImageState::ImageState(std::string fileName) {
  cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);
  if(!image.data){
    throw FileCouldNotBeOpenedError{};
  }

  cv::cvtColor(image, image, CV_BGR2RGBA, 4);

  this->width = image.cols;
  this->height = image.rows;

  const size_t size = height * width * 4;

  imagePixels = std::vector<Pixel>(height * width);

  for(size_t i = 0; i < size; i += 4){
    const uint8_t redColor = image.data[i];
    const uint8_t greenColor = image.data[i + 1];
    const uint8_t blueColor = image.data[i + 2];
    const uint8_t alpha = image.data[i + 3];

    imagePixels[i/4] = Pixel{redColor, greenColor, blueColor, alpha};
  }
}

Pixel &ImageState::getPixel(size_t xCoord, size_t yCoord) {
  return imagePixels[yCoord*width + xCoord];
}

void ImageState::printState(){
  const size_t size = height * width;
  for(size_t i = 0; i < size; ++i) {
    std::cout << "(" << i / width << "," << i % width << "): ";
    std::cout << "[" << static_cast<int>(imagePixels[i].red) << "," << static_cast<int>(imagePixels[i].green) << ","
      << static_cast<int>(imagePixels[i].blue) << "," << static_cast<int>(imagePixels[i].alpha) << "]";
    std::cout << "\n";
  }
  std::cout << std::endl;
}
