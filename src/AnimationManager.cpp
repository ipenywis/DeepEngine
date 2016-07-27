#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
	
}

AnimationManager::~AnimationManager() 
{

}

void AnimationManager::init(const std::string& fileName, const std::string& entityName) {
	// Init all the Systems and Vars 
	//parseFile(fileName, entityName);
}

void AnimationManager::animate() {

	// Animate Entity 

}

//bool AnimationManager::parseFile(const std::string& fileName, const std::string& entityName) {
	// Parse Animation XML file here 
	// Local Vars 
	/*tinyxml2::XMLDocument XMLDocument;
	tinyxml2::XMLNode* XMLRootNode = nullptr; ///< store the root node 
	// Opening and loading the data 
	tinyxml2::XMLError eResult = XMLDocument.LoadFile(fileName.c_str());
	if (eResult != tinyxml2::XML_SUCCESS) return false;
	// Root node 
	XMLRootNode = XMLDocument.FirstChildElement("Animation");
	if (XMLRootNode == nullptr) return false;*/
	
	// Looping throught all the Elements 
	/*for (tinyxml2::XMLElement* XMLelem = XMLRootNode->FirstChildElement(entityName.c_str()); XMLelem != nullptr; XMLelem = XMLelem->NextSiblingElement()) {
		std::string elemName = XMLelem->Value();
		if (elemName == "Player") {
			for (tinyxml2::XMLElement* XMLe = XMLelem->FirstChildElement("Sprite"); XMLe != nullptr; XMLe = XMLe->NextSiblingElement()) {
				// Storing Local Sprite Variables 
				m_spriteAttributes.insert(std::make_pair(XMLe->Attribute("name"), XMLe->Attribute("path")));
			
				for (tinyxml2::XMLElement* e = XMLe->FirstChildElement("Tile"); e != nullptr; e = e->NextSiblingElement()) {
					const char* eName = e->Value();
					if (eName == "Tile") {
						m_numTiles = (int)e->Attribute("numTiles");
					}
					else if (eName == "State") {
						const char* stateName = e->Attribute("movingState");
						printf("Moving state  : %s", stateName);
						m_state = checkState(stateName); ///< our check() for checking the Aniamtion 					
					}
				}
			
			}	
		}
	}*/

	//return true; ///< false means does not complete successfully 
//}

/*AnimationState AnimationManager::checkState(const char* stateName) {
	// Check if the animation Exist 
	if (stateName == (char*)AnimationState::Idle) {
		return AnimationState::Idle;
	}
	else if (stateName == (char*)AnimationState::Running) {
		return AnimationState::Running;
	}
	else if (stateName == (char*)AnimationState::Jumping) {
		return AnimationState::Jumping;
	}
	else if (stateName == (char*)AnimationState::Shooting) {
		return AnimationState::Shooting;
	}
	else {
		// Then return default Aniamtion 
		return AnimationState::Idle;
		printf("No Animation Found, with Name :  %s", stateName);
	}
}*/