#include "SDLRenderer.h"


SDLRenderer::SDLRenderer() {

}

SDLRenderer::SDLRenderer(SDL_Window* SDLWindow, Deep::Window* window) : m_SDLwindow(SDLWindow), m_window(window)
{
	// Empty 
}


SDLRenderer::~SDLRenderer()
{

}


void SDLRenderer::init() {

	// Creating the Renderer 
	m_renderer = SDL_CreateRenderer(m_SDLwindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		printf("We were not able to create the renderer! SDL Error:  %s\n", SDL_GetError());
		
	}
	// Initing the Renderer 
	SDL_RenderSetLogicalSize(m_renderer, m_window->getScreenWidth(), m_window->getScreenHeight());
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	// Image Init  
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not be initialized! SDL_image Error:  %s\n", IMG_GetError());

	}
	
}

void SDLRenderer::draw() {

}


void SDLRenderer::Begin() {
	SDL_RenderClear(m_renderer);
}

void SDLRenderer::End() {
	SDL_RenderPresent(m_renderer);
}


void SDLRenderer::update() {

}

void SDLRenderer::loadTexture(const std::string& imagePath) {

	// Loading and returning the loaded texture 
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());

	if (loadedSurface == nullptr)
		printf("Unable to load the image  %s!  SDL_image Error:  %s\n", imagePath.c_str(), IMG_GetError());
	else
	{
		newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);

		if (newTexture == nullptr)
			printf("Unable to create the texture from  %s!  SDL Error:  %s\n", imagePath.c_str(), SDL_GetError());

		SDL_FreeSurface(loadedSurface);
	}

	m_texture = newTexture;
}

void SDLRenderer::renderExample() {
	// Rendering the loaded texture to the screen 
	SDL_Rect srcRect;
	SDL_Rect destRect;

	// Setting The Destination Rectangular for Drawing  
	srcRect.x = 1;
	srcRect.y = 1;
	srcRect.w = 100;
	srcRect.h = 100;
	destRect.x = 10;
	destRect.y = 100;

	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &destRect, 0, 0, SDL_FLIP_NONE);
}