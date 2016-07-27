#pragma once 

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <iostream>

//#include <tinyxml2/tinyxml2.h>

//enum AnimationState {Idle, Running, Jumping, Shooting};

class AnimationManager {
	AnimationManager();
	~AnimationManager();

public: 
	void init(const std::string& fileName, const std::string& entityName);
	void animate();

	//bool parseFile(const std::string& fileName, const std::string& entityName);
	//AnimationState checkState(const char* stateName);
	// Parsing Store Vars 
	
	//std::map<const char*, const char*> m_spriteAttributes;
	//int m_numTiles; ///< start from 0 
	//AnimationState m_state = AnimationState::Idle;

};