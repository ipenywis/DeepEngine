#pragma once
#include <GL/glew.h>
#include <string>

namespace Deep {

    struct GLTexture {
        std::string filePath = "";
        GLuint id;
        int width;
        int height;
		// Getters 
		int getWidth() const { return width; }
		int getHeight() const { return height; }
    };
}