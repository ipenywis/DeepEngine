#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>




namespace Deep {

    TextureCache::TextureCache()
    {
    }

    TextureCache::~TextureCache()
    {
    }

    GLTexture TextureCache::getTexture(std::string texturePath) {

        //lookup the texture and see if its in the map
        auto mit = _textureMap.find(texturePath);

        //check if its not in the map
        if (mit == _textureMap.end()) {
            //Load the texture
            GLTexture newTexture = ImageLoader::loadPNG(texturePath);

            //Insert it into the map
            _textureMap.insert(make_pair(texturePath, newTexture));

            return newTexture;
        }
        return mit->second;
    }

	GLTexture TextureCache::getopencvTexture(std::string texturePath) {

		//lookup the texture and see if its in the map
		auto mit = _textureMap.find(texturePath);
		GLTexture newTexture;
		
		//check if its not in the map
		if (mit == _textureMap.end()) {
			//Load the texture using OpenCV
			cv::Mat image;
			image = cv::imread(texturePath);
			if (image.empty()) {
				puts("Image file is  Corrupted !");
			}
			else {
				newTexture = ImageLoader::loadImage(texturePath, image);
				//Insert it into the map
				_textureMap.insert(make_pair(texturePath, newTexture));
			}

			return newTexture;
		}
		return mit->second;

	}

	// Function turn a cv::Mat into a texture, and return the texture ID as a GLuint for use
	GLuint TextureCache::matToTexture(cv::Mat &mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter)
	{
		// Generate a number for our textureID's unique handle
		GLuint textureID;
		glGenTextures(1, &textureID);

		// Bind to our texture handle
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Catch silly-mistake texture interpolation method for magnification
		if (magFilter == GL_LINEAR_MIPMAP_LINEAR ||
			magFilter == GL_LINEAR_MIPMAP_NEAREST ||
			magFilter == GL_NEAREST_MIPMAP_LINEAR ||
			magFilter == GL_NEAREST_MIPMAP_NEAREST)
		{
			std::cout << "You can't use MIPMAPs for magnification - setting filter to GL_LINEAR" << std::endl;
			magFilter = GL_LINEAR;
		}

		// Set texture interpolation methods for minification and magnification
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapFilter);

		// Set incoming texture format to:
		// GL_BGR       for CV_CAP_OPENNI_BGR_IMAGE,
		// GL_LUMINANCE for CV_CAP_OPENNI_DISPARITY_MAP,
		// Work out other mappings as required ( there's a list in comments in main() )
		GLenum inputColourFormat = GL_BGR;
		if (mat.channels() == 1)
		{
			inputColourFormat = GL_LUMINANCE;
		}

		// Create the texture
		glTexImage2D(GL_TEXTURE_2D,     // Type of texture
			0,                 // Pyramid level (for mip-mapping) - 0 is the top level
			GL_RGB,            // Internal colour format to convert to
			mat.cols,          // Image width  i.e. 640 for Kinect in standard mode
			mat.rows,          // Image height i.e. 480 for Kinect in standard mode
			0,                 // Border width in pixels (can either be 1 or 0)
			inputColourFormat, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
			GL_UNSIGNED_BYTE,  // Image data type
			mat.ptr());        // The actual image data itself

							   // If we're using mipmaps then generate them. Note: This requires OpenGL 3.0 or higher
		if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
			minFilter == GL_LINEAR_MIPMAP_NEAREST ||
			minFilter == GL_NEAREST_MIPMAP_LINEAR ||
			minFilter == GL_NEAREST_MIPMAP_NEAREST)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		return textureID;
	}

		
}