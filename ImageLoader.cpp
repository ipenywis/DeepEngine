#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "DeepErrors.h"

#include <iostream>

using namespace std;


namespace Deep {

    GLTexture ImageLoader::loadPNG(std::string filePath) {
        //Create a GLTexture and initialize all its fields to 0
        GLTexture texture = {};

        //This is the input data to decodePNG, which we load from a file
        std::vector<unsigned char> in;
        //This is the output data from decodePNG, which is the pixel data for our texture
        std::vector<unsigned char> out;

        unsigned long width, height;

        //Read in the image file contents into a buffer
        if (IOManager::readFileToBuffer(filePath, in) == false) {
            fatalError("Failed to load PNG file to buffer!");
        }

        //Decode the .png format into an array of pixels
        int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
        if (errorCode != 0) {
            fatalError("decodePNG failed with error: " + std::to_string(errorCode));
        }

        //Generate the openGL texture object
        glGenTextures(1, &(texture.id));

        //Bind the texture object
        glBindTexture(GL_TEXTURE_2D, texture.id);
		

        //Upload the pixels to the texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

        //Set some texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); ///< OLD: GL_LINEAR_MIPMAP_LINEAR
		// FIXED BUG: Change GL_LINEAR To GL_NEAREST_MIPMAP_NEAREST to fix  ** GAPS ** Between Tiles, in tile Maps 

        //Generate the mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);

        //Unbind the texture
        glBindTexture(GL_TEXTURE_2D, 0);

		// Setting the local VARs
        texture.width = width;
        texture.height = height;
        texture.filePath = filePath;

        //Return a copy of the texture data
        return texture;
    }

	// TODO: Add FreeImage Library support for loading all Kind of images 

	GLTexture ImageLoader::loadImage(std::string filePath, cv::Mat &image) {

		GLTexture texture = {}; ///< init everything to Zero 

		if (image.empty()) {
			std::cout << "image empty" << std::endl;
		}
		else {
			std::cout << "Processing Image ... " << std::endl;
			//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glGenTextures(1, &(texture.id));
			glBindTexture(GL_TEXTURE_2D, texture.id);

			/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Set texture clamping method
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);*/

			//Set some texture parameters
			/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);*/ ///< OLD: GL_LINEAR_MIPMAP_LINEAR
																							  // FIXED BUG: Change GL_LINEAR To GL_NEAREST_MIPMAP_NEAREST to fix  ** GAPS ** Between Tiles, in tile Maps P);

			//cv::cvtColor(image, image, CV_RGB2BGR);

			glTexImage2D(GL_TEXTURE_2D,         // Type of texture
				0,                   // Pyramid level (for mip-mapping) - 0 is the top level
				GL_RGBA,              // Internal colour format to convert to
				image.cols,          // Image width  i.e. 640 for Kinect in standard mode
				image.rows,          // Image height i.e. 480 for Kinect in standard mode
				0,                   // Border width in pixels (can either be 1 or 0)
				GL_RGB,              // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
				GL_UNSIGNED_BYTE,    // Image data type
				image.ptr());        // The actual image data itself

			//Generate the mipmaps
			glGenerateMipmap(GL_TEXTURE_2D);

			// Unbind the texture 
			glBindTexture(GL_TEXTURE_2D, 0);

			cv::addWeighted(image, 1, image, 1, 0.0, image);

		// Setting the local VARs
			texture.width = image.cols;
			texture.height = image.rows;
			texture.filePath = filePath;

			//Return a copy of the texture data
			return texture;
		}
	}

	std::vector<unsigned char> ImageLoader::resizePixels(std::vector<unsigned char> pixels, int w1, int h1, int w2, int h2) {
		std::vector<unsigned char> temp;
		// Allocate Space 
		//temp[w2*h2];

		// EDIT: added +1 to account for an early rounding problem
		int x_ratio = (int)((w1 << 16) / w2) + 1;
		int y_ratio = (int)((h1 << 16) / h2) + 1;
		//int x_ratio = (int)((w1<<16)/w2) ;
		//int y_ratio = (int)((h1<<16)/h2) ;
		int x2, y2;	
		for (int i = 0; i<h2; i++) {
			for (int j = 0; j<w2; j++) {
				x2 = ((j*x_ratio) >> 16);
				y2 = ((i*y_ratio) >> 16);
				temp = pixels;
				//temp[x2, y2] = pixels[x2*w1 / w2, y2*h1 / h2];
			}
		}
		return temp;
	}

}