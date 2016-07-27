#pragma once

// All the includes are in the Engine 
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "AudioEngine.h"
#include "Box.h" ///< Box2D
#include "DeepErrors.h"
#include "camera2D.h"
#include "DebugRenderer.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include "GUI.h"
#include "IGameScreen.h"
#include "ImageLoader.h"
#include "IMainGame.h"
#include "InputManager.h"
#include "IOManager.h"
#include "LevelManager.h"
#include "LoadUV.h"
#include "ParticleEngine2D.h"
#include "ParticleBatch2D.h"
#include "picoPNG.h"
#include "ResourceManager.h"
#include "ScreenList.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "TextureCache.h"
#include "TileSheet.h"
#include "Timing.h"
#include "Vertex.h"
#include "Window.h"
#include "Capsule.h" ///< Capsule Collision for Player 

namespace Deep {
    extern int init();
}