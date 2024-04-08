#include "IMainGame.h"
#include "IGameScreen.h"
#include "ScreenList.h"
#include "Timing.h"
#include "Toaster.h"

namespace Toaster
{
    IMainGame::IMainGame()
    {
        _screenList = std::make_unique<ScreenList>(this);
    }

    IMainGame::~IMainGame()
    {
        // Empty
    }

    void IMainGame::run()
    {
        if (!init())
            return;

        FpsLimiter limiter;
        limiter.setMaxFps(60.0f);

        _isRunning = true;

        while (_isRunning)
        {
            limiter.begin();

            inputManager.update();

            update();

            // Prevent exception on draw() call if the program exits
            if (!_isRunning)
                break;

            draw();

            _fps = limiter.end();

            _window.swapBuffer();
        }
    }

    void IMainGame::exit()
    {
        _currentScreen->onExit();

        if (_screenList)
        {
            _screenList->destroy();
            _screenList.reset();
        }

        _isRunning = false;
    }

    bool IMainGame::init()
    {
        Toaster::init();

        if (!initSystems())
            return false;

        onInit();

        addScreens();

        _currentScreen = _screenList->getCurrent();
        _currentScreen->onEntry();
        _currentScreen->setRunning();

        return true;
    }

    bool IMainGame::initSystems()
    {
        // TODO: Add error checking in _window.create();
        _window.create("Default", 1920, 1080);
        return true;
    }

    void IMainGame::onSDLEvent(SDL_Event &evnt)
    {
        switch (evnt.type)
        {
        case SDL_QUIT:
            exit();
            break;
        case SDL_MOUSEMOTION:
            inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
            break;
        case SDL_KEYDOWN:
            inputManager.pressKey(evnt.key.keysym.sym);
            break;
        case SDL_KEYUP:
            inputManager.releaseKey(evnt.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            inputManager.pressKey(evnt.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            inputManager.releaseKey(evnt.button.button);
            break;
        }
    }

    void IMainGame::update()
    {
        if (!_currentScreen)
            exit();

        switch (_currentScreen->getState())
        {
        case SCREEN_STATE::RUNNING:
            _currentScreen->update();
            break;
        case SCREEN_STATE::CHANGE_NEXT:
            _currentScreen->onExit();
            _currentScreen = _screenList->moveToNext();
            if (_currentScreen)
            {
                _currentScreen->setRunning();
                _currentScreen->onEntry();
            }
            break;

        case SCREEN_STATE::CHANGE_PREVIOUS:
            _currentScreen->onExit();
            _currentScreen = _screenList->moveToPrevious();
            if (_currentScreen)
            {
                _currentScreen->setRunning();
                _currentScreen->onEntry();
            }
            break;

        case SCREEN_STATE::EXIT_APPLICATION:
            exit();
            break;

        default:
            break;
        }
    }

    void IMainGame::draw()
    {
        glViewport(0, 0, _window.getWidth(), _window.getHeight());

        if (_currentScreen && _currentScreen->getState() == SCREEN_STATE::RUNNING)
            _currentScreen->draw();
    }
}
