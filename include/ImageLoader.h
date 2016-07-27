#pragma once
#include "GLTexture.h"

#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace Deep {

    //Loads images into GLTextures
    class ImageLoader
    {
    public:
        static GLTexture loadPNG(std::string filePath);
		static GLTexture loadImage(std::string filePath, cv::Mat &image);
		static std::vector<unsigned char> resizePixels(std::vector<unsigned char> pixels, int w1, int h1, int w2, int h2);
    };

}