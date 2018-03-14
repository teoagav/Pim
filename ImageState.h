#ifndef _IMAGE_STATE_H_
#define _IMAGE_STATE_H_

#include <memory>
#include <string>
#include <iterator>
#include <iostream>
#include <cstddef>

#include <opencv2/opencv.hpp>

using std::unique_ptr;

class FileCouldNotBeOpenedError{};

class ImageState{
  unique_ptr<unique_ptr<uchar[4]>> imagePixels;
  public:
    ImageState(std::string fileName) {
      std::cout<< fileName << std::endl;
      cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);
      if(!image.data){
        throw FileCouldNotBeOpenedError{};
      }
      size_t i = 0;
      while(i < 360000) {
        std::cout<< static_cast<int>(image.data[i]) <<std::endl;
          std::cout<< "size"<< i <<std::endl;
        i++;
      }
      std::cout << static_cast<size_t>(sizeof(image.data)) << std::endl;
    }
};

#endif
