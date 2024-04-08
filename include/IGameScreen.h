#pragma once

#ifndef INVALID_SCREEN_INDEX
#define INVALID_SCREEN_INDEX -1
#endif

namespace Toaster
{
    class IMainGame;

    enum class SCREEN_STATE
    {
        NONE,
        RUNNING,
        EXIT_APPLICATION,
        CHANGE_NEXT,
        CHANGE_PREVIOUS
    };

    class IGameScreen
    {
    public:
        friend class ScreenList;

        virtual void build() = 0;
        virtual void destroy() = 0;

        // Called when screen enters/leaves focus
        virtual void onEntry() = 0;
        virtual void onExit() = 0;

        virtual void update() = 0;
        virtual void draw() = 0;

        virtual int getNextIndex() const = 0;
        virtual int getPreviousIndex() const = 0;

        // Getters
        int getIndex() const { return _index; }
        SCREEN_STATE getState() const { return _currentState; }

        // Setters
        void setParent(IMainGame *game) { this->_game = game; }
        void setRunning() { this->_currentState = SCREEN_STATE::RUNNING; }

    protected:
        SCREEN_STATE _currentState = SCREEN_STATE::NONE;
        IMainGame *_game = nullptr;
        int _index = INVALID_SCREEN_INDEX;
    };
}
