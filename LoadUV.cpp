#include "LoadUV.h"

namespace Deep {

	LoadUV::LoadUV()
	{
	}


	LoadUV::~LoadUV()
	{
		if (m_UVIndecies->size() == 56) {
			dispose();
		}
	}

	UVIndex::UVIndex() {
		// Empty 
	}

	UVIndex::UVIndex(int UV, int ID) : m_UV(UV), m_ID(ID) {
		// Empty 
	}

	void LoadUV::init(glm::ivec2& sheetDims, bool useID) {
		// Init TileSheet 
		m_sheet = new Deep::TileSheet;
		m_sheet->init(sheetDims);
		m_useID = useID;

		//Pointer Init 
// 		m_UVs = new std::vector<int>;
// 		m_IDs = new std::vector<int>;

		m_UVIndecies = new std::vector<UVIndex>;
	}

	void LoadUV::loadFile(const std::string& filePath) {


		// Input UV File 
		std::ifstream UVFile;
		UVFile.open(filePath);
		// Error Checking 
		if (UVFile.fail()) {
			puts("Could Not Open UV File !");
			UVFile.close();///< Close the file
		}

		// Tmp string to hold file data 
		std::string tmp;
		// Looping on the file Lines  
		while (std::getline(UVFile, tmp)) {
			// if the line starts with '#' ignore
			if (tmp[0] == '#') {
				// Do Nothing....continue;
				continue;
			}

			else {

				int version; ///< File Version 
				UVFile >> version;
				// File Version Checking 
				if (version != 100) {
					//puts("File Version not recognized ");
					//UVFile.close();
				}

				int numberLines; ///< Number Of lines for GID and UV
				UVFile >> numberLines;
				// Aloocate the Needed Memory space 
				
				int UV;
				int ID; ///< this variable could handle    ID or GID  depending on   useID boolean 
				// Looping for the number of GIDs and UVs available 
				for (int i = 0; i < numberLines; i++) {

					// Fetching UV and GID from File 
					UVFile >> UV;
					UVFile >> ID;

					// Getting the Exact UVs for Tile GID
					//if (m_useID) {
							// If the user want to use  ID 
					m_UVIndecies->emplace_back(UV, ID);	
				}

				if (m_UVIndecies->size() == numberLines) {
					UVFile.close();
				}
			}
		}
		
		// After success .. close the file 
		UVFile.close();

	}
	
	glm::vec4& LoadUV::getUVRect(int tileGID, int TileID) {
		glm::vec4 uvRect;

		for (auto& it = m_UVIndecies->begin(); it != m_UVIndecies->end(); it++) {
			if (m_useID) {
				if (it->getID() == TileID) {
					uvRect = m_sheet->getUVs(it->getUV());///< if use ID true then use ID
				}
			}
			else {
				if (it->getID() == tileGID)
					uvRect = m_sheet->getUVs(it->getUV());///< if use GID true then use GID
			}
		}

		return uvRect;
	}

	void LoadUV::dispose() {
		delete m_sheet;
		delete m_UVIndecies;
	}
}