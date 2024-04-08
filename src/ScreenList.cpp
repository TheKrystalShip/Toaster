#include "ScreenList.h"

#include "IGameScreen.h"

namespace Toaster
{
    ScreenList::ScreenList(IMainGame *game) : _game(game)
    {
    }

    ScreenList::~ScreenList()
    {
        destroy();
    }

    IGameScreen *ScreenList::getCurrent()
    {
        if (_currentScreenIndex == INVALID_SCREEN_INDEX)
            return nullptr;

        return _screens[_currentScreenIndex];
    }

    IGameScreen *ScreenList::moveToNext()
    {
        auto current = getCurrent();

        if (current->getNextIndex() != INVALID_SCREEN_INDEX)
            _currentScreenIndex = current->getNextIndex();

        return getCurrent();
    }

    IGameScreen *ScreenList::moveToPrevious()
    {
        auto current = getCurrent();

        if (current->getPreviousIndex() != INVALID_SCREEN_INDEX)
            _currentScreenIndex = current->getPreviousIndex();

        return getCurrent();
    }

    void ScreenList::setScreen(int screenIndex)
    {
        _currentScreenIndex = screenIndex;
    }

    void ScreenList::addScreen(IGameScreen *newScreen)
    {
        newScreen->_index = _screens.size();
        newScreen->build();
        newScreen->setParent(_game);

        _screens.push_back(newScreen);
    }

    void ScreenList::destroy()
    {
        for (std::size_t i = 0; i < _screens.size(); i++)
        {
            _screens[i]->destroy();
        }

        _screens.resize(0);
        _currentScreenIndex = INVALID_SCREEN_INDEX;
    }
}
