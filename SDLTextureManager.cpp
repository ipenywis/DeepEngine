
#include "SDLTextureManager.h"
#include <iostream>

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0)
	{	
		printf("%s Image Can't Loaded \n", fileName.c_str());
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface); 
	if (pTexture = 0) {
		printf("Texture can't be created !");
		return false;
	}

	SDL_FreeSurface(pTempSurface);

	// everything went ok, add the texture to our list
	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

std::cout << "can't load texturmanager \n";

	// reaching here means something went wrong
	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip) 
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
 
void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawTile(int margin, int
	spacing, int x, int y, int width, int height, int currentRow,
	int currentFrame, SDL_Renderer *pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = margin + (spacing + width) * currentFrame;
	srcRect.y = margin + (spacing + height) * currentRow;

	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::loadTexture(const std::string& imagePath, SDL_Renderer* renderer) {

	// Loading and returning the loaded texture 
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());

	if (loadedSurface == nullptr)
		printf("Unable to load the image  %s!  SDL_image Error:  %s\n", imagePath.c_str(), IMG_GetError());
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == nullptr)
			printf("Unable to create the texture from  %s!  SDL Error:  %s\n", imagePath.c_str(), SDL_GetError());

		SDL_FreeSurface(loadedSurface);
	}

	m_texture = newTexture;
}