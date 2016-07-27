#pragma once
#include "TextureCache.h"
#include "Vertex.h"
#include <string>

#include "glm/glm.hpp"

#include <fstream>
#include <iostream>
#include <sstream>



namespace Deep {

    //This is a way for us to access all our resources, such as
    //Models or textures.
    class ResourceManager
    {
    public:
        static GLTexture getTexture(std::string texturePath);
		static GLTexture getOpencvTexture(std::string texturePath);
		//static ColorRGBA8 convertHEXToRGBcolor(std::string HEXColor);
		//static ColorRGBA8 normalizeColor(const ColorRGBA8& color);

		// Getters 
		//const ColorRGBA8& getConvertedColor() const { return m_Convertedcolor; }
		//const ColorRGBA8& getNormalizedColor() const { return m_normalizedColor; }

    private:
        static TextureCache _textureCache;
		static ColorRGBA8 m_Convertedcolor;
		static ColorRGBA8 m_normalizedColor;
    };
}