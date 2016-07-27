#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "TileSheet.h"
#include "GLTexture.h"

#include <glm\glm.hpp>

namespace Deep {

	// UV & ID rect  Struct 
	struct UVIndex {
	public:
		UVIndex();
		UVIndex(int UV, int ID);

		// Getters 
		int getUV() const { return m_UV; }
		int getID() const { return m_ID; }

	private:
		int m_UV;
		int m_ID;

	};



	class LoadUV
	{
	public:
		LoadUV();
		~LoadUV();

		void init(glm::ivec2& sheetDims, bool useID);
		void loadFile(const std::string& fileName);
		glm::vec4& getUVRect(int tileGID, int TileID);
		void dispose();

		// Getters 
		Deep::TileSheet* getSheet() const { return m_sheet; }
		glm::vec4 getUV() const { return m_uvRect; }
// 		std::vector<int>* getUVVector() const { return m_UVs; }
// 		std::vector<int>* getIDVector() const { return m_IDs; }

		std::vector<UVIndex>* getUVIndexVec() const { return m_UVIndecies; }
		

	private:
		Deep::TileSheet* m_sheet;
		glm::vec4 m_uvRect;

		bool m_useID;

		/*int* m_UV;
		int* m_ID;
*/
// 		std::vector<int>* m_UVs = nullptr;
// 		std::vector<int>* m_IDs = nullptr;

		std::vector<UVIndex>* m_UVIndecies = nullptr;

		// Is it the right thing for buildig video games 
	};
	

}