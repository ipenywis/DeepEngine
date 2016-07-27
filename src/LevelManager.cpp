#include "LevelManager.h"

#include "TextureCache.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Deep {

	LevelManager::LevelManager() {

	}

	LevelManager::LevelManager(const std::string& fileName, const std::string& UVFileName, Deep::Camera2D& camera) 
		: m_fileName(fileName), m_UVFileName(UVFileName), m_camera(camera)
	{
		// Empty 
	}


	LevelManager::~LevelManager()
	{
		//m_DebugRenderer->dispose();
		dispose();
	}



	void LevelManager::init(Deep::LoadUV* loadUV, const std::string& fileName, const std::string& UVFileName,
		Deep::Window* window, Deep::Camera2D& camera, const glm::ivec2& sheetDims, bool useID) {

		// Setting Variables
		m_loadUV = loadUV;
		m_fileName = fileName;
		m_UVFileName = UVFileName;
		m_window = window;
		m_camera = camera;
		m_sheetDims = sheetDims;
		m_useID = useID;

		m_newMapTileWidth = 2;
		m_newMapTileHeight = 2;

		// Pointer Initialization
	//	m_SDLRenderer = new SDLRenderer(m_window->getWindow(), m_window);
		m_map = new Tmx::Map;

		m_sheet = new Deep::TileSheet;
		m_sheet->init(glm::ivec2(8, 7));

		x_pos = std::uniform_real_distribution<float>(0.0f, 10.0f);
		y_pos = std::uniform_real_distribution<float>(0.0f, 10.0f);

		// SDLRenderer Init 
/*
		m_SDLRenderer->init();
		m_SDLRenderer->loadTexture("Tiles/Tileset.png");*/

		//std::string fileName = (argc > 1) ? argv[1] : "testa.tmx";  /// Not good File Loading 
		m_map->ParseFile(m_fileName);
		// Error checking 
		if (m_map->HasError())
		{
			// Error Handling 
			printf("error code: %d\n", m_map->GetErrorCode());
			printf("error text: %s\n", m_map->GetErrorText().c_str());
                                 
		}
		// Debug Renderer for drawing Circles, Lines, Rectangulars... [Shapes]	
// 		m_DebugRenderer = new Deep::DebugRenderer;
// 		m_DebugRenderer->init();


		// The texture to Defragete with UV Rect (UV System)

		//TextureManager::Instance()->loadTexture("Tiles/tileset.png", m_SDLRenderer->getSDLRenderer());


		// Init UV Loading 
		//m_loadUV = new Deep::LoadUV;
		//m_loadUV->init(m_sheetDims, m_useID);
		
		// TODO: Must implement UV Auto Mapping System with Tile ID  for making the preformance Better means  : NO LAG !

		m_backgroundsBatch.init();
}


	void LevelManager::OpenGLDraw() {

		m_spriteBatch.init();
		m_spriteBatch.begin();

		for (int i = 0; i < m_numTileLayers; ++i)
		{
			for (int y = 0; y < m_layerHeight; ++y)
			{
				for (int x = 0; x < m_layerWidth; ++x)
				{

					// Tiles GIDs and IDs 
					m_tileID = m_tileLayer->GetTileId(x, y);
					m_tileGID = m_tileLayer->GetTileGid(x, y);

					

					// Drawing All tiles using SpriteBatch 
					glm::vec4 destRect;
					// Converting Coordinates 

					//m_camera.setScale(32.0f);

					 m_newMapTileWidth = 2;
					m_newMapTileHeight = 2;

					int newWidth = m_mapTileWidth - m_newMapTileWidth;
					int newHeight = m_mapTileHeight - m_mapTileHeight;

					int height = m_newMapTileHeight * m_mapHeight;

					//m_camera.setPosition(glm::vec2(m_window->getScreenWidth(), m_window->getScreenHeight()));
					//float SCALE = 1.0f / 5.0f;
					//m_camera.setScale(32.0f);
					//glm::vec2 pos = m_camera.convertScreenToWorld(glm::vec2(x * m_mapTileWidth, y * m_mapTileHeight), false);
					//glm::vec2 pos = m_camera.convertScreenToWorld(glm::vec2(x * m_newMapTileWidth, y * m_newMapTileHeight), true);
					glm::vec2 pos = glm::vec2(x * m_newMapTileWidth, y * m_newMapTileHeight);
					
					//glm::vec2 m_o = oldPos - pos;

					//glm::vec2 scale = m_camera.convertScreenToWorld(glm::vec2(x * m_mapTileWidth, y * m_mapTileHeight), false);

					//glm::vec2 dims = m_camera.convertScreenToWorld(glm::vec2(m_mapTileWidth, m_mapTileHeight));
					
					
					//glm::vec2 pos = glm::vec2(x * m_mapTileWidth, y * m_mapTileHeight);
					// Destination Rectangular for Drawing 
					destRect.x = pos.x;
					destRect.y = (pos.y * -1) + height - 2.0f;  ///< flipping the Y Axis  m_window.getScreenHeight() - 
					destRect.w = m_newMapTileWidth;
					destRect.z = m_newMapTileHeight; ///< Fliping the Y Axis

					// Background Color 
					Deep::ColorRGBA8 backgroundColor;
					glm::vec4 UVrect;

					//printf("  %d  ", m_tileLayer->GetTileTilesetIndex(x, y));

					// Getting the Tileset Index 
					m_tileTileSetIndex = m_tileLayer->GetTileTilesetIndex(x, y);
					if(m_tileTileSetIndex == -1) {
						
					}
					else { /// If the tile has a texture on it 
						// Remove the first three chars    ../
						m_imageSRC = m_imageSource.substr(3, m_imageSource.size());
						//printf("  %s  ", m_imageSource.c_str());
						// The texture to Defragete with UV Rect (UV System)
						m_texture = Deep::ResourceManager::getTexture("Tiles/Tileset_no_mini_Tiles.png");
						backgroundColor = Deep::ColorRGBA8(255, 255, 255, 255);
					}

					// Drawing the Level using SpriteBatch 
 					m_spriteBatch.draw(destRect, m_loadUV->getUVRect(m_tileGID, m_tileID)
 					, m_texture.id, 0.0f, backgroundColor);

				}

			}

		}
		
		// End Sprite Batching 
		m_spriteBatch.end();

	}

	void LevelManager::drawBackgrounds(glm::vec4& uvRect, Deep::Camera2D& camera) {
		m_backgroundsBatch.begin();

		// Calculating Map Width and Height 
		int width = m_mapTileWidth * m_mapWidth;
		int height = m_mapTileHeight * m_mapHeight;

		int w_width = 500;
		int w_height = 500;

		Deep::GLTexture BackTexture = Deep::ResourceManager::getTexture("Tiles/background.png");
		float XPos = m_window->getScreenWidth();
		float YPos = m_window->getScreenHeight();
		//glm::vec2 pos = m_camera.convertScreenToWorld(glm::vec2(XPos, YPos));
		//m_camera.setPosition(glm::vec2(XPos, YPos)); 

		int halfWidth = m_window->getScreenWidth() * 3;
		int halfHeight = m_window->getScreenHeight() * 3;

		glm::vec2 pos(camera.getPosition().x - halfWidth, camera.getPosition().y - halfHeight);

		glm::vec4 dest(pos, halfWidth * 4, height);
		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

		//m_backgroundsBatch.draw(dest, uv, BackTexture.id, 0.0f, Deep::ColorRGBA8(255, 255, 255, 255));
		Deep::GLTexture coin = Deep::ResourceManager::getTexture("Tiles/coin.png");
		m_backgroundsBatch.draw(dest, uv, coin.id, 0.0f, Deep::ColorRGBA8(255, 255, 255, 255));
		m_backgroundsBatch.end();

		m_backgroundsBatch.renderBatch();
	}

	void LevelManager::drawobject(Deep::SpriteBatch& spriteBatch, const std::string& objectName, glm::vec2& dims, glm::vec4& UVRect, Deep::GLTexture& texture,
		Deep::ColorRGBA8 color /*= Deep::ColorRGBA8(255, 255, 255, 255)*/) {
		// Locating Object Position 
		glm::vec4 destRect;
		// Check if the Object is Available 
		if (objectName == m_objectName) {
			destRect = glm::vec4(m_objectPositionX, m_objectPositionY, dims);
		}
		// Draw the object with the spicified Texture and corrdinates 
		spriteBatch.draw(destRect, UVRect, texture.id, 0.0f, color);
	}

	void LevelManager::drawObjects(const std::string EllipseTexture /* = "" */) {
		// Ellipse Objects Drawing 
		for (int i = 0; i < m_map->GetNumObjectGroups(); i++) {
			const Tmx::ObjectGroup* m_group = m_map->GetObjectGroup(i);

			for (int j = 0; j < m_group->GetNumObjects(); j++) {
				//const Tmx::Object* m_object = m_group->GetObject(j);

				glm::vec4 destRect;
				m_objectPosition = m_camera.convertScreenToWorld(glm::vec2(m_object->GetX(), m_object->GetY()));
				destRect.x = (float)m_objectPosition.x;
				destRect.y = (float)m_objectPosition.y;
				destRect.z = (float)m_object->GetWidth();
				destRect.w = (float)m_object->GetHeight();
				Deep::GLTexture texture = Deep::ResourceManager::getTexture(""); ///< Draw Ellipse with the spicified texture 
				m_spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.id, 0.0f, Deep::ColorRGBA8(255, 255, 255, 255));
				//pos = glm::vec2(pos.x / 2, pos.y / 2);
				// m_DebugRenderer->drawCircle(pos, Deep::ColorRGBA8(255, 20, 20, 255), m_object->GetWidth() / 2);

			}
		}
		// TODO: Add drawing support for other objects 
		//TODO: Add other Polygons and shapes drawing and rendering support for TMX Parsing
	}


	void LevelManager::SDLDraw() {
		// NOTICE: Try to ADD to the LevelManager SDL Drawing and Rendering Support Because it's more stable and easy to Map UV Coords 
 		m_SDLRenderer->Begin();
		SDLDrawLevel();
 		m_SDLRenderer->End(); 	
	}


	void LevelManager::SDLDrawLevel() {
		
		//(id - (tileset.firstGridID - 1)) / tileset.numColumns; ///< Current ROW 
		//(id - (tileset.firstGridID - 1)) % tileset.numColumns; ///< Current Frame 

		int currentROW = (m_tileGID - (m_tileFirstGID - 1)) / m_mapWidth;
		int currentFrame = (m_tileGID - (m_tileFirstGID - 1)) % m_mapWidth;

		// Lopping on all the layers 
		for (int i = 0; i < m_numTileLayers; ++i)
		{

			for (int y = 0; y < m_layerHeight; ++y)
			{
				for (int x = 0; x < m_layerWidth; ++x)
				{

					// Tiles GIDs and IDs 
					m_tileID = m_tileLayer->GetTileId(x, y);
					m_tileGID = m_tileLayer->GetTileGid(x, y);

					const std::string loadedID = "T1";
					if (m_tileLayer->GetTileTilesetIndex(x, y) == -1) {
						//TextureManager::draw()
					}
					else {

						TextureManager::Instance()->drawTile(m_tileMargin, m_tileSpacing, x, y, m_mapTileWidth, m_mapTileHeight, currentROW, currentFrame, m_SDLRenderer->getSDLRenderer());
					}
				}
			}
		}
	}

	void LevelManager::render() {
		// Render the Drawed Batch
		m_spriteBatch.renderBatch();
	}


	void LevelManager::dispose() {
		// Deleting the Pointer Instance For Map
		delete m_map;

		delete m_DebugRenderer;
		delete m_loadUV;
		m_spriteBatch.dispose();
	}

	// Mapping system is currently under development so stay toun for the final release 
	glm::vec4& LevelManager::mappingSystem(int tileID, int numTiles, int numROWTiles, int numROWs) {

		int numColumns = numROWTiles - 1;
		//numTiles += 1;
		glm::vec4 mappedUV;
		unsigned int UV = (numTiles - numColumns) + 1;
		int ID = 0;
		//numTiles += 1;
		glm::vec4 uvRect;
		for (int i = 0; i < numTiles; i++) {
			ID = i; ///< Seeting the ID of Tiles 
			UV++;

 			if (UV == numTiles) {
 				UV -= (numColumns * 2) + 2;
 			}
 			else if (UV == (numTiles - (numROWTiles))) {
 				UV -= (numROWTiles * 2);
 			}
			else if (UV == (numTiles - 16)) {
				UV -= 16;
			}
			else if (UV == 32) {
				UV -= 16;
			}
			else if (UV == 24) {
				UV -= 16;
			}
			else if (UV == 16) {
				UV -= 16;
			}
		//UV++;
		/*for (int x = (numROWs - 1); x > 0; x--) {
			
// 			if (UV == numTiles) {
// 				//printf("%d: \n", UV);
// 				UV -= 8;
// 			}
			if (UV == numTiles) {
				UV -= 8;
			}

			if (UV  == (numROWTiles * x)) {
				UV -= (numROWTiles * 2);
				//UV++;
				//printf("%d: \n", UV);
			} 
		}*/

		//int rows;

			/*if (r == 0) {
				continue;
			}*/
			/*if (UV == (numTiles - (numROWTiles * r)) && r == 1) {
				UV -= (numTiles - (numROWTiles * r));
			}*/
			/* if (UV == (numTiles - (numROWTiles * r)) && r > 1) {
				UV -= (numTiles - (numROWTiles * r));*/
				//}
// 			if (UV == (numTiles - (numROWTiles * r)) && r > 1) {
// 				UV -= numROWTiles * r;
// 				//printf("\n \n \n \n \n \n It's Matching \n \n \n \n \n \n ");
// 			}
		

		//}
	//}


	//if (ID == UV) {
		//printf(" UV Mapping Succes : %d\n", UV);
	//}
	//printf(" UV and ID : (%d,  %d) \n", UV, ID);
		
		if (m_tileID == ID) {
			uvRect = m_sheet->getUVs(UV);
			return uvRect;

	}

	}

	}


	 void LevelManager::convertHEXtoRGB(std::string& HEXColor) {

		// ... and the target rgb integer values.
		int r, g, b;

		// Remove the hashtag ...
		if (HEXColor.at(0) == '#') {
			HEXColor = HEXColor.erase(0, 1);
		}

		// ... and extract the rgb values.
		std::istringstream(HEXColor.substr(0, 2)) >> std::hex >> r;
		std::istringstream(HEXColor.substr(2, 2)) >> std::hex >> g;
		std::istringstream(HEXColor.substr(4, 2)) >> std::hex >> b;

		// Finally dump the result.
		//std::cout << std::dec << "Parsing #" << HEXColor
		//	<< " as hex gives (" << r << ", " << g << ", " << b << ")" << '\n';
		// Setting Color Values for the Background
		m_backgroundColor = Deep::ColorRGBA8(r, g, b, 255); //< TODO: Add support for Parsing Alpha Color 

	}

	void LevelManager::parseMap() {
		m_mapVersion = m_map->GetVersion();
		m_mapOrientation = m_map->GetOrientation();

		m_mapBackgroundColor = m_map->GetBackgroundColor();
		// Converting the HEX [HTML] color into RGB Color 
		convertHEXtoRGB(m_mapBackgroundColor);

		m_mapWidth = m_map->GetWidth();
		m_mapHeight = m_map->GetHeight();
		m_mapTileWidth = m_map->GetTileWidth();
		m_mapTileHeight = m_map->GetTileHeight();
	}

	void LevelManager::parseLayer() {


		m_numLayers = m_map->GetNumLayers();
		for (int i = 0; i < m_numLayers; ++i) {
			m_layer = m_map->GetLayer(i);
		}
		m_layerWidth = m_map->GetWidth();
		m_layerHeight = m_layer->GetHeight();

	}
	void LevelManager::parseTileSet() {
		// Tileset 
		m_tilesNumber = m_map->GetNumTilesets();
		for (int i = 0; i < m_tilesNumber; ++i) {

			m_tileSet = m_map->GetTileset(i);
			m_tileSetName = m_tileSet->GetName();
			m_tileMargin = m_tileSet->GetMargin();
			m_tileSpacing = m_tileSet->GetSpacing();
			m_tileFirstGID = m_tileSet->GetFirstGid();
			m_image = m_tileSet->GetImage();
			m_imageWidth = m_image->GetWidth();
			m_imageHeight = m_image->GetHeight();
			m_imageSource = m_image->GetSource();
			//		if (m_image->GetTransparentColor().empty) {}
				//	else { m_imageTransparentColor = m_image->GetTransparentColor(); }
					//m_imageSource = m_image->GetSource();




							// Tile Animation  TODO: Implement Tiles Animation 
					/*	if (m_tile->IsAnimated()) {
							m_frameCount = m_tile->GetFrameCount();
							m_framesTotalDuration = m_tile->GetTotalDuration();
							m_animationFrames = m_tile->GetFrames();
							int i = 0;
							for (std::vector<Tmx::AnimationFrame>::const_iterator it =
								m_animationFrames.begin(); it != m_animationFrames.end(); it++, i++)
							{
								m_frameTileID = it->GetTileID();
								m_frameDuration = it->GetDuration();
							}
						}*/

						// Tile Object 
				/*	if (m_tile->HasObjects()) {
						for (int j = 0; j < m_tile->GetNumObjects(); ++j)
						{
							m_object = m_tile->GetObject(j);
							m_objectWidth = m_object->GetWidth();
							m_objectHeight = m_object->GetHeight();
							m_objectName = m_object->GetName();
							m_objectPositionX = m_object->GetX();
							m_objectPositionY = m_object->GetY();

								//Polygon Point
							m_objectPolygon = m_object->GetPolygon();

						}
					} */
		}
		//m_texture = Deep::ResourceManager::getTexture(m_imageSource);
		//printf("Image Source : %s", m_imageSource.c_str());

	}

	void LevelManager::parseTileLayer() {


		for (int i = 0; i < m_map->GetNumTileLayers(); ++i)
		{
			m_tileLayer = m_map->GetTileLayer(i);
			m_tileLayerPosition = glm::vec2(m_tileLayer->GetX(), m_tileLayer->GetY()); ///< The Position Of the Layer;
			m_layerWidth = m_tileLayer->GetWidth();
			m_layerHeight = m_tileLayer->GetHeight();
			m_numTileLayers = m_map->GetNumTileLayers();
		}
	}

	void LevelManager::parseObject() {

		for (int i = 0; i < m_map->GetNumObjectGroups(); ++i)
		{

			// Get an object group.
			m_objectGroup = m_map->GetObjectGroup(i);

			// Iterate through all objects in the object group.
			for (int j = 0; j < m_objectGroup->GetNumObjects(); ++j)
			{
				// Get an object.
				m_object = m_objectGroup->GetObject(j);
				
				// Store Object Data in >> map 
					// Storing Position 
				m_objectsPosition.insert(std::make_pair(m_object->GetName(), glm::vec2(m_object->GetX(), m_object->GetY()))); 
					// Storing Dims 
				m_objectsDimensions.insert(std::make_pair(m_object->GetName(), glm::vec2(m_object->GetWidth(), m_object->GetHeight())));
					// Storing ID & GID 
				m_objectsIDs.insert(std::make_pair(m_object->GetName(), glm::vec2(m_object->GetId(), m_object->GetGid())));

				// Ellipse 
				m_objectEllipse = m_object->GetEllipse();
				//m_objectEllipseCenter = glm::vec2(m_objectEllipse->GetCenterX(), m_objectEllipse->GetCenterY());
				//m_objectEllipseRadius = glm::vec2(m_objectEllipse->GetRadiusX(), m_objectEllipse->GetRadiusX());

			/*	glm::vec4 destRect;
				m_objectPosition = m_camera.convertScreenToWorld(glm::vec2(m_object->GetX(), m_object->GetY()));
				destRect.x = m_objectPosition.x;
				destRect.y = m_objectPosition.y;
				destRect.z = m_object->GetWidth();
				destRect.w = m_object->GetHeight();
				Deep::GLTexture texture = Deep::ResourceManager::getTexture("Tiles/coinGold.png");
				m_spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.id, 0.0f, Deep::ColorRGBA8(255, 255, 255, 255));

				// Print Polygon points.
/*				const Tmx::Polygon *polygon = m_groupObject->GetPolygon();
				if (polygon != 0)
				{
					for (int i = 0; i < polygon->GetNumPoints(); i++)
					{
						const Tmx::Point &point = polygon->GetPoint(i);
						printf("Object Polygon: Point %d: (%f, %f)\n", i, point.x,
							point.y);
					}*/
				//}
			}
		}
	}
}