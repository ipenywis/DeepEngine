#include "ResourceManager.h"



namespace Deep {

    TextureCache ResourceManager::_textureCache;

    GLTexture ResourceManager::getTexture(std::string texturePath) {
        return _textureCache.getTexture(texturePath);
    }

	GLTexture ResourceManager::getOpencvTexture(std::string texturePath) {
		return _textureCache.getopencvTexture(texturePath);
	}

	/*ColorRGBA8 ResourceManager::convertHEXToRGBcolor(std::string HEXColor) {
			// ... and the target rgb integer values.
		GLubyte r, g, b;

			// Remove the hashtag ...
			if (HEXColor.at(0) == '#') {
				HEXColor = HEXColor.erase(0, 1);
			}

			// ... and extract the rgb values.
			std::istringstream(HEXColor.substr(0, 2)) >> std::hex >> r;
			std::istringstream(HEXColor.substr(2, 2)) >> std::hex >> g;
			std::istringstream(HEXColor.substr(4, 2)) >> std::hex >> b;

			// Finally dump the result.
			/ *std::cout << std::dec << "Parsing #" << HEXColor
				<< " as hex gives (" << r << ", " << g << ", " << b << ")" << '\n';* /
			// Setting Color Values for the Background
			m_Convertedcolor.r = r;
			m_Convertedcolor.g = g;
			m_Convertedcolor.b = b;

			return m_Convertedcolor;
	}

	ColorRGBA8 ResourceManager::normalizeColor(const ColorRGBA8& color) {
		// Normalize the Color getted from the level to Opengl Nomalized Color 
		m_normalizedColor.r = (float)color.r / 255.0f;
		m_normalizedColor.g = (float)color.g / 255.0f;
		m_normalizedColor.b = (float)color.b / 255.0f;
		m_normalizedColor.a = (float)color.a / 255.0f;

		return m_normalizedColor;

	}
*/

}
