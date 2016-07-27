#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <SDL/SDL_events.h>

namespace Deep {
    class GUI {
    public:
        void init(const std::string& resourceDirectory);
        void destroy();

        void draw();
        void update();

        void setMouseCursor(const std::string& imageFile);
        void showMouseCursor();
        void hideMouseCursor();

        void onSDLEvent(SDL_Event& evnt);

        void loadScheme(const std::string& schemeFile);
        void setFont(const std::string& fontFile);
        CEGUI::Window* createWidget(const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
        CEGUI::Window* createWidget(CEGUI::Window* parent, const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
        static void setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);
		static void setWidgetPos(CEGUI::Window* widget, const glm::vec2& position);

		void createImage(const std::string& imagePath, const std::string& imageName);
		void loadLayout(const std::string& fileName);
		void loadLayout(const std::string& fileName, CEGUI::Window* parentWindow);
		void loadAnimation(const std::string& fileName);
		void loadLuaScript(const std::string& fileName);

		// Events Handlers 
		void handleEvent(const std::string& widgetName, const std::string& name, CEGUI::SubscriberSlot& subscriberSolt, const int layoutNumber = 0);
		CEGUI::Window* getLayoutChilds(const std::string& childHierarchy, const int layoutNumber = 0);

        // Getters
        static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
        const CEGUI::GUIContext* getContext() { return m_context; }
		CEGUI::Window* getRoot() const { return m_root; }
		CEGUI::WindowManager* getWindowManager() const { return m_WindowManager; }
		CEGUI::Window* getRootWindow(const int LayoutNumber = 0) const { return m_layoutWindows[LayoutNumber]; }

    private:
        static CEGUI::OpenGL3Renderer* m_renderer;
        CEGUI::GUIContext* m_context = nullptr;
        CEGUI::Window* m_root = nullptr;
		CEGUI::Window* m_layoutWindow = nullptr;
		CEGUI::System* mGUISystem;
		CEGUI::WindowManager* m_WindowManager;
        unsigned int m_lastTime = 0;
		// Vector for Multiple Layout loading and working on theme 
		std::vector<CEGUI::Window*> m_layoutWindows;
    };
}