#pragma once

#include <vector>

namespace Toaster
{
    class IMainGame;
    class IGameScreen;

    class ScreenList
    {
    public:
        ScreenList(IMainGame *game);
        ~ScreenList();

        IGameScreen *getCurrent();
        IGameScreen *moveToNext();
        IGameScreen *moveToPrevious();

        void setScreen(int screenIndex);
        void addScreen(IGameScreen *newScreen);

        void destroy();


    protected:
        IMainGame *_game = nullptr;
        int _currentScreenIndex = -1;
        std::vector<IGameScreen *> _screens;
    };
}
