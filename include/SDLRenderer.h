#pragma once

/*
* @This Class is just for demonstrating how SDL_Rendering Works and is it worth using for drawing Tiled Maps wit the UV Mapping 
* @Automaticaly without an External File 'UV_Mapping' 
* @Ipenywis
*/

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <stdio.h>
#include <string>

#include "Window.h"


class SDLRenderer
{
public:

	SDLRenderer();
	SDLRenderer(SDL_Window* SDLWindow, Deep::Window* window);
	~SDLRenderer();

	void init();
	void draw();
	void update();
	void renderExample();

	void loadTexture(const std::string& file);

	// Getters 
	SDL_Renderer* getSDLRenderer() const { return m_renderer; }

	// The SDL Drawing Code should goes between those two Functions 
	void Begin(); ///< start SDL Rendering 
	void End(); ///< Stop SDL Rendering  

private:

	
	SDL_Window* m_SDLwindow = nullptr; ///< This is an instance of our main Winodw to use with SDL Rendering 
	SDL_Renderer* m_renderer = nullptr; ///< main SDL Renderer 
	SDL_Texture* m_texture = nullptr; ///< The texture to Render to the screen 
	
	Deep::Window* m_window = nullptr;///< This window is the default window of our game 
};

