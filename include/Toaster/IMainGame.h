#pragma once

#include "Window.h"
#include "InputManager.h"

#include <memory>

namespace Toaster
{
    class ScreenList;
    class IGameScreen;

    class IMainGame
    {
    public:

        IMainGame();
        virtual ~IMainGame();

        void run();
        void exit();

        virtual void onInit() = 0;
        virtual void onExit() = 0;

        virtual void addScreens() = 0;

        void onSDLEvent(SDL_Event &evnt);

        // Getters

        const float getFps() const { return _fps; }

        InputManager inputManager;

    protected:

        std::unique_ptr<ScreenList> _screenList = nullptr;
        IGameScreen *_currentScreen = nullptr;
        bool _isRunning = false;
        float _fps = 0.0f;
        Window _window;

        virtual void update();
        virtual void draw();

        bool init();
        bool initSystems();
    };
}
